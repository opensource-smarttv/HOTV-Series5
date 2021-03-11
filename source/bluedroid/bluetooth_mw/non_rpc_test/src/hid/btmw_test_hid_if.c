#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "bluetooth.h"
#include "bt_hh.h"
#include "bt_mw_common.h"

#include "btmw_test_cli.h"
#include "btmw_test_debug.h"
#include "btmw_test_hid_if.h"
#include "c_bt_mw_hidh.h"

typedef unsigned char U8;
typedef unsigned short U16;
//extern void *btmw_test_gap_get_profile_interface(const char *profile_id);

static int btmw_test_hid_connect_int_handler(int argc, char *argv[]);
static int btmw_test_hid_disconnect_handler(int argc, char *argv[]);
static int btmw_test_hid_set_output_report_handler(int argc, char *argv[]);
static int btmw_test_hid_get_input_report_handler(int argc, char *argv[]);
static int btmw_test_hid_set_feature_report_handler(int argc, char *argv[]);
static int btmw_test_hid_get_feature_report_handler(int argc, char *argv[]);
static int btmw_test_hid_set_protocol_handler(int argc, char *argv[]);
static int btmw_test_hid_get_protocol_handler(int argc, char *argv[]);
static int btmw_test_hid_get_output_report_handler(int argc, char *argv[]);
static int btmw_test_hid_set_input_report_handler(int argc, char *argv[]);
#if defined(MTK_LINUX_HIDH_PTS_TEST) && (MTK_LINUX_HIDH_PTS_TEST == TRUE)
static int btmw_test_hid_virtual_unplug_cli(int argc, char *argv[]);
static int btmw_test_hid_send_data_cli(int argc, char *argv[]);
#endif
static int btmw_test_hid_get_hid_devlist_cli(int argc, char *argv[]);
static int btmw_test_hid_del_paired_one_cli (int argc, char *argv[]);
static int btmw_test_hid_del_paired_all_cli (int argc, char *argv[]);

#if 0
static void btmw_test_hid_connection_state_cb(bt_bdaddr_t *bd_addr, bthh_connection_state_t state)
{
    BTMW_TEST_Logd("[HID] %s()\n", __func__);
    switch (state)
    {
        case BTHH_CONN_STATE_CONNECTED:
            BTMW_TEST_Logi("[HID] Connection State : connected\n");
            break;
        case BTHH_CONN_STATE_CONNECTING:
            BTMW_TEST_Logi("[HID] Connection State : connecting\n");
            break;
        case BTHH_CONN_STATE_DISCONNECTED:
            BTMW_TEST_Logi("[HID] Connection State : disconnected\n");
            break;
        case BTHH_CONN_STATE_DISCONNECTING:
            BTMW_TEST_Logi("[HID] Connection State : disconnecting\n");
            break;
        default:
            BTMW_TEST_Logi("[HID] Connection State : '%d'\n", state);
    }
}

static void btmw_test_hid_virtual_unplug_cb(bt_bdaddr_t *bd_addr, bthh_status_t hh_status)
{
    BTMW_TEST_Logd("[HID] %s() state: %s(%d)\n", __func__, (hh_status == 0) ? "SUCCESS" : "FAILED", hh_status);
}

static void btmw_test_hid_info_cb(bt_bdaddr_t *bd_addr, bthh_hid_info_t hid_info)
{
    BTMW_TEST_Logd("[HID] %s() \n", __func__);
    BTMW_TEST_Logd("[HID] attr_mask = 0x%x\n", hid_info.attr_mask);
    BTMW_TEST_Logd("[HID] sub_class = 0x%x\n", hid_info.sub_class);
    BTMW_TEST_Logd("[HID] app_id = 0x%x\n", hid_info.app_id);
    BTMW_TEST_Logd("[HID] vendor_id = 0x%x\n", hid_info.vendor_id);
    BTMW_TEST_Logd("[HID] product_id = 0x%x\n", hid_info.product_id);
    BTMW_TEST_Logd("[HID] version = %d\n", hid_info.version);
    BTMW_TEST_Logd("[HID] ctry_code = %d\n", hid_info.ctry_code);
    BTMW_TEST_Logd("[HID] dl_len = %d\n", hid_info.dl_len);
    BTMW_TEST_Logd("[HID] dsc_list = %s\n", hid_info.dsc_list);
}

