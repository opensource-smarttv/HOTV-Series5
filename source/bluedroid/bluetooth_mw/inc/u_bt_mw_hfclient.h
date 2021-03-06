#ifndef _U_BT_MW_HFCLIENT_H_
#define _U_BT_MW_HFCLIENT_H_

#include "u_bt_mw_common.h"

#define HFCLIENT_OPERATOR_NAME_LEN 16
#define HFCLIENT_NUMBER_LEN 32

typedef enum
{
    BT_HFCLIENT_CONNECTION_STATE_DISCONNECTED = 0,
    BT_HFCLIENT_CONNECTION_STATE_CONNECTING,
    BT_HFCLIENT_CONNECTION_STATE_CONNECTED,
    BT_HFCLIENT_CONNECTION_STATE_SLC_CONNECTED,
    BT_HFCLIENT_CONNECTION_STATE_DISCONNECTING
} BT_HFCLIENT_CONNECTION_STATE_T;

typedef enum
{
    BT_HFCLIENT_AUDIO_STATE_DISCONNECTED = 0,
    BT_HFCLIENT_AUDIO_STATE_CONNECTING,
    BT_HFCLIENT_AUDIO_STATE_CONNECTED,
    BT_HFCLIENT_AUDIO_STATE_CONNECTED_MSBC,
} BT_HFCLIENT_AUDIO_STATE_T;

typedef enum
{
    BT_HFCLIENT_VR_STATE_STOPPED = 0,
    BT_HFCLIENT_VR_STATE_STARTED
} BT_HFCLIENT_VR_STATE_T;

typedef enum
{
    BT_HFCLIENT_VOLUME_TYPE_SPK = 0,
    BT_HFCLIENT_VOLUME_TYPE_MIC
} BT_HFCLIENT_VOLUME_TYPE_T;

typedef enum
{
    BT_HFCLIENT_NETWORK_STATE_NOT_AVAILABLE = 0,
    BT_HFCLIENT_NETWORK_STATE_AVAILABLE
} BT_HFCLIENT_NETWORK_STATE_T;

typedef enum
{
    BT_HFCLIENT_SERVICE_TYPE_HOME = 0,
    BT_HFCLIENT_SERVICE_TYPE_ROAMING
} BT_HFCLIENT_SERVICE_TYPE_T;

typedef enum
{
    BT_HFCLIENT_CALL_STATE_ACTIVE = 0,
    BT_HFCLIENT_CALL_STATE_HELD,
    BT_HFCLIENT_CALL_STATE_DIALING,
    BT_HFCLIENT_CALL_STATE_ALERTING,
    BT_HFCLIENT_CALL_STATE_INCOMING,
    BT_HFCLIENT_CALL_STATE_WAITING,
    BT_HFCLIENT_CALL_STATE_HELD_BY_RESP_HOLD,
} BT_HFCLIENT_CALL_STATE_T;

typedef enum
{
    BT_HFCLIENT_CALL_NO_CALLS_IN_PROGRESS = 0,
    BT_HFCLIENT_CALL_CALLS_IN_PROGRESS
} BT_HFCLIENT_CALL_T;

typedef enum
{
    BT_HFCLIENT_CALLSETUP_NONE = 0,
    BT_HFCLIENT_CALLSETUP_INCOMING,
    BT_HFCLIENT_CALLSETUP_OUTGOING,
    BT_HFCLIENT_CALLSETUP_ALERTING
} BT_HFCLIENT_CALLSETUP_T;

typedef enum
{
    BT_HFCLIENT_CALLHELD_NONE = 0,
    BT_HFCLIENT_CALLHELD_HOLD_AND_ACTIVE,
    BT_HFCLIENT_CALLHELD_HOLD,
} BT_HFCLIENT_CALLHELD_T;

typedef enum
{
    BT_HFCLIENT_RESP_AND_HOLD_HELD = 0,
    BT_HFCLIENT_RESP_AND_HOLD_ACCEPT,
    BT_HFCLIENT_RESP_AND_HOLD_REJECT,
} BT_HFCLIENT_RESP_AND_HOLD_T;

