#!/bin/bash

THISUSER=`whoami`
if [ "x$THISUSER" != "xroot" ]; then
    echo "This script requires root privilege"
    exit 1
fi

DISK=$(df / | awk '{print $4}' | tail -n1)

if [[ $(($DISK/1024/1024)) -le 10 ]]; then
    echo "DISK space not enough!"
    exit 1
fi

apt update
#apt-mark hold nvidia-l4t-kernel nvidia-l4t-kernel-dtbs nvidia-l4t-kernel-headers
apt install -y nvidia-jetpack
#apt install -y nvidia-cuda nvidia-opencv nvidia-cudnn8 nvidia-tensorrt nvidia-visionworks nvidia-container nvidia-vpi

DS_VER="`apt-cache search deepstream  | grep -oE "deepstream-[0-9].{2,3}"`"

if [ $? -eq 0 ]; then
	read -p "Do you want to install ${DS_VER}? (y/n) " ANS
	if [[ "$ANS" == [yY] ]]; then
		apt install -y ${DS_VER}
	fi
fi