static void btmw_test_hid_protocol_mode_cb(bt_bdaddr_t *bd_addr, bthh_status_t hh_status, bthh_protocol_mode_t mode)
{
    BTMW_TEST_Logd("[HID] %s() state: %s\n", __func__, (hh_status == 0) ? "SUCCESS" : "FAILED");
    BTMW_TEST_Logi("[HID] mode = %s(%d)\n", (mode == BTHH_REPORT_MODE) ? "REPORT_MODE" : "BOOT_MODE", mode);
}

static void btmw_test_hid_idle_time_cb(bt_bdaddr_t *bd_addr, bthh_status_t hh_status, int idle_rate)
{
    BTMW_TEST_Logd("[HID] %s() state: %s\n", __func__, (hh_status == 0) ? "SUCCESS" : "FAILED");
}

static void btmw_test_hid_get_report_cb(bt_bdaddr_t *bd_addr, bthh_status_t hh_status, uint8_t* rpt_data, int rpt_size)
{
    BTMW_TEST_Logd("[HID] %s() state: %s\n", __func__, (hh_status == 0) ? "SUCCESS" : "FAILED");
    BTMW_TEST_Logi("Data Len = %d", rpt_size);

    BTMW_TEST_Logi("Data = 0x%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ",
                rpt_size>0?rpt_data[0]:0,
                rpt_size>1?rpt_data[1]:0,
                rpt_size>2?rpt_data[2]:0,
                rpt_size>3?rpt_data[3]:0,
                rpt_size>4?rpt_data[4]:0,
                rpt_size>5?rpt_data[5]:0,
                rpt_size>6?rpt_data[6]:0,
                rpt_size>7?rpt_data[7]:0,
                rpt_size>9?rpt_data[8]:0,
                rpt_size>10?rpt_data[9]:0,
                rpt_size>11?rpt_data[10]:0,
                rpt_size>12?rpt_data[11]:0,
                rpt_size>13?rpt_data[12]:0,
                rpt_size>14?rpt_data[13]:0,
                rpt_size>15?rpt_data[14]:0,
                rpt_size>16?rpt_data[15]:0);

    if (rpt_data[0] == 0)
    {
        BTMW_TEST_Logd("Report ID is NULL.Report ID cannot be NULL. Invalid HID report recieved \n");
    }
}

static bthh_interface_t *g_bt_hid_interface = NULL;
static bthh_callbacks_t g_bt_hid_callbacks =
{
    sizeof(bthh_callbacks_t),
    btmw_test_hid_connection_state_cb,
    btmw_test_hid_info_cb,
    btmw_test_hid_protocol_mode_cb,
    btmw_test_hid_idle_time_cb,
    btmw_test_hid_get_report_cb,
    btmw_test_hid_virtual_unplug_cb,
};

#endif
static BTMW_TEST_CLI btmw_test_hid_cli_commands[] =
{
    {"connect",             btmw_test_hid_connect_int_handler,        " = connect <addr>"},
    {"disconnect",          btmw_test_hid_disconnect_handler,         " = disconnect <addr>"},
    {"get_input_report",    btmw_test_hid_get_input_report_handler,   " = get input report <addr> <report id> <max buffer size>"},
    {"get_feature_report",  btmw_test_hid_get_feature_report_handler, " = get feature report <addr> <report id> <max buffer size>"},
    {"get_output_report",   btmw_test_hid_get_output_report_handler,  " = get output report <addr> <report id> <max buffer size>"},
    {"set_feature_report",  btmw_test_hid_set_feature_report_handler, " = set feature report <addr> <report data(hex)>"},
    {"set_output_report",   btmw_test_hid_set_output_report_handler,  " = set output report <addr> <report data(hex)>"},
    {"set_input_report",    btmw_test_hid_set_input_report_handler,   " = set input report <addr> <report data(hex)>"},
    {"set_protocol",        btmw_test_hid_set_protocol_handler,       " = set protocol <addr> <protocol(0:boot, 1:report)>"},
    {"get_protocol",        btmw_test_hid_get_protocol_handler,       " = get protocol <addr>"},
#if defined(MTK_LINUX_HIDH_PTS_TEST) && (MTK_LINUX_HIDH_PTS_TEST == TRUE)
    {"virtual_up",          btmw_test_hid_virtual_unplug_cli,         " = send virtual unplug request <addr>"},
    {"send_data",           btmw_test_hid_send_data_cli,              " = send data <addr> <data(hex)>"},
#endif
    {"get_history",         btmw_test_hid_get_hid_devlist_cli,        " = get history"},
    {"del_pair_one",        btmw_test_hid_del_paired_one_cli,         " = del one history <addr>"},
    {"del_pair_all",        btmw_test_hid_del_paired_all_cli,         " = del all history"},
    {NULL, NULL, NULL},
};

