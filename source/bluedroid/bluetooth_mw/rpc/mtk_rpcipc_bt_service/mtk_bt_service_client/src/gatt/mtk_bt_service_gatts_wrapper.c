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

/*-----------------------------------------------------------------------------
                        include files
-----------------------------------------------------------------------------*/
#include <stdio.h>

#include "mtk_bt_service_gatts_wrapper.h"
#include "mtk_bt_service_gatt_ipcrpc_struct.h"
#include "client_common.h"
#include "ri_common.h"

#define BT_RW_LOG(_stmt...) \
        do{ \
            if(0){    \
                printf("[Client]Func:%s Line:%d--->: ", __FUNCTION__, __LINE__);   \
                printf(_stmt); \
                printf("\n"); \
            }        \
        }   \
        while(0)

static INT32 _hndlr_bt_app_gatts_event_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{
    BT_RW_LOG("bt_app_gatts_event_cbk, pv_cb_addr = %p", pv_cb_addr);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSEventCbk)pv_cb_addr)((BT_GATTS_EVENT_T)pt_args[0].u.i4_arg, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_reg_server_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_reg_server_cbk, pv_cb_addr = %p, pt_args[0].u.pv_desc = %p", pv_cb_addr, pt_args[0].u.pv_desc);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSRegServerCbk)pv_cb_addr)((BT_GATTS_REG_SERVER_RST_T *)pt_args[0].u.pv_desc, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_add_srvc_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_add_srvc_cbk, pv_cb_addr = %p, pt_args[0].u.pv_desc = %p", pv_cb_addr, pt_args[0].u.pv_desc);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSAddSrvcCbk)pv_cb_addr)((BT_GATTS_ADD_SRVC_RST_T *)pt_args[0].u.pv_desc, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_add_incl_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_add_incl_cbk, pv_cb_addr = %p, pt_args[0].u.pv_desc = %p", pv_cb_addr, pt_args[0].u.pv_desc);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSAddInclCbk)pv_cb_addr)((BT_GATTS_ADD_INCL_RST_T *)pt_args[0].u.pv_desc, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_add_char_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_add_char_cbk, pv_cb_addr = %p, pt_args[0].u.pv_desc = %p", pv_cb_addr, pt_args[0].u.pv_desc);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSAddCharCbk)pv_cb_addr)((BT_GATTS_ADD_CHAR_RST_T *)pt_args[0].u.pv_desc, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_add_desc_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_add_desc_cbk, pv_cb_addr = %p, pt_args[0].u.pv_desc = %p", pv_cb_addr, pt_args[0].u.pv_desc);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSAddDescCbk)pv_cb_addr)((BT_GATTS_ADD_DESCR_RST_T *)pt_args[0].u.pv_desc, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_op_srvc_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_op_srvc_cbk, pv_cb_addr = %p, pt_args[0].u.i4_arg = %ld, pt_args[1].u.pv_desc = %p",
               pv_cb_addr, pt_args[0].u.i4_arg, pt_args[1].u.pv_desc);

    if(ui4_num_args != 3)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSOpSrvcCbk)pv_cb_addr)((BT_GATTS_SRVC_OP_TYPE_T)pt_args[0].u.i4_arg,
                                                (BT_GATTS_SRVC_RST_T *)pt_args[1].u.pv_desc, pt_args[2].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_req_read_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_req_read_cbk, pv_cb_addr = %p, pt_args[0].u.pv_desc = %p",
               pv_cb_addr, pt_args[0].u.pv_desc);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSReqReadCbk)pv_cb_addr)((BT_GATTS_REQ_READ_RST_T *)pt_args[0].u.pv_desc, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_req_write_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_req_write_cbk, pv_cb_addr = %p, pt_args[0].u.pv_desc = %p",
               pv_cb_addr, pt_args[0].u.pv_desc);

    if(ui4_num_args != 2)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSReqWriteCbk)pv_cb_addr)((BT_GATTS_REQ_WRITE_RST_T *)pt_args[0].u.pv_desc, pt_args[1].u.pv_arg);
    return RPCR_OK;
}

