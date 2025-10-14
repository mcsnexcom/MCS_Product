#!/bin/bash

display_usage() {
	echo -e "\nUsage: bash v4l2set.sh [video device] \n"
	echo -e "Example: bash v4l2set.sh /dev/video0 /dev/video1 /dev/video2 \n"
	}
# if less than one arguments supplied, display usage
	if [  $# -le 0 ]
	then
		display_usage
		exit 1
	fi 

#IFS=$'\n' read -r -d '' -a videoArray < <( ls /dev/video* && printf '\0' )
inputArray=( "$@" )

for videoX in "${inputArray[@]}"
do
	echo "setting..${videoX}"
	v4l2-ctl --stream-mmap --stream-count=10 -d $videoX  &
	sleep 2
	v4l2-ctl -d $videoX \
        --set-ctrl=power_line_frequency=0 \
        --set-ctrl=wdr_enable=1 \
        --set-ctrl=wdr_level=3 \
        --set-ctrl=digital_zoom=0 \
        --set-ctrl=pan=50 \
        --set-ctrl=tilt=50 \
        --set-ctrl=ae_max_shutter=4 \
        --set-ctrl=ae_max_gain=6 \
        --set-ctrl=awb_mode=0 \
        --set-ctrl=wb_manual_rgain=1024 \
        --set-ctrl=wb_manual_bgain=1024 \
        --set-ctrl=wb_manual_color_temp_unit_k=5500
	wait

done

