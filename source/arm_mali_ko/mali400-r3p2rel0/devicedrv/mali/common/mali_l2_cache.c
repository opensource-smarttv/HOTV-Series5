/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2012 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#include "mali_kernel_common.h"
#include "mali_osk.h"
#include "mali_l2_cache.h"
#include "mali_hw_core.h"
#include "mali_scheduler.h"

/**
 * Size of the Mali L2 cache registers in bytes
 */
#define MALI400_L2_CACHE_REGISTERS_SIZE 0x30

/**
 * Mali L2 cache register numbers
 * Used in the register read/write routines.
 * See the hardware documentation for more information about each register
 */
typedef enum mali_l2_cache_register {
	MALI400_L2_CACHE_REGISTER_STATUS       = 0x0008,
	/*unused                               = 0x000C */
	MALI400_L2_CACHE_REGISTER_COMMAND      = 0x0010, /**< Misc cache commands, e.g. clear */
	MALI400_L2_CACHE_REGISTER_CLEAR_PAGE   = 0x0014,
	MALI400_L2_CACHE_REGISTER_MAX_READS    = 0x0018, /**< Limit of outstanding read requests */
	MALI400_L2_CACHE_REGISTER_ENABLE       = 0x001C, /**< Enable misc cache features */
	MALI400_L2_CACHE_REGISTER_PERFCNT_SRC0 = 0x0020,
	MALI400_L2_CACHE_REGISTER_PERFCNT_VAL0 = 0x0024,
	MALI400_L2_CACHE_REGISTER_PERFCNT_SRC1 = 0x0028,
	MALI400_L2_CACHE_REGISTER_PERFCNT_VAL1 = 0x002C,
} mali_l2_cache_register;

/**
 * Mali L2 cache commands
 * These are the commands that can be sent to the Mali L2 cache unit
 */
typedef enum mali_l2_cache_command
{
	MALI400_L2_CACHE_COMMAND_CLEAR_ALL = 0x01, /**< Clear the entire cache */
	/* Read HW TRM carefully before adding/using other commands than the clear above */
} mali_l2_cache_command;

/**
 * Mali L2 cache commands
 * These are the commands that can be sent to the Mali L2 cache unit
 */
typedef enum mali_l2_cache_enable
{
	MALI400_L2_CACHE_ENABLE_DEFAULT = 0x0, /**< Default state of enable register */
	MALI400_L2_CACHE_ENABLE_ACCESS = 0x01, /**< Permit cacheable accesses */
	MALI400_L2_CACHE_ENABLE_READ_ALLOCATE = 0x02, /**< Permit cache read allocate */
} mali_l2_cache_enable;

/**
 * Mali L2 cache status bits
 */
typedef enum mali_l2_cache_status
{
	MALI400_L2_CACHE_STATUS_COMMAND_BUSY = 0x01, /**< Command handler of L2 cache is busy */
	MALI400_L2_CACHE_STATUS_DATA_BUSY    = 0x02, /**< L2 cache is busy handling data requests */
} mali_l2_cache_status;

/**
 * Definition of the L2 cache core struct
 * Used to track a L2 cache unit in the system.
 * Contains information about the mapping of the registers
 */
struct mali_l2_cache_core
{
	struct mali_hw_core  hw_core;      /**< Common for all HW cores */
	u32                  core_id;      /**< Unique core ID */
	_mali_osk_lock_t    *command_lock; /**< Serialize all L2 cache commands */
	_mali_osk_lock_t    *counter_lock; /**< Synchronize L2 cache counter access */
	u32                  counter_src0; /**< Performance counter 0, MALI_HW_CORE_NO_COUNTER for disabled */
	u32                  counter_src1; /**< Performance counter 1, MALI_HW_CORE_NO_COUNTER for disabled */
	u32                  last_invalidated_id;
	mali_bool            power_is_enabled;
};

#define MALI400_L2_MAX_READS_DEFAULT 0x1C

static struct mali_l2_cache_core *mali_global_l2_cache_cores[MALI_MAX_NUMBER_OF_L2_CACHE_CORES];
static u32 mali_global_num_l2_cache_cores = 0;

int mali_l2_max_reads = MALI400_L2_MAX_READS_DEFAULT;

/* Local helper functions */
static _mali_osk_errcode_t mali_l2_cache_send_command(struct mali_l2_cache_core *cache, u32 reg, u32 val);