static INT32 _hndlr_bt_app_gatts_ind_sent_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    void          *pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{

    BT_RW_LOG("bt_app_gatts_ind_sent_cbk, pv_cb_addr = %p, pt_args[0].u.i4_arg = %ld, pt_args[1].u.i4_arg = %ld",
               pv_cb_addr, pt_args[0].u.i4_arg, pt_args[1].u.i4_arg);

    if(ui4_num_args != 3)
    {
        return RPCR_INV_ARGS;
    }
    pt_return->e_type   = ARG_TYPE_VOID;

    ((mtkrpcapi_BtAppGATTSIndSentCbk)pv_cb_addr)(pt_args[0].u.i4_arg, pt_args[1].u.i4_arg, pt_args[2].u.pv_arg);
    return RPCR_OK;
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_base_init(MTKRPCAPI_BT_APP_GATTS_CB_FUNC_T *func, void* pv_tag)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_base_init");
    RPC_CLIENT_DECL(2, INT32);
    RPC_CLIENT_CHECK(bt_rpc_add_ref_desc(RPC_DEFAULT_ID,
                    func,
                    RPC_DESC_MTKRPCAPI_BT_APP_GATTS_CB_FUNC_T,
                    NULL));
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_DESC, func);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_VOID, pv_tag);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_base_init");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_register_server(char * app_uuid)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_register_server");
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, app_uuid);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_register_server");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}
EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_unregister_server(INT32 server_if)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_unregister_server");
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_unregister_server");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_open(INT32 server_if, CHAR *bt_addr,
                                                UINT8 is_direct, INT32 transport)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_open");
    RPC_CLIENT_DECL(4, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, bt_addr);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT8, is_direct);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, transport);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_open");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_close(INT32 server_if, CHAR *bt_addr, INT32 conn_id)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_close");
    RPC_CLIENT_DECL(3, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, bt_addr);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, conn_id);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_close");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_add_service(INT32 server_if, CHAR *service_uuid,
                                                       UINT8 is_primary, INT32 number)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_add_service");
    RPC_CLIENT_DECL(4, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT8, is_primary);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, number);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_add_service");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_add_included_service(INT32 server_if, INT32 service_handle,
                                                                  INT32 included_handle)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_add_included_service");
    RPC_CLIENT_DECL(3, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, service_handle);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, included_handle);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_add_included_service");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_add_char(INT32 server_if, INT32 service_handle,
                                                    CHAR *uuid, INT32 properties, INT32 permissions)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_add_char");
    RPC_CLIENT_DECL(5, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, service_handle);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, properties);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, permissions);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_add_char");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_add_desc(INT32 server_if, INT32 service_handle,
                                                     CHAR *uuid, INT32 permissions)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_add_desc");
    RPC_CLIENT_DECL(4, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, service_handle);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, permissions);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_add_desc");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_start_service(INT32 server_if, INT32 service_handle, INT32 transport)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_start_service");
    RPC_CLIENT_DECL(3, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, service_handle);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, transport);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_start_service");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_stop_service(INT32 server_if, INT32 service_handle)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_stop_service");
    RPC_CLIENT_DECL(2, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, service_handle);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_stop_service");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_delete_service(INT32 server_if, INT32 service_handle)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_delete_service");
    RPC_CLIENT_DECL(2, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, service_handle);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_delete_service");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_send_indication(INT32 server_if, INT32 attribute_handle,
                                                            INT32 conn_id, INT32 fg_confirm,
                                                            CHAR *p_value, INT32 value_len)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_send_indication");
    RPC_CLIENT_DECL(6, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, server_if);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, attribute_handle);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, conn_id);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, fg_confirm);
    //RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, p_value);
    RPC_CLIENT_CHECK(bt_rpc_add_ref_buff(RPC_DEFAULT_ID, p_value, value_len));
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_DESC, p_value);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, value_len);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_send_indication");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_send_response(INT32 conn_id, INT32 trans_id,
                                                           INT32 status, INT32 handle,
                                                           CHAR *p_value, INT32 value_len,
                                                           INT32 auth_req)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_send_response");
    RPC_CLIENT_DECL(7, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, conn_id);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, trans_id);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, status);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, handle);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, p_value);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, value_len);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, auth_req);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_send_response");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL VOID a_mtkapi_bt_gatts_get_connect_result_info(BT_GATTS_CONNECT_RST_T *connect_rst_info)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_get_connect_result_info");
    RPC_CLIENT_DECL_VOID(1);
    RPC_CLIENT_CHECK(bt_rpc_add_ref_desc(RPC_DEFAULT_ID,
                    connect_rst_info,
                    RPC_DESC_BT_GATTS_CONNECT_RST_T,
                    NULL));

    RPC_CLIENT_ARG_IO(ARG_TYPE_REF_DESC, connect_rst_info);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_get_connect_result_info");
    RPC_RETURN_VOID;
}