static int btmw_test_hid_connect_int_handler(int argc, char *argv[])
{
    CHAR *pbt_addr;
    if (argc != 1)
    {
        BTMW_TEST_Loge("[HID] Usage : connect ([addr])\n", __func__);
        return -1;
    }
    pbt_addr = argv[0];
    c_bt_hid_connect(pbt_addr);
    return 0;
}

static int btmw_test_hid_disconnect_handler(int argc, char *argv[])
{
    CHAR *pbt_addr;

    if (argc != 1)
    {
        BTMW_TEST_Loge("[HID] Usage : disconnect ([addr])\n", __func__);
        return -1;
    }
    pbt_addr = argv[0];
    c_bt_hid_disconnect(pbt_addr);
    return 0;
}

static int btmw_test_hid_set_input_report_handler(int argc, char *argv[])
{
    CHAR *pbt_addr;
    CHAR *report_data;
    if (argc != 2)
    {
        BTMW_TEST_Loge("[HID] Usage : set_output_report ([addr][report data(hex)])\n", __func__);
        return -1;
    }
    pbt_addr = argv[0];  /*bt address */
    report_data = argv[1];
    c_bt_hid_set_input_report(pbt_addr, report_data);
    return 0;
}

static int btmw_test_hid_set_output_report_handler(int argc, char *argv[])
{
    CHAR *pbt_addr;
    CHAR *report_data;

    if (argc != 2)
    {
        BTMW_TEST_Loge("[HID] Usage : set_output_report ([addr][report data(hex)])\n", __func__);
        return -1;
    }
    pbt_addr = argv[0];  /*bt address */
    report_data = argv[1];
    c_bt_hid_set_output_report(pbt_addr, report_data);
    return 0;
}

static int btmw_test_hid_get_output_report_handler(int argc, char *argv[])
{
    CHAR *pbt_addr;
    char *ptr1;
    char *ptr2;
    int reportId;
    int bufferSize;
    if (argc != 3)
    {
        BTMW_TEST_Loge("[HID] Usage : get_input_report ([addr][report id][max buffer size])\n", __func__);
        return -1;
    }

    pbt_addr = argv[0];  /* bluetooth address of remote device */
    ptr1 = argv[1];  /* report id*/
    ptr2 = argv[2];  /* buffer size */
    reportId = atoi(ptr1);
    bufferSize = atoi(ptr2);
    c_bt_hid_get_output_report(pbt_addr, reportId, bufferSize);
    return 0;
}

static int btmw_test_hid_get_input_report_handler(int argc, char *argv[])
{
    char *pbt_addr;
    char *ptr1;
    char *ptr2;
    int reportId;
    int bufferSize;
    if (argc != 3)
    {
        BTMW_TEST_Loge("[HID] Usage : get_input_report ([addr][report id][max buffer size])\n", __func__);
        return -1;
    }

    pbt_addr = argv[0];  /* bluetooth address of remote device */
    ptr1 = argv[1];  /* report id*/
    ptr2 = argv[2];  /* buffer size */
    reportId = atoi(ptr1);
    bufferSize = atoi(ptr2);
    c_bt_hid_get_input_report(pbt_addr, reportId, bufferSize);
    return 0;
}