struct mali_l2_cache_core *mali_l2_cache_create(_mali_osk_resource_t *resource)
{
	struct mali_l2_cache_core *cache = NULL;
	_mali_osk_lock_flags_t lock_flags;

#if defined(MALI_UPPER_HALF_SCHEDULING)
	lock_flags = _MALI_OSK_LOCKFLAG_ORDERED | _MALI_OSK_LOCKFLAG_SPINLOCK_IRQ | _MALI_OSK_LOCKFLAG_NONINTERRUPTABLE;
#else
	lock_flags = _MALI_OSK_LOCKFLAG_ORDERED | _MALI_OSK_LOCKFLAG_SPINLOCK | _MALI_OSK_LOCKFLAG_NONINTERRUPTABLE;
#endif

	MALI_DEBUG_PRINT(2, ("Mali L2 cache: Creating Mali L2 cache: %s\n", resource->description));

	if (mali_global_num_l2_cache_cores >= MALI_MAX_NUMBER_OF_L2_CACHE_CORES)
	{
		MALI_PRINT_ERROR(("Mali L2 cache: Too many L2 cache core objects created\n"));
		return NULL;
	}

	cache = _mali_osk_malloc(sizeof(struct mali_l2_cache_core));
	if (NULL != cache)
	{
		cache->core_id =  mali_global_num_l2_cache_cores;
		cache->counter_src0 = MALI_HW_CORE_NO_COUNTER;
		cache->counter_src1 = MALI_HW_CORE_NO_COUNTER;
		if (_MALI_OSK_ERR_OK == mali_hw_core_create(&cache->hw_core, resource, MALI400_L2_CACHE_REGISTERS_SIZE))
		{
			cache->command_lock = _mali_osk_lock_init(lock_flags, 0, _MALI_OSK_LOCK_ORDER_L2_COMMAND);
			if (NULL != cache->command_lock)
			{
				cache->counter_lock = _mali_osk_lock_init(lock_flags, 0, _MALI_OSK_LOCK_ORDER_L2_COUNTER);
				if (NULL != cache->counter_lock)
				{
					mali_l2_cache_reset(cache);

					cache->last_invalidated_id = 0;
					cache->power_is_enabled = MALI_TRUE;

					mali_global_l2_cache_cores[mali_global_num_l2_cache_cores] = cache;
					mali_global_num_l2_cache_cores++;

					return cache;
				}
				else
				{
					MALI_PRINT_ERROR(("Mali L2 cache: Failed to create counter lock for L2 cache core %s\n", cache->hw_core.description));
				}

				_mali_osk_lock_term(cache->command_lock);
			}
			else
			{
				MALI_PRINT_ERROR(("Mali L2 cache: Failed to create command lock for L2 cache core %s\n", cache->hw_core.description));
			}

			mali_hw_core_delete(&cache->hw_core);
		}

		_mali_osk_free(cache);
	}
	else
	{
		MALI_PRINT_ERROR(("Mali L2 cache: Failed to allocate memory for L2 cache core\n"));
	}

	return NULL;
}

void mali_l2_cache_delete(struct mali_l2_cache_core *cache)
{
	u32 i;

	/* reset to defaults */
	mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_MAX_READS, (u32)MALI400_L2_MAX_READS_DEFAULT);
	mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_ENABLE, (u32)MALI400_L2_CACHE_ENABLE_DEFAULT);

	_mali_osk_lock_term(cache->counter_lock);
	_mali_osk_lock_term(cache->command_lock);
	mali_hw_core_delete(&cache->hw_core);

	for (i = 0; i < MALI_MAX_NUMBER_OF_L2_CACHE_CORES; i++)
	{
		if (mali_global_l2_cache_cores[i] == cache)
		{
			mali_global_l2_cache_cores[i] = NULL;
			mali_global_num_l2_cache_cores--;
		}
	}

	_mali_osk_free(cache);
}

void mali_l2_cache_power_is_enabled_set(struct mali_l2_cache_core * core, mali_bool power_is_enabled)
{
       core->power_is_enabled = power_is_enabled;
}

mali_bool mali_l2_cache_power_is_enabled_get(struct mali_l2_cache_core * core)
{
       return core->power_is_enabled;
}

u32 mali_l2_cache_get_id(struct mali_l2_cache_core *cache)
{
	return cache->core_id;
}

