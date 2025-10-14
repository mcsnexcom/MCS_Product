#!/bin/bash

RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
NC='\033[0m' # No Color
COLOR=''

FUN_PASS=0
FUN_FAIL=1
RESULT=$FUN_PASS

USER="`logname`"
# if the user is not root, there is not point in going forward
THISUSER="`whoami`"

PRODUCT=$(tr -d '\0' < /proc/device-tree/product)
CHK_PRODUCT="ATC3750-8M"

_CAMERA=""
MODULES_DIR="/usr/lib/modules/`uname -r`/updates"
DRIVER="/nexcom/camera/.driver"

EXTLINUX_CONF="/boot/extlinux/extlinux.conf"


OVERLAY_FILE=""
_OVERLAY_FILE="OVERLAYS /boot/tegra234-p3737-camera-overlay_ecam_%s.dtbo"
CAMERA_OVERLAY_FILES=( "N/A" "ar0233_four_lane" "ar0234_four_lane" "isx031_wide_angle" )

CHK_USER(){
	if [ "x$THISUSER" != "xroot" ]; then
		echo -e "${RED}This script requires root privilege.${NC}"
    		exit $FUN_FAIL
	fi
	return $FUN_PASS
}

CHK_SHUT_DOWN(){
	echo -ne "${YELLOW}WARNING!! Relpace gmsl2 camera need power-off, shut down system now? (y/N)${NC}"
	read -p "" YN
	if [ "${YN^^}" = "Y" ]; then
		echo -e "${GREEN}shut down system...${NC}"
		sleep 1
		shutdown -h now

	elif [ "${YN^^}" = "N" ]; then
		echo -e "${YELLOW}Manually shut down by user!${NC}"
	else
		echo -e "${RED}Invalid input!!${NC}"
		exit
	fi
	return $FUN_PASS
}

MENU(){	
	echo -e "${RED}***************************************************************${NC}"
	echo -e "${RED}*            DO NOT use Ctrl+C to stop this script            *${NC}"
	echo -e "${RED}*                 (Input '0' to exit script)                  *${NC}"
	echo -e "${RED}***************************************************************${NC}"
	echo -e "${RED}*                                                             *${NC}"
	echo -e "${RED}* [1]:'STURDeCAM21'   [2]:'STURDeCAM25'   [3]:'STURDeCAM31'   *${NC}"
	echo -e "${RED}*                                                             *${NC}"
	echo -e "${RED}***************************************************************${NC}"
	echo 
	echo -en "${GREEN}Which camera are you currently using?:${NC}"
	read -p "" _CAMERA
	if [[ "$_CAMERA" =~ ^[0-9]+$ ]]; then
		if [ $_CAMERA -eq 0 ]; then
			echo -e "${RED}exit${NC}"
			exit
		else
			OVERLAY_FILE="`printf "${_OVERLAY_FILE}" "${CAMERA_OVERLAY_FILES[${_CAMERA}]}"`"
		fi
	else
		echo -e "${RED}Invalid input!!${NC}"
		return $FUN_FAIL
	fi
	return $FUN_PASS
}

REPLACE_DTBO(){
	local linux_num;
	local camera_overlay_num;
	if [ -f $EXTLINUX_CONF ]; then
		# Delete OVERLAYS lines if exist
        	sed -i "/.*OVERLAYS/d" "${EXTLINUX_CONF}"	
                sed -i "/^[ \t]*APPEND/a\      ${OVERLAY_FILE}" "${EXTLINUX_CONF}"
                sed -i "/^#.*APPEND/a\#    ${OVERLAY_FILE}" "${EXTLINUX_CONF}"
		linux_num="$(grep -c "LINUX .*$" "${EXTLINUX_CONF}")"
                camera_overlay_num="$(grep -c "OVERLAYS .*$" "${EXTLINUX_CONF}")"
		if [ "$camera_overlay_num" = "${linux_num}" ]; then
                        echo -e "${GREEN}Setting \"${OVERLAY_FILE}\" successfully in the extlinux.conf.${NC}"
			return $FUN_PASS
                else
                        echo -n -e "${RED}Setting \"${OVERLAY_FILE}\" in the extlinux.conf failed!${NC}"
			return $FUN_FAIL
                fi
	fi
	return $FUN_FAIL
}

REPLACE_DRIVER(){
	if [ -e ${DRIVER} ]; then
		echo -e "${YELLOW}Update driver...${NC}"
		if [[ ${CAMERA_OVERLAY_FILES[${_CAMERA}]} =~ ar0233 ]]; then	
			CAM_MODEL="STURDeCAM21"
			CAM_DRIVER="ecam_yuv_gmsl.ko"
		else # ar0234, isx031
			CAM_MODEL="STURDeCAM25_31"
			CAM_DRIVER="ecam_gmsl_yuv_common.ko"
		fi
		cp -af "${DRIVER}/${CAM_MODEL}/max96712.ko" "${MODULES_DIR}/drivers/media/i2c"
		cp -af "${DRIVER}/${CAM_MODEL}/tegra-camera.ko" "${MODULES_DIR}/drivers/media/platform/tegra/camera"
		cp -af "${DRIVER}/${CAM_MODEL}/nvhost-nvcsi-t194.ko" "${MODULES_DIR}/drivers/video/tegra/host/nvcsi"
		if [ "`find ${MODULES_DIR} -name "ecam*" | wc -l`" -gt 0 ]; then
                        rm -rf ${MODULES_DIR}/ecam*.ko
                fi
		cp -af "${DRIVER}/${CAM_MODEL}/${CAM_DRIVER}" "${MODULES_DIR}"
		depmod -a
	fi
}

# Main Start
CHK_USER
if [ $? -eq $FUN_PASS ]; then
	MENU
	if [ $? -eq $FUN_PASS ]; then
		REPLACE_DTBO
		if [ $? -eq $FUN_PASS ]; then
			REPLACE_DRIVER
			if [ $? -eq $FUN_PASS ]; then
				CHK_SHUT_DOWN
			fi
		fi
	fi
fi

