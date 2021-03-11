/* $Id: //DTV/MP_BR/DTV_X_IDTV1401_002306_12_001_37_007_120_001/l-pdk/device/mediatek_common/vm_linux/chiling/kernel/linux-3.10/include/uapi/linux/isdn_divertif.h#1 $
 *
 * Header for the diversion supplementary interface for i4l.
 *
 * Author    Werner Cornelius (werner@titro.de)
 * Copyright by Werner Cornelius (werner@titro.de)
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#ifndef _UAPI_LINUX_ISDN_DIVERTIF_H
#define _UAPI_LINUX_ISDN_DIVERTIF_H

/***********************************************************/
/* magic value is also used to control version information */
/***********************************************************/
#define DIVERT_IF_MAGIC 0x25873401
#define DIVERT_CMD_REG  0x00  /* register command */
#define DIVERT_CMD_REL  0x01  /* release command */
#define DIVERT_NO_ERR   0x00  /* return value no error */
#define DIVERT_CMD_ERR  0x01  /* invalid cmd */
#define DIVERT_VER_ERR  0x02  /* magic/version invalid */
#define DIVERT_REG_ERR  0x03  /* module already registered */
#define DIVERT_REL_ERR  0x04  /* module not registered */
#define DIVERT_REG_NAME isdn_register_divert


#endif /* _UAPI_LINUX_ISDN_DIVERTIF_H */