EXPORT_SYMBOL VOID a_mtkapi_bt_gatts_get_disconnect_result_info(BT_GATTS_CONNECT_RST_T *disconnect_rst_info)
{
    BT_RW_LOG("a_mtkapi_bt_gatts_get_disconnect_result_info");
    RPC_CLIENT_DECL_VOID(1);
    RPC_CLIENT_CHECK(bt_rpc_add_ref_desc(RPC_DEFAULT_ID,
                    disconnect_rst_info,
                    RPC_DESC_BT_GATTS_CONNECT_RST_T,
                    NULL));

    RPC_CLIENT_ARG_IO(ARG_TYPE_REF_DESC, disconnect_rst_info);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_get_disconnect_result_info");
    RPC_RETURN_VOID;
}

#if MTK_BLE_GGL_SETUP_SUPPORT
EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_initialize(void)
{
    //Adding a invalid value for passing IPC/RPC, no other use
    INT32 i4_InvalidValue = 0;
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, i4_InvalidValue);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_initialize");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_finalize(void)
{
    BT_RW_LOG("finalize");
    //Adding a invalid value for passing IPC/RPC, no other use
    INT32 i4_InvalidValue = 0;
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, i4_InvalidValue);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_finalize");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_isSupported(void)
{
    BT_RW_LOG("isSupported");
    //Adding a invalid value for passing IPC/RPC, no other use
    INT32 i4_InvalidValue = 0;
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, i4_InvalidValue);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_isSupported");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_setDelegate(INT32 delegate)
{
    BT_RW_LOG("delegate = %ld", delegate);
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_INT32, delegate);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_setDelegate");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_onCharacteristicWrite(char * service_uuid, char * char_uuid, char * value)
{
    BT_RW_LOG("service_uuid = %s, char_uuid = %s, value = %s", service_uuid, char_uuid, value);
    RPC_CLIENT_DECL(3, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, char_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, value);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_onCharacteristicWrite");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_createService(char * service_uuid)
{
    BT_RW_LOG("service_uuid = %s", service_uuid);
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_createService");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_destroyService(char * service_uuid)
{
    BT_RW_LOG("service_uuid = %s", service_uuid);
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_destroyService");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_startService(char * service_uuid)
{
    BT_RW_LOG("service_uuid = %s", service_uuid);
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_startService");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_stopService(char* service_uuid)
{
    BT_RW_LOG("service_uuid = %s", service_uuid);
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_stopService");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_setDeviceName(char * name)
{
    BT_RW_LOG("name = %s", name);
    RPC_CLIENT_DECL(1, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, name);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_setDeviceName");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_setAdvertisement(char * service_uuid, char ** advertised_uuids, UINT32 advertised_uuids_num, char * advertise_data, const char * manufacturer_data, bool transmit_name)
{
    BT_RW_LOG("service_uuid = %s, advertised_uuids_num = %ld, advertise_data = %s, manufacturer_data = %s, transmit_name = %d",
            service_uuid, advertised_uuids_num, advertise_data, manufacturer_data, transmit_name);
    UINT32 index = 0;

    RPC_CLIENT_DECL(16, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, advertise_data);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, manufacturer_data);
    RPC_CLIENT_ARG_INP(ARG_TYPE_BOOL, transmit_name);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, advertised_uuids_num);
    for (index = 0; index < advertised_uuids_num; index++)
    {
        BT_RW_LOG("advertised_uuids[%ld] = %s", index, advertised_uuids[index]);
        RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, advertised_uuids[index]);
    }

    for (index = 5 + advertised_uuids_num; index < 16; index++)
    {
        RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, index);
    }

    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_setAdvertisement");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_setScanResponse(char * service_uuid, char ** advertised_uuids, UINT32 advertised_uuids_num, char * advertise_data, char * manufacturer_data, bool transmit_name)
{
    BT_RW_LOG("service_uuid = %s, advertised_uuids_num = %ld, advertise_data = %s, manufacturer_data = %s, transmit_name = %d",
            service_uuid, advertised_uuids_num, advertise_data, manufacturer_data, transmit_name);
    UINT32 index = 0;

    RPC_CLIENT_DECL(16, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, advertise_data);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, manufacturer_data);
    RPC_CLIENT_ARG_INP(ARG_TYPE_BOOL, transmit_name);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, advertised_uuids_num);
    for (index = 0; index < advertised_uuids_num; index++)
    {
        BT_RW_LOG("advertised_uuids[%ld] = %s", index, advertised_uuids[index]);
        RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, advertised_uuids[index]);
    }

    for (index = 5 + advertised_uuids_num; index < 16; index++)
    {
        RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, index);
    }

    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_setScanResponse");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_addCharacteristic(char * service_uuid, char * attribute_uuid,
                                                              char * control_uuid, char ** options, UINT32 options_num)
{
    if ((NULL == service_uuid) || (NULL == attribute_uuid) || (NULL == control_uuid) || (NULL == options))
    {
        BT_RW_LOG("Ptr is null\n");
        return -1;
    }

    BT_RW_LOG("service_uuid = %s, attribute_uuid = %s, control_uuid = %s, options_num = %ld",
            service_uuid, attribute_uuid, control_uuid, options_num);
    UINT32 index = 0;

    RPC_CLIENT_DECL(16, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, attribute_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, control_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, options_num);
    for (index = 0; index < options_num; index++)
    {
        BT_RW_LOG("options[%ld] = %s", index, options[index]);
        RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, options[index]);
    }

    for (index = 4 + options_num; index < 16; index++)
    {
        RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, index);
    }

    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_addCharacteristic");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}

