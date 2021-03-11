# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein is
# confidential and proprietary to MediaTek Inc. and/or its licensors. Without
# the prior written permission of MediaTek inc. and/or its licensors, any
# reproduction, modification, use or disclosure of MediaTek Software, and
# information contained herein, in whole or in part, shall be strictly
# prohibited.

# MediaTek Inc. (C) 2010. All rights reserved.
#
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
# RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
# ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
# WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
# NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
# RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
# INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
# TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
# RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
# OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
# SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
# RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
# ENTIRE ANDCUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
# RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
# MEDIATEK SOFTWARE AT ISSUE,OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
# CHARGE PAID BY RECEIVER TOMEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
#
# The following software/firmware and/or related documentation ("MediaTek
# Software") have been modified by MediaTek Inc. All revisions are subject to
# any receiver's applicable license agreements with MediaTek Inc.

ifeq ($(MTK_BT_SUPPORT), yes)

LOCAL_PATH := $(call my-dir)

###########################################################################
# MTK BT MW SOLUTION
###########################################################################
include $(CLEAR_VARS)

MW_C_LIST := $(wildcard $(LOCAL_PATH)/*.c)
MW_C_LIST += $(wildcard $(LOCAL_PATH)/../../wrap/src/*.c)

LOCAL_SRC_FILES := $(MW_C_LIST:$(LOCAL_PATH)/%=%)

$(warning custom path $(MTK_PATH_CUSTOM))

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../../../config    \
        $(LOCAL_PATH)/../../../include    \
        $(LOCAL_PATH)/inc    \
        $(LOCAL_PATH)/../inc    \
        $(LOCAL_PATH)/../../wrap/inc

LOCAL_C_INCLUDES += $(LOCAL_PATH)/a2dp/snk/playback

LOCAL_MODULE := libbt-mw
LOCAL_STATIC_LIBRARIES := libbtmw_gap libbtmw_gatt libbtmw_hid libbtmw_spp libbtmw_avrcp libbtmw_a2dp libbtmw_a2dp_src libbtmw_a2dp_snk
LOCAL_SHARED_LIBRARIES := libbluetooth.default libaudio.a2dp.default
LOCAL_PRELINK_MODULE := false

ifeq ($(strip $(MTK_BLE_GGL_SETUP_SUPPORT)),yes)
LOCAL_CFLAGS += -DMTK_BLE_GGL_SETUP_SUPPORT
endif

include $(BUILD_SHARED_LIBRARY)
include $(call all-makefiles-under,$(LOCAL_PATH))
endif