mali_bool mali_l2_cache_core_set_counter_src0(struct mali_l2_cache_core *cache, u32 counter)
{
	u32 value = 0; /* disabled src */
	mali_bool core_is_on;

	MALI_DEBUG_ASSERT_POINTER(cache);

	core_is_on = mali_l2_cache_lock_power_state(cache);

	_mali_osk_lock_wait(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);

	cache->counter_src0 = counter;

	if (MALI_HW_CORE_NO_COUNTER != counter)
	{
		value = counter;
	}

	if (MALI_TRUE == core_is_on)
	{
		mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_PERFCNT_SRC0, value);
	}

	_mali_osk_lock_signal(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);

	mali_l2_cache_unlock_power_state(cache);

	return MALI_TRUE;
}

mali_bool mali_l2_cache_core_set_counter_src1(struct mali_l2_cache_core *cache, u32 counter)
{
	u32 value = 0; /* disabled src */
	mali_bool core_is_on;

	MALI_DEBUG_ASSERT_POINTER(cache);

	core_is_on = mali_l2_cache_lock_power_state(cache);

	_mali_osk_lock_wait(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);

	cache->counter_src1 = counter;

	if (MALI_HW_CORE_NO_COUNTER != counter)
	{
		value = counter;
	}

	if (MALI_TRUE == core_is_on)
	{
		mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_PERFCNT_SRC1, value);
	}

	_mali_osk_lock_signal(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);

	mali_l2_cache_unlock_power_state(cache);

	return MALI_TRUE;
}

u32 mali_l2_cache_core_get_counter_src0(struct mali_l2_cache_core *cache)
{
	return cache->counter_src0;
}

u32 mali_l2_cache_core_get_counter_src1(struct mali_l2_cache_core *cache)
{
	return cache->counter_src1;
}

void mali_l2_cache_core_get_counter_values(struct mali_l2_cache_core *cache, u32 *src0, u32 *value0, u32 *src1, u32 *value1)
{
	MALI_DEBUG_ASSERT(NULL != src0);
	MALI_DEBUG_ASSERT(NULL != value0);
	MALI_DEBUG_ASSERT(NULL != src1);
	MALI_DEBUG_ASSERT(NULL != value1);

	/* Caller must hold the PM lock and know that we are powered on */

	_mali_osk_lock_wait(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);

	*src0 = cache->counter_src0;
	*src1 = cache->counter_src1;

	if (cache->counter_src0 != MALI_HW_CORE_NO_COUNTER)
	{
		*value0 = mali_hw_core_register_read(&cache->hw_core, MALI400_L2_CACHE_REGISTER_PERFCNT_VAL0);
	}

	if (cache->counter_src1 != MALI_HW_CORE_NO_COUNTER)
	{
		*value1 = mali_hw_core_register_read(&cache->hw_core, MALI400_L2_CACHE_REGISTER_PERFCNT_VAL1);
	}

	_mali_osk_lock_signal(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);
}

struct mali_l2_cache_core *mali_l2_cache_core_get_glob_l2_core(u32 index)
{
	if (MALI_MAX_NUMBER_OF_L2_CACHE_CORES > index)
	{
		return mali_global_l2_cache_cores[index];
	}

	return NULL;
}

u32 mali_l2_cache_core_get_glob_num_l2_cores(void)
{
	return mali_global_num_l2_cache_cores;
}

void mali_l2_cache_reset(struct mali_l2_cache_core *cache)
{
	/* Invalidate cache (just to keep it in a known state at startup) */
	mali_l2_cache_invalidate_all(cache);

	/* Enable cache */
	mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_ENABLE, (u32)MALI400_L2_CACHE_ENABLE_ACCESS | (u32)MALI400_L2_CACHE_ENABLE_READ_ALLOCATE);
	mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_MAX_READS, (u32)mali_l2_max_reads);

	/* Restart any performance counters (if enabled) */
	_mali_osk_lock_wait(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);

	if (cache->counter_src0 != MALI_HW_CORE_NO_COUNTER)
	{
		mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_PERFCNT_SRC0, cache->counter_src0);
	}

	if (cache->counter_src1 != MALI_HW_CORE_NO_COUNTER)
	{
		mali_hw_core_register_write(&cache->hw_core, MALI400_L2_CACHE_REGISTER_PERFCNT_SRC1, cache->counter_src1);
	}

	_mali_osk_lock_signal(cache->counter_lock, _MALI_OSK_LOCKMODE_RW);
}

void mali_l2_cache_reset_all(void)
{
	int i;
	u32 num_cores = mali_l2_cache_core_get_glob_num_l2_cores();

	for (i = 0; i < num_cores; i++)
	{
		mali_l2_cache_reset(mali_l2_cache_core_get_glob_l2_core(i));
	}
}

