/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/

#ifndef __LINUXBT_SPP_IF_H__
#define __LINUXBT_SPP_IF_H__

#include "u_bluetooth.h"

/**
 * FUNCTION NAME: linuxbt_spp_init
 * PURPOSE:
 *      The function is used to init SPP interface.
 * INPUT:
 *      VOID
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 linuxbt_spp_init(VOID);

/**
 * FUNCTION NAME: linuxbt_spp_deinit
 * PURPOSE:
 *      The function is used to deinit SPP interface.
 * INPUT:
 *      VOID
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 linuxbt_spp_deinit(VOID);

/**
 * FUNCTION NAME: linuxbt_spp_activate
 * PURPOSE:
 *      The function is used to active SPP with uuid.
 * INPUT:
 *      ptr         -- the device address that to active.
 *      puuid_128   -- the uuid.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 linuxbt_spp_activate(CHAR *ptr, CHAR *puuid_128);

/**
 * FUNCTION NAME: linuxbt_spp_deactivate
 * PURPOSE:
 *      The function is used to deactive SPP with uuid.
 * INPUT:
 *      puuid_128   -- the uuid that to deactive.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 linuxbt_spp_deactivate(CHAR *puuid_128);

/**
 * FUNCTION NAME: linuxbt_spp_connect
 * PURPOSE:
 *      The function is used to SPP connect with uuid.
 * INPUT:
 *      bt_addr -- the device address that to connect.
 *      uuid    -- using this uuid to connect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 linuxbt_spp_connect(CHAR *bt_addr, CHAR *puuid_128);

/**
 * FUNCTION NAME: linuxbt_spp_disconnect
 * PURPOSE:
 *      The function is used to SPP disconnect with port id.
 * INPUT:
 *      addr -- the device address that to disconnect.
 *      uuid    -- using this uuid to disconnect.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 linuxbt_spp_disconnect(CHAR *addr, CHAR *uuid);

/**
 * FUNCTION NAME: linuxbt_spp_send_data
 * PURPOSE:
 *      The function is used to send data.
 * INPUT:
 *      bd_addr -- the device to send.
 *      uuid -- the uuid to send.
 *      pdata -- the string to send.
 *      length -- the string length to send.
 * OUTPUT:
 *      None
 * RETURN:
 *      BT_SUCCESS           -- Operate success.
 *      BT_ERR_STATUS_FAIL   -- Operate fail.
 * NOTES:
 *      None
 */
INT32 linuxbt_spp_send_data(CHAR* bd_addr, CHAR* uuid, CHAR *pdata, UINT16 length);

#endif /* __LINUXBT_SPP_IF_H__ */