typedef enum
{
    BT_HFCLIENT_CALL_DIRECTION_OUTGOING = 0,
    BT_HFCLIENT_CALL_DIRECTION_INCOMING
} BT_HFCLIENT_CALL_DIRECTION_T;

typedef enum
{
    BT_HFCLIENT_CALL_MPTY_TYPE_SINGLE = 0,
    BT_HFCLIENT_CALL_MPTY_TYPE_MULTI
} BT_HFCLIENT_CALL_MPTY_TYPE_T;

typedef enum
{
    BT_HFCLIENT_CMD_COMPLETE_OK = 0,
    BT_HFCLIENT_CMD_COMPLETE_ERROR,
    BT_HFCLIENT_CMD_COMPLETE_ERROR_NO_CARRIER,
    BT_HFCLIENT_CMD_COMPLETE_ERROR_BUSY,
    BT_HFCLIENT_CMD_COMPLETE_ERROR_NO_ANSWER,
    BT_HFCLIENT_CMD_COMPLETE_ERROR_DELAYED,
    BT_HFCLIENT_CMD_COMPLETE_ERROR_BLACKLISTED,
    BT_HFCLIENT_CMD_COMPLETE_ERROR_CME
} BT_HFCLIENT_CMD_COMPLETE_TYPE_T;

typedef enum
{
    BT_HFCLIENT_CALL_ACTION_CHLD_0 = 0,
    BT_HFCLIENT_CALL_ACTION_CHLD_1,
    BT_HFCLIENT_CALL_ACTION_CHLD_2,
    BT_HFCLIENT_CALL_ACTION_CHLD_3,
    BT_HFCLIENT_CALL_ACTION_CHLD_4,
    BT_HFCLIENT_CALL_ACTION_CHLD_1x,
    BT_HFCLIENT_CALL_ACTION_CHLD_2x,
    BT_HFCLIENT_CALL_ACTION_ATA,
    BT_HFCLIENT_CALL_ACTION_CHUP,
    BT_HFCLIENT_CALL_ACTION_BTRH_0,
    BT_HFCLIENT_CALL_ACTION_BTRH_1,
    BT_HFCLIENT_CALL_ACTION_BTRH_2,
} BT_HFCLIENT_CALL_ACTION_T;

typedef enum
{
    BT_HFCLIENT_SERVICE_UNKNOWN = 0,
    BT_HFCLIENT_SERVICE_VOICE,
    BT_HFCLIENT_SERVICE_FAX
} BT_HFCLIENT_SUBSCRIBER_SERVICE_TYPE_T;

typedef enum
{
    BT_HFCLIENT_IN_BAND_RINGTONE_NOT_PROVIDED = 0,
    BT_HFCLIENT_IN_BAND_RINGTONE_PROVIDED,
} BT_HFCLIENT_IN_BAND_RING_STATE_T;

typedef struct
{
    int index;
    BT_HFCLIENT_CALL_DIRECTION_T dir;
    BT_HFCLIENT_CALL_STATE_T state;
    BT_HFCLIENT_CALL_MPTY_TYPE_T mpty;
    CHAR number[HFCLIENT_NUMBER_LEN + 1];
} BT_HFCLIENT_CURRENT_CALLS_T;

typedef struct
{
    BT_HFCLIENT_VOLUME_TYPE_T type;
    int volume;
} BT_HFCLIENT_VOLUME_CHANGE_T;

typedef struct
{
    BT_HFCLIENT_CMD_COMPLETE_TYPE_T type;
    int cme;
} BT_HFCLIENT_CMD_COMPLETE_T;

typedef struct
{
    CHAR number[HFCLIENT_NUMBER_LEN + 1];
    BT_HFCLIENT_SUBSCRIBER_SERVICE_TYPE_T type;
} BT_HFCLIENT_SUBSCRIBER_INFO_T;

#endif /*  _U_BT_MW_HFCLIENT_H_ */
