#!/bin/bash

if ! command -v dialog &>/dev/null; then
	echo "Error: dialog isn't installed. Please install it with 'sudo apt install dialog'"
	exit 1
fi

if [ "$EUID" -ne 0 ];then
	echo "Error: This script must be run with sudo." 
	exit 1
fi

VER="v2.0"
PRODUCT=$(tr -d '\0' < /proc/device-tree/product)

# Temp files
TEMP=$(mktemp -d)
CAMERA="${TEMP}/camera"
SHUTDOWN="${TEMP}/Shutdown"

# Drivers
MODULES="/usr/lib/modules/5.15.148-tegra"
DRIVER="/nexcom/camera/.driver"
APPRO="${DRIVER}/ApproPho"
ECON21="${DRIVER}/STURDeCAM21"
ECON25="${DRIVER}/STURDeCAM25"
ECON31="${DRIVER}/STURDeCAM31"
Leopard="${DRIVER}/Leopard_Hawk"
LeopardOWL="${DRIVER}/Leopard_Owl"
LI_HAWK_OWL="${DRIVER}/Leopard_Hawk_Owl"
LI_OWL_HAWK="${DRIVER}/Leopard_Owl_Hawk"

# Camera array
CAMERA_ARRAY_3562=("$ECON21" "$ECON25" "$ECON31" "$APPRO" "$Leopard" "$LeopardOWL")
CAMERA_ARRAY_3750=("$ECON21" "$ECON25" "$ECON31" "$APPRO" "$LI_HAWK_OWL" "$LI_OWL_HAWK")

# Dtb
CAMERA_DTB="nexcom_camera.dtbo"


trap CLEANUP EXIT

MENU() {
	# Camera options
	case $PRODUCT in
		ATC3562*)
			dialog  --no-shadow \
				--menu "[$VER]\n$PRODUCT Select Camera" 15 30 8 \
				1 "e-con Systems 21" \
				2 "e-con Systems 25" \
				3 "e-con Systems 31" \
				4 "ApproPho" \
				5 "Leopard Hawk" \
				6 "Leopard Owl" \
				2>"${CAMERA}"
			;;
		ATC3750-8M)
			dialog  --no-shadow \
				--menu "[$VER]\n$PRODUCT Select Camera" 15 35 8 \
				1 "e-con Systems 21" \
				2 "e-con Systems 25" \
				3 "e-con Systems 31" \
				4 "ApproPho" \
				5 "Leopard Hawk and Owl" \
				6 "Leopard Owl and Hawk" \
				2>"${CAMERA}"
			;;
		*)
			dialog --no-shadow --msgbox "Not on the support list" 8 40
			exit 1
			;;
	esac

	# Exit if no camera has been chosen
	if [  -z "$(cat ${CAMERA})" ];then
		dialog --no-shadow --msgbox "Choose no camera, exit now." 8 40
		exit 1
	fi

	# Shutdown option
	dialog --no-shadow \
		--yesno "Shutdown now to apply changes?" 8 40

	echo "$?" > "${SHUTDOWN}"	
}

APPLY() {
	camera=$(cat $CAMERA)
	camera=$((camera - 1))
	Shutdown_s=$(cat $SHUTDOWN)

	case $PRODUCT in
		ATC3562*)
			CAMERA_ARRAY=("${CAMERA_ARRAY_3562[@]}")
			;;
		ATC3750-8M)
			CAMERA_ARRAY=("${CAMERA_ARRAY_3750[@]}")
			;;
	esac
	
	(
		# Copy drivers
		echo 0
		cp -a "${CAMERA_ARRAY[$camera]}"/driver/* "${MODULES}"
		echo 50

		depmod -a
		echo 80

		# Copy dtb
		cp -a "${CAMERA_ARRAY[$camera]}"/dtb/* /boot/"${CAMERA_DTB}"
		echo 100
		sleep 1
	) | dialog --no-shadow --gauge "Processing..." 10 40 0

	# Shutdown system or not
	if [ "$Shutdown_s" -eq "0" ];then
		dialog --no-shadow --msgbox "Driver applied complete! \nShutdown system..." 8 40
		init 0
	else
		dialog --no-shadow --msgbox "Driver applied complete! \nRemember shutdown system to apply changes." 8 40
	fi
}

CLEANUP() {
	rm -rf ${TEMP}
	clear
}

MENU
APPLY
CLEANUP


