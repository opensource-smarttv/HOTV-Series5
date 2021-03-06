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
/*------------------------------------------------------------------------
                    include files
 -----------------------------------------------------------------------*/
#include <stdio.h>
#include "ri_common.h"

#define RET_ON_FAIL(stmt) \
do {\
    INT32 __i4_ret;\
    __i4_ret = (stmt);\
    if(__i4_ret != RPCR_OK)\
    {   RPC_ERROR("RPC Failure %s, #%d\n", __FUNCTION__, __LINE__);\
        return __i4_ret;\
    }\
}while(0)

EXPORT_SYMBOL RPC_CB_NFY_TAG_T * ri_create_cb_tag(
    RPC_ID_T t_rpc_id,
    VOID *   apv_cb_addr_ex[],
    SIZE_T   z_num,
    VOID *   pv_tag)
{
    RPC_CB_NFY_TAG_T *   pt_nfy_tag;

    pt_nfy_tag = (RPC_CB_NFY_TAG_T *)malloc(sizeof(RPC_CB_NFY_TAG_T));
    if(pt_nfy_tag == NULL)
    {
        printf("<Server>alloc memory for tag error\n");

        return NULL;
    }
    else
    {
        printf("<Server>alloc memory for tag succeed: 0x%lx\n", (INT32)pt_nfy_tag);
    }

    pt_nfy_tag->t_id        = t_rpc_id;
    pt_nfy_tag->pv_tag      = pv_tag;

    if(z_num == 1)
    {
        pt_nfy_tag->pv_cb_addr  = apv_cb_addr_ex[0];
    }
    else if(z_num == 0)
    {
        //do nothing
    }
    else
    {
        SIZE_T z_i;
        for(z_i = 0; z_i < z_num; z_i ++)
        {
            pt_nfy_tag->apv_cb_addr_ex[z_i] = apv_cb_addr_ex[z_i];
        }
    }

    return pt_nfy_tag;
}


EXT_RPC_CB_NFY_TAG_T * ri_create_ext_cb_tag(
    RPC_ID_T t_rpc_id,
    VOID *   apv_cb_addr_ex[],
    SIZE_T   z_num,
    VOID *   pv_tag,
    UINT32    ui4_pb_handle)
{
    EXT_RPC_CB_NFY_TAG_T *   pt_nfy_tag;

    pt_nfy_tag = (EXT_RPC_CB_NFY_TAG_T *)malloc(sizeof(EXT_RPC_CB_NFY_TAG_T));
    if(pt_nfy_tag == NULL)
    {
        printf("<Server>alloc memory for tag error\n");

        return NULL;
    }
    else
    {
        printf("<Server>alloc memory for tag succeed: 0x%lx\n", (INT32)pt_nfy_tag);
    }

    pt_nfy_tag->t_id        = t_rpc_id;
    pt_nfy_tag->pv_tag      = pv_tag;
    pt_nfy_tag->ui4_pb_handle        = ui4_pb_handle;

    if(z_num == 1)
    {
        pt_nfy_tag->pv_cb_addr  = apv_cb_addr_ex[0];
    }
    else if(z_num == 0)
    {
        //do nothing
    }
    else
    {
        SIZE_T z_i;
        for(z_i = 0; z_i < z_num; z_i ++)
        {
            pt_nfy_tag->apv_cb_addr_ex[z_i] = apv_cb_addr_ex[z_i];
        }
    }

    return pt_nfy_tag;
}


EXPORT_SYMBOL VOID ri_free_cb_tag(RPC_CB_NFY_TAG_T *   pt_nfy_tag)
{
    free(pt_nfy_tag);
}


VOID ri_free_ext_cb_tag(EXT_RPC_CB_NFY_TAG_T *   pt_ext_nfy_tag)
{
    free(pt_ext_nfy_tag);
}

EXPORT_SYMBOL INT32 c_rpc_server_init(VOID)
{
    printf("c_rpc_server_init is called\n");

    //OS_FNCT_T t_of = {_thread_create};

    bt_rpc_init(NULL);

    return RPCR_OK;
}


RPC_ID_T c_rpc_start_server(VOID)
{
    printf("YZ c_rpc_start_server is called\n");

    return bt_rpc_open_server("mtkpbctrl"" "RPC_KW_LOG_FUNCTION" "RPC_KW_LOG_LEVEL, bt_rpcu_default_output_log, 15);
    //return rpc_open_server("mtkpbctrl");
}

RPC_ID_T c_rpc_start_snd_server(VOID)
{
    printf("c_rpc_start_snd_server is called\n");

    return bt_rpc_open_server("mtkpbsnd");
}

RPC_ID_T c_rpc_start_misc_server(VOID)
{
    printf("c_rpc_start_misc_server is called\n");

    return bt_rpc_open_server("mtkpbmisc");
}


