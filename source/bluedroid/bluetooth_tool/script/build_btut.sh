
##############################################################################################
if [ ! $CC ]; then
    CC=/mtkoss/gnuarm/neon_4.8.2_2.6.35_cortex-a9-ubuntu/i686/bin/armv7a-mediatek482_001_neon-linux-gnueabi-gcc
    echo "single build?"
    echo "please asure the build environment correctly setting"
    echo $CC
fi
if [ ! $CXX ]; then
    CXX=/mtkoss/gnuarm/neon_4.8.2_2.6.35_cortex-a9-ubuntu/i686/bin/armv7a-mediatek482_001_neon-linux-gnueabi-g++
fi
if [ ! $Script_Dir ]; then
    Script_Dir=$(pwd)
    echo $Script_Dir
    if [[ $(pwd) =~ "script/common" ]]; then
        Bluetooth_Tool_Dir=${Script_Dir}/../..
    else
        Bluetooth_Tool_Dir=${Script_Dir}/..
    fi
fi
if [ ! $Bluetooth_Stack_Dir ]; then
    Bluetooth_Stack_Dir=${Bluetooth_Tool_Dir}/../bluetooth_stack
fi
if [ ! $Bluetooth_Mw_Dir ]; then
    Bluetooth_Mw_Dir=${Bluetooth_Tool_Dir}/../bluetooth_mw
fi
if [ ! $Bluetooth_Vendor_Lib_Dir ]; then
    Bluetooth_Vendor_Lib_Dir=${Bluetooth_Tool_Dir}/vendor_lib
fi
if [ ! $Bluetooth_Prebuilts_Dir ]; then
    Bluetooth_Prebuilts_Dir=${Bluetooth_Tool_Dir}/prebuilts
fi
if [ ! $Bluedroid_Libs_Path ]; then
    Bluedroid_Libs_Path=${Bluetooth_Tool_Dir}/prebuilts/lib
fi
if [ ! $External_Libs_Path ]; then
    External_Libs_Path=${Bluetooth_Tool_Dir}/external_libs
fi

#stack config file path:bt_stack.conf,bt_did.conf
if [ ! $Conf_Path ]; then
    Conf_Path=/3rd_rw/bluedroid
fi
#stack record file path.
if [ ! $Cache_Path ]; then
    Cache_Path=/3rd_rw
fi
#mw record file path, should the same with stack record path.
if [ ! $Storage_Path ]; then
    Storage_Path=/3rd_rw
fi
#/tmp path
if [ ! $Tmp_Path ]; then
    Tmp_Path=/tmp
fi
#system library file path:libbluetooth.default.so...
if [ ! $Platform_Libs_Path ]; then
    Platform_Libs_Path=/system/lib
fi
##############################################################################################

Libhw_Include_Path=${Bluetooth_Tool_Dir}/libhardware/include
Core_Include_Path=${Bluetooth_Tool_Dir}/core/include
Btif_Include_Path=${Bluetooth_Stack_Dir}/btif/include
Stack_Include_Path=${Bluetooth_Stack_Dir}/stack/include
Utils_Include_Path=${Bluetooth_Stack_Dir}/utils/include
Mtk_Bt_Include_Path=${Bluetooth_Stack_Dir}/mediatek/include
if [ ! -f ${External_Libs_Path}/libz.so ]; then
    External_Libs_Path=${Bluetooth_Tool_Dir}/external_libs/local_lib
fi


cd ${Bluetooth_Tool_Dir}/btut

rm -rf out

gn gen out/Default/ --args="libhw_include_path=\"${Libhw_Include_Path}\" core_include_path=\"${Core_Include_Path}\" btif_include_path=\"${Btif_Include_Path}\" stack_include_path=\"${Stack_Include_Path}\" utils_include_path=\"${Utils_Include_Path}\" mtk_bt_include_path=\"${Mtk_Bt_Include_Path}\" bluedroid_libs_path=\"-L${Bluedroid_Libs_Path}\" external_libs_path=\"-L${External_Libs_Path}\"  cc=\"${CC}\" cxx=\"${CXX}\""
ninja -C out/Default all

cd ${Script_Dir}

if [ ! -d ${Bluetooth_Prebuilts_Dir}/bin ]; then
    mkdir -p ${Bluetooth_Prebuilts_Dir}/bin
fi

cd ${Script_Dir}


if [ -f ${Bluetooth_Tool_Dir}/btut/out/Default/btut ]; then
    cp ${Bluetooth_Tool_Dir}/btut/out/Default/btut ${Bluetooth_Prebuilts_Dir}/bin/
else
    exit 1
fi