static int btmw_test_hid_get_feature_report_handler(int argc, char *argv[])
{
    char *pbt_addr;
    int reportId;
    int bufferSize;

    BTMW_TEST_Logi("[HID] %s()\n", __func__);
    if (argc != 3)
    {
        BTMW_TEST_Loge("[HID] Usage : get_feature_report ([addr][report id][max buffer size])\n", __func__);
        return -1;
    }

    pbt_addr = argv[0];              /* bluetooth address of remote device */
    reportId = atoi(argv[1]); /* report id */
    bufferSize = atoi(argv[2]); /* max buffer size */
    c_bt_hid_get_feature_report(pbt_addr, reportId, bufferSize);
    return 0;
}
static int btmw_test_hid_set_protocol_handler(int argc, char *argv[])
{
    char *pbt_addr;
    int protocol_mode;
    BTMW_TEST_Logi("[HID] %s()\n", __func__);
    if (argc != 2)
    {
        BTMW_TEST_Loge("[HID] Usage : set_protocol ([addr][protocol, 1:boot protocol | 0:report protocol])\n", __func__);
        return -1;
    }
    pbt_addr = argv[0];                  /* bluetooth address of remote device */
    protocol_mode = atoi(argv[1]);  /* protocol mode ( 0:boot protocol, 1:report protocol)  */
    c_bt_hid_set_protocol(pbt_addr, protocol_mode);
    return 0;
}

static int btmw_test_hid_get_protocol_handler(int argc, char *argv[])
{
    char *pbt_addr;
    INT32 ret = 0;
    if (argc != 1)
    {
        BTMW_TEST_Loge("[HID] Usage : get_protocol ([addr])\n", __func__);
        return -1;
    }
    pbt_addr = argv[0];              /* bluetooth address of remote device */
    ret = c_bt_hid_get_protocol(pbt_addr);
    return ret;
}

static int btmw_test_hid_set_feature_report_handler(int argc, char *argv[])
{
    char *pbt_addr;
    CHAR *report_data;
    if (argc != 2)
    {
        BTMW_TEST_Loge("[HID] Usage : set_feature_report ([addr][report data(hex)])\n", __func__);
        return -1;
    }

    pbt_addr = argv[0];  /* bluetooth address of remote device */
    report_data = argv[1];
    c_bt_hid_set_feature_report(pbt_addr, report_data);
    return 0;
}

#if defined(MTK_LINUX_HIDH_PTS_TEST) && (MTK_LINUX_HIDH_PTS_TEST == TRUE)
static int btmw_test_hid_virtual_unplug_cli(int argc, char *argv[])
{
    CHAR *pbt_addr;
    INT32 ret = 0;
    if (1 != argc)
    {
        BTMW_TEST_Loge("[HID] Usage : virtual_unplug ([addr])\n", __func__);
        return -1;
    }
    pbt_addr = argv[0];  /* bluetooth address of remote device */
    ret = c_bt_hid_virtual_unplug(pbt_addr);
    return ret;
}

static int btmw_test_hid_send_data_cli(int argc, char *argv[])
{
    CHAR *pbt_addr;
    CHAR *psend_data;
    INT32 ret = 0;
    if (2 != argc)
    {
        BTMW_TEST_Loge("[HID] Usage : send_data ([addr][data(hex)])\n", __func__);
        return -1;

    }
    pbt_addr = argv[0];  /* bluetooth address of remote device */
    psend_data = argv[1];
    ret = c_bt_hid_send_data(pbt_addr, psend_data);
    return ret;
}
#endif

