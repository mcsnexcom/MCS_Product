#!/bin/bash

THISUSER=`whoami`
FUN_PASS=0
FUN_FAIL=1
RESULT=$FUN_PASS
_VERSION=v3.6.0

main(){
# if the user is not root, there is not point in going forward
if [ "x$THISUSER" != "xroot" ]; then
    echo "This script requires root privilege"
    return $FUN_FAIL
fi

if [ ! -e rootfs/etc/image_version ]; then
        touch rootfs/etc/image_version
fi

#ATC3540 8G
VERSION="${_VERSION}_ORIN_NX_8G"
sed -i "1s/.*/${VERSION}/" rootfs/etc/image_version
#ATC3540_mfi_v1.0.0_ORIN_NX_8G.tar.gz

#offline mode
#package full (qspi + system.img)
sudo PACKAGE_NAME=ATC3540_mfi_${VERSION} BOARDID=3767 FAB=300 BOARDSKU=0001 BOARDREV=M.3 ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --external-device nvme0n1p1 -p "-c bootloader/t186ref/cfg/flash_t234_qspi.xml --no-systemimg" -c ./tools/kernel_flash/flash_l4t_external.xml --massflash 5 --showlogs --network usb0 atc3540-orinNX nvme0n1p1


# online mode
#read -p "--- Please check your SOM is Orin NX 8G ---   (y/N): " check
#if [[ "$check" != "y" ]]; then
#	echo "exit script"
#    	return $FUN_FAIL
#fi
#sudo PACKAGE_NAME=ATC3540_mfi_${VERSION} ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --external-device nvme0n1p1 -p "-c bootloader/t186ref/cfg/flash_t234_qspi.xml --no-systemimg" -c ./tools/kernel_flash/flash_l4t_external.xml --massflash 1 --showlogs --network usb0 atc3540-orinNX nvme0n1p1

RESULT=$(( RESULT | $? ))

#package qspi only
#sudo PACKAGE_NAME=ATC3540_mfi_${VERSION} BOARDID=3701 FAB=300 BOARDSKU=0000 BOARDREV=G.3 ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --massflash 1 atc3540-orinNX nvme0n1p1

#online mode
#package qspi only
#sudo PACKAGE_NAME=ATC3750_mfi_${VERSION}  ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --massflash 1 atc3540-orinNX nvme0n1p1

#ATC3540 16G
VERSION="${_VERSION}_ORIN_NX_16G"
sed -i "1s/.*/${VERSION}/" rootfs/etc/image_version
#ATC3540_mfi_v1.0.0_ORIN_NX_16G.tar.gz

#offline mode
sudo PACKAGE_NAME=ATC3540_mfi_${VERSION} BOARDID=3767 FAB=300 BOARDSKU=0000 BOARDREV=G.3 ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --external-device nvme0n1p1 -p "-c bootloader/t186ref/cfg/flash_t234_qspi.xml --no-systemimg" -c ./tools/kernel_flash/flash_l4t_external.xml --massflash 5 --showlogs --network usb0 atc3540-orinNX nvme0n1p1

# online mode
#read -p "--- Please check your SOM is Orin NX 16G ---   (y/N): " check
#if [[ "$check" != "y" ]]; then
#	echo "exit script"
#	return $FUN_FAIL
#fi
#sudo PACKAGE_NAME=ATC3540_mfi_${VERSION} ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --external-device nvme0n1p1 -p "-c bootloader/t186ref/cfg/flash_t234_qspi.xml --no-systemimg" -c ./tools/kernel_flash/flash_l4t_external.xml --massflash 1 --showlogs --network usb0 atc3540-orinNX nvme0n1p1

RESULT=$(( RESULT | $? ))

#package qspi only
#sudo PACKAGE_NAME=ATC3540_mfi_${VERSION} BOARDID=3767 FAB=300 BOARDSKU=0000 BOARDREV=G.3 ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --massflash 1 atc3540-orinNX nvme0n1p1

#online mode
#package qspi only
#sudo PACKAGE_NAME=ATC3750_mfi_${VERSION}  ./tools/kernel_flash/l4t_initrd_flash.sh --no-flash --massflash 1 atc3540-orinNX nvme0n1p1

return $RESULT
}

main
