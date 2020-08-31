#!/bin/sh

CURR_DIR=${1}

mkdir -p ${CURR_DIR}/build
cd ${CURR_DIR}/build
cmake ..
make

# echo "/usr/bin/adb -s 0123456789ABCDEF push ./mgbox-cyber-app /usr/bin/mgbox-cyber-app"
#/usr/bin/adb -s 0123456789ABCDEF push ./mgbox-cyber-app /usr/bin/mgbox-cyber-app
#/usr/bin/adb -s 0123456789ABCDEF push ../mgbox-app/database/mgbox-cyber-database.db /media/sda1/
#/usr/bin/adb -s 0123456789ABCDEF shell sync

echo "/usr/bin/adb push ./dvir-hello /usr/bin/quec_launcher"
/usr/bin/adb shell mount -o remount,rw /dev/mmcblk0p21 /
/usr/bin/adb shell systemctl stop quec_launcher.service

/usr/bin/adb push ./dvir-hello /usr/bin/quec_launcher
/usr/bin/adb shell sync
/usr/bin/adb shell systemctl restart quec_launcher.service