static int btmw_test_hid_get_hid_devlist_cli(int argc, char *argv[])
{
    //FUNC_ENTRY;
    BT_HID_TARGET_DEV_LIST pt_device_list;
    BT_HID_STATUS_STRUCT_LIST pt_device_status;
    UINT32 i = 0;
    UINT32 j = 0;/* j is for count device num */
    int i4_ret=0;
    memset(&pt_device_list, 0, sizeof(BT_HID_TARGET_DEV_LIST));
    memset(&pt_device_status, 0, sizeof(BT_HID_STATUS_STRUCT_LIST));
    i4_ret = c_btm_get_paired_hid_dev_list(&pt_device_list, &pt_device_status);

    BTMW_TEST_Logv("[all]BT_HID_TARGET_DEV_LIST: head_idx=%d\n", pt_device_list.head_idx);
    BTMW_TEST_Logv("[all]BT_HID_TARGET_DEV_LIST: dev_num=%d\n", pt_device_list.dev_num);
    BTMW_TEST_Logv("[all]i4_ret=%2x\n", i4_ret);

    BTMW_TEST_Logv("[all]BT_HID_STATUS_STRUCT_LIST: head_idx=%d\n", pt_device_status.head_idx);
    BTMW_TEST_Logv("[all]BT_HID_STATUS_STRUCT_LIST: dev_num=%d\n", pt_device_status.dev_num);

    i = pt_device_list.head_idx;
    BTMW_TEST_Logv("head_idx:%ld\n", i);
    while (j < pt_device_list.dev_num)
    {
        BTMW_TEST_Logv("device_list[%ld].bdAddr:%s device_list[%ld].name:%s device_list[%ld].cod:0x%02X\n",
                        i,
                        pt_device_list.device_list[i].bdAddr,
                        i,
                        pt_device_list.device_list[i].name,
                        i,
                        pt_device_list.device_list[i].cod
                       );
        BTMW_TEST_Logv("device_list[%ld].bdaddr:%s device_list[%ld].status:%d.\n",
                        i,
                        pt_device_status.device_list[i].bdAddr,
                        i,
                        pt_device_status.device_list[i].status
                       );
        i = (i + 1) % MAX_DEV_NUM;
        j++;
    }

    return 0;
}

static int btmw_test_hid_del_paired_one_cli (int argc, char *argv[])
{
    //FUNC_ENTRY;
    BT_TARGET_DEV_INFO pt_device_info;
    memset(&pt_device_info, 0, sizeof(BT_TARGET_DEV_INFO));
    BTMW_TEST_Logd("btmw_test_hid_del_paired_one_cli argc: %d\n", argc);
    if (1 == argc)
    {
        if (17 > strlen(argv[0]))
        {
            BTMW_TEST_Loge("mac length should be 17\n");
            return -1;
        }
        strncpy(pt_device_info.bdAddr, argv[0], 17);
        BTMW_TEST_Logd("pt_device_info.bdAddr: %s\n", pt_device_info.bdAddr);
    }
    c_btm_del_paired_hid_dev_one(&pt_device_info);
    return 0;
}

static int btmw_test_hid_del_paired_all_cli (int argc, char *argv[])
{
    //FUNC_ENTRY;

    c_btm_del_paired_hid_dev_all();
    return 0;
}


// For handling incoming commands from CLI.
int btmw_test_hid_cmd_handler(int argc, char **argv)
{
    BTMW_TEST_CLI *cmd, *match = NULL;
    int ret = 0;
    int count;

    count = 0;
    cmd = btmw_test_hid_cli_commands;

    while (cmd->cmd)
    {
        if (!strcmp(cmd->cmd, argv[0]))
        {
            match = cmd;
            count = 1;
            break;
        }
        cmd++;
    }

    if (count == 0)
    {
        btmw_test_print_cmd_help(BTMW_TEST_CMD_KEY_HID, btmw_test_hid_cli_commands);
        ret = -1;
    }
    else
    {
        match->handler(argc - 1, &argv[1]);
    }

    return ret;
}

int btmw_test_hid_init()
{
    int ret = 0;
    BTMW_TEST_MOD hid_mod = {0};

    // Register command to CLI
    hid_mod.mod_id = BTMW_TEST_MOD_HID;
    strncpy(hid_mod.cmd_key, BTMW_TEST_CMD_KEY_HID, sizeof(hid_mod.cmd_key));
    hid_mod.cmd_handler = btmw_test_hid_cmd_handler;
    hid_mod.cmd_tbl = btmw_test_hid_cli_commands;

    ret = btmw_test_register_mod(&hid_mod);
    BTMW_TEST_Logi("[HID] btmw_test_register_mod() returns: %d\n", ret);

    return ret;
}

int btmw_test_hid_deinit()
{
    return 0;
}
