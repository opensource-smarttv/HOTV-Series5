/* $Id: //DTV/MP_BR/DTV_X_IDTV1401_002306_12_001_37_007_120_001/l-pdk/device/mediatek_common/vm_linux/chiling/kernel/linux-3.10/arch/cris/include/asm/dma.h#1 $ */

#ifndef _ASM_DMA_H
#define _ASM_DMA_H

#include <arch/dma.h>

/* it's useless on the Etrax, but unfortunately needed by the new
   bootmem allocator (but this should do it for this) */

#define MAX_DMA_ADDRESS PAGE_OFFSET

/* From PCI */

#ifdef CONFIG_PCI
extern int isa_dma_bridge_buggy;
#else
#define isa_dma_bridge_buggy 	(0)
#endif

#endif /* _ASM_DMA_H */