EXPORT_SYMBOL INT32 a_mtkapi_bt_gatts_setCharacteristicValue(char * service_uuid, char * attribute_uuid,
                                                                   void * value, UINT32 length,
                                                                   UINT32 max_length, UINT32 flag)
{
    BT_RW_LOG("service_uuid = %s, attribute_uuid = %s, value = %p, length = %ld, max_length = %ld, flag = %ld",
            service_uuid, attribute_uuid, value, length, max_length, flag);

    if (length > 512)
    {
        length = 512;
        BT_RW_LOG("length = %ld", length);
    }
    RPC_CLIENT_DECL(6, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, service_uuid);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_STR, attribute_uuid);
    RPC_CLIENT_CHECK(bt_rpc_add_ref_buff(RPC_DEFAULT_ID, value, length));
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_DESC, value);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, length);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, max_length);
    RPC_CLIENT_ARG_INP(ARG_TYPE_UINT32, flag);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatts_setCharacteristicValue");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}
#endif

static INT32 _hndlr_bt_app_gatt_nfy_fct_cbk(
    RPC_ID_T     t_rpc_id,
    const CHAR*  ps_cb_type,
    VOID *       pv_cb_addr,
    UINT32       ui4_num_args,
    ARG_DESC_T*  pt_args,
    ARG_DESC_T*  pt_return)
{
    BT_RW_LOG("gatt_nfy_fct, arg_1 = %s, arg_2 = %s, arg_3 = %s, pv_cb_addr = %p", pt_args[0].u.pc_arg,pt_args[1].u.pc_arg,pt_args[2].u.pc_arg,pv_cb_addr);

    pt_return->e_type = ARG_TYPE_VOID;
    ((a_mtkapi_bt_gatt_nfy_fct_cbk)pv_cb_addr)(
                              pt_args[0].u.pc_arg,
                              pt_args[1].u.pc_arg,
                              pt_args[2].u.pc_arg,
                              pt_args[3].u.pv_arg);

    return RPCR_OK;
}

#if MTK_BLE_GGL_SETUP_SUPPORT
EXPORT_SYMBOL INT32 a_mtkapi_bt_gatt_reg_nfy_fct(a_mtkapi_bt_gatt_nfy_fct_cbk pf_nfy, void* pv_tag)
{
    BT_RW_LOG("reg_nfy_fct, pf_nfy = %p", pf_nfy);
    RPC_CLIENT_DECL(2, INT32);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_FUNC, pf_nfy);
    RPC_CLIENT_ARG_INP(ARG_TYPE_REF_VOID, pv_tag);
    RPC_BT_SERVICE_CLIENT_DO_OP("x_mtkapi_bt_gatt_reg_nfy_fct");
    RPC_CLIENT_RETURN(ARG_TYPE_INT32, -1);
}
#endif

INT32 c_rpc_reg_mtk_bt_service_gatts_cb_hndlrs(void)
{
    int i4_ret = 0;
    RPC_REG_CB_HNDLR(bt_app_gatts_event_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_reg_server_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_add_srvc_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_add_incl_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_add_char_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_add_desc_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_op_srvc_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_req_read_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_req_write_cbk);
    RPC_REG_CB_HNDLR(bt_app_gatts_ind_sent_cbk);
    return RPCR_OK;
}

INT32 c_rpc_reg_mtk_ble_setup_cb_hndlrs(void)
{
    int i4_ret = 0;
    RPC_REG_CB_HNDLR(bt_app_gatt_nfy_fct_cbk);
    return RPCR_OK;
}



