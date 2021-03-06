/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2010 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file ump_ukk_wrappers.c
 * Defines the wrapper functions which turn Linux IOCTL calls into _ukk_ calls for the reference implementation
 */


#include <asm/uaccess.h>             /* user space access */

#include "ump_osk.h"
#include "ump_uk_types.h"
#include "ump_ukk.h"
#include "ump_kernel_common.h"

/*
 * IOCTL operation; Allocate UMP memory
 */
int ump_allocate_wrapper(u32 __user * argument, struct ump_session_data  * session_data)
{
	_ump_uk_allocate_s user_interaction;
	_mali_osk_errcode_t err;

	/* Sanity check input parameters */
	if (NULL == argument || NULL == session_data)
	{
		MSG_ERR(("NULL parameter in ump_ioctl_allocate()\n"));
		return -ENOTTY;
	}

	/* Copy the user space memory to kernel space (so we safely can read it) */
	if (0 != copy_from_user(&user_interaction, argument, sizeof(user_interaction)))
	{
		MSG_ERR(("copy_from_user() in ump_ioctl_allocate()\n"));
		return -EFAULT;
	}

	user_interaction.ctx = (void *) session_data;

	err = _ump_ukk_allocate( &user_interaction );
	if( _MALI_OSK_ERR_OK != err )
	{
		DBG_MSG(1, ("_ump_ukk_allocate() failed in ump_ioctl_allocate()\n"));
		return map_errcode(err);
	}
	user_interaction.ctx = NULL;

	if (0 != copy_to_user(argument, &user_interaction, sizeof(user_interaction)))
	{
		/* If the copy fails then we should release the memory. We can use the IOCTL release to accomplish this */
		_ump_uk_release_s release_args;

		MSG_ERR(("copy_to_user() failed in ump_ioctl_allocate()\n"));

		release_args.ctx = (void *) session_data;
		release_args.secure_id = user_interaction.secure_id;

		err = _ump_ukk_release( &release_args );
		if(_MALI_OSK_ERR_OK != err)
		{
			MSG_ERR(("_ump_ukk_release() also failed when trying to release newly allocated memory in ump_ioctl_allocate()\n"));
		}

		return -EFAULT;
	}

	return 0; /* success */
}
#ifdef UMP_TO_FBM_SUPPORT
int ump_allocate_secure_id_wrapper(u32 __user * argument, struct ump_session_data  * session_data)
{
	 int seucre_id;
	 _ump_uk_to_fbm_s fbm_args;
		_mali_osk_errcode_t err;
		/* Sanity check input parameters */
		if (NULL == session_data)
		{
			MSG_ERR(("NULL parameter in ump_allocate_secure_id_wrapper()\n"));
			return -ENOTTY;
		}
	
		/* Copy the user space memory to kernel space (so we safely can read it) */
		if (0 != copy_from_user(&fbm_args, argument, sizeof(fbm_args)))
		{
			MSG_ERR(("copy_from_user() in ump_ioctl_get_api_version()\n"));
			return -EFAULT;
		}
	
		fbm_args.ctx = (void*) session_data;
        seucre_id = ump_secure_id_handle_create_from_phys_blocks(&fbm_args, fbm_args.phys_addr, fbm_args.mapping, fbm_args.size);
		fbm_args.secure_id = seucre_id;

		
		if (0 != copy_to_user(argument, &fbm_args, sizeof(fbm_args)))
		{
			/* If the copy fails then we should release the memory. We can use the IOCTL release to accomplish this */

			MSG_ERR(("copy_to_user() failed in ump_allocate_secure_id_wrapper()\n"));
			return -EFAULT;
		}

	return 0; /* success */
}
#endif