_mali_osk_errcode_t mali_l2_cache_invalidate_all(struct mali_l2_cache_core *cache)
{
	return mali_l2_cache_send_command(cache, MALI400_L2_CACHE_REGISTER_COMMAND, MALI400_L2_CACHE_COMMAND_CLEAR_ALL);
}

mali_bool mali_l2_cache_invalidate_all_conditional(struct mali_l2_cache_core *cache, u32 id)
{
       MALI_DEBUG_ASSERT_POINTER(cache);

       if (NULL != cache)
       {
               /* If the last cache invalidation was done by a job with a higher id we
                * don't have to flush. Since user space will store jobs w/ their
                * corresponding memory in sequence (first job #0, then job #1, ...),
                * we don't have to flush for job n-1 if job n has already invalidated
                * the cache since we know for sure that job n-1's memory was already
                * written when job n was started. */
               if (((s32)id) <= ((s32)cache->last_invalidated_id))
               {
                       return MALI_FALSE;
               }
               else
               {
                       cache->last_invalidated_id = mali_scheduler_get_new_id();
               }

               mali_l2_cache_invalidate_all(cache);
       }
       return MALI_TRUE;
}

void mali_l2_cache_invalidate_all_force(struct mali_l2_cache_core *cache)
{
       MALI_DEBUG_ASSERT_POINTER(cache);

       if (NULL != cache)
       {
               cache->last_invalidated_id = mali_scheduler_get_new_id();
               mali_l2_cache_invalidate_all(cache);
       }
}

_mali_osk_errcode_t mali_l2_cache_invalidate_pages(struct mali_l2_cache_core *cache, u32 *pages, u32 num_pages)
{
	u32 i;
	_mali_osk_errcode_t ret1, ret = _MALI_OSK_ERR_OK;

	for (i = 0; i < num_pages; i++)
	{
		ret1 = mali_l2_cache_send_command(cache, MALI400_L2_CACHE_REGISTER_CLEAR_PAGE, pages[i]);
		if (_MALI_OSK_ERR_OK != ret1)
		{
			ret = ret1;
		}
	}

	return ret;
}

void mali_l2_cache_invalidate_pages_conditional(u32 *pages, u32 num_pages)
{
       u32 i;

       for (i = 0; i < mali_global_num_l2_cache_cores; i++)
       {
               /*additional check*/
               if (MALI_TRUE == mali_l2_cache_lock_power_state(mali_global_l2_cache_cores[i]))
               {
                       mali_l2_cache_invalidate_pages(mali_global_l2_cache_cores[i], pages, num_pages);
               }
               mali_l2_cache_unlock_power_state(mali_global_l2_cache_cores[i]);
               /*check for failed power locking???*/
       }
}

mali_bool mali_l2_cache_lock_power_state(struct mali_l2_cache_core *cache)
{
	return _mali_osk_pm_dev_ref_add_no_power_on();
}

void mali_l2_cache_unlock_power_state(struct mali_l2_cache_core *cache)
{
	_mali_osk_pm_dev_ref_dec_no_power_on();
}

/* -------- local helper functions below -------- */


static _mali_osk_errcode_t mali_l2_cache_send_command(struct mali_l2_cache_core *cache, u32 reg, u32 val)
{
	int i = 0;
	const int loop_count = 100000;

	/*
	 * Grab lock in order to send commands to the L2 cache in a serialized fashion.
	 * The L2 cache will ignore commands if it is busy.
	 */
	_mali_osk_lock_wait(cache->command_lock, _MALI_OSK_LOCKMODE_RW);

	/* First, wait for L2 cache command handler to go idle */

	for (i = 0; i < loop_count; i++)
	{
		if (!(mali_hw_core_register_read(&cache->hw_core, MALI400_L2_CACHE_REGISTER_STATUS) & (u32)MALI400_L2_CACHE_STATUS_COMMAND_BUSY))
		{
			break;
		}
	}

	if (i == loop_count)
	{
		_mali_osk_lock_signal(cache->command_lock, _MALI_OSK_LOCKMODE_RW);
		MALI_DEBUG_PRINT(1, ( "Mali L2 cache: aborting wait for command interface to go idle\n"));
		MALI_ERROR( _MALI_OSK_ERR_FAULT );
	}

	/* then issue the command */
	mali_hw_core_register_write(&cache->hw_core, reg, val);

	_mali_osk_lock_signal(cache->command_lock, _MALI_OSK_LOCKMODE_RW);

	MALI_SUCCESS;
}
