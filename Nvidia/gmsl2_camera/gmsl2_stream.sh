#!/bin/bash

TYPE=""
MODEL=""
VIDEO_CNT=""

FUN_PASS=0
FUN_FAIL=1

ENABLE=1
DISABLE=0
HCI=${DISABLE}

RED='\033[0;31m'
BLUE='\033[0;34m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

HAWK="nv_ar0234"
OWL="nv_ar0234_owl"
APPROPHO="ap_cam_gmsl"
CAM21="ecam_yuv_gmsl"
CAM25="ecam_gmsl_yuv_common"
CAM31="ecam_gmsl_yuv_common"

DISCRETE_ARR=()
DISCRETE_IDX=""

ARGUS_TAG=1
MODELS=( "$HAWK" "$OWL" "$APPROPHO" "$CAM21" "$CAM25" "$CAM31" )

LIB_SRC=""
DEV=""
WIDTH=""
HEIGHT=""
CAM_IDX=""

ARGVS=( "$LIB_SRC" "$DEV" "$WIDTH" "$HEIGHT" "$CAM_IDX" )

NVIDIA=0
V4L2=1

_CMD=( "gst-launch-1.0 %s %s ! 'video/x-raw(memory:NVMM), width=%d, height=%d' ! queue ! nvvidconv ! 'video/x-raw, format=(string)I420' ! videorate ! textoverlay text=\"Camera %d\" valignment=top halignment=center ! fpsdisplaysink video-sink=xvimagesink sync=false > /dev/null 2>&1 &" 
	"gst-launch-1.0 %s %s ! videorate ! 'video/x-raw, width=%d, height=%d' ! textoverlay text=\"Camera %d\" valignment=top halignment=center ! fpsdisplaysink video-sink=xvimagesink sync=false -v > /dev/null 2>&1 &" )

GET_VIDEO_CNT(){
	VIDEO_CNT=$(ls /dev/video* 2>/dev/null | wc -l)
	if [ $VIDEO_CNT -eq 0 ]; then
		return $FUN_FAIL
	fi
	return $FUN_PASS
}

GET_MODEL(){
	for (( i=0;i<${#MODELS[@]}; i++))
	do
		if [ -d /sys/module/${MODELS[$i]} ]; then
			MODEL=${MODELS[$i]}
			echo -e "${YELLOW}MODEL : ${MODEL}${NC}"
			if [ $i -le ${ARGUS_TAG} ]; then
				TYPE="$NVIDIA"
				LIB_SRC="nvarguscamerasrc"
				_DEV="sensor-id=%d"
			elif [ "$MODEL" == "${APPROPHO}" ]; then
				TYPE="$NVIDIA"
				LIB_SRC="nvv4l2camerasrc"
				_DEV="device=/dev/video%d"
			else
				TYPE="$V4L2"
				LIB_SRC="v4l2src"
				_DEV="device=/dev/video%d"
			fi
			if [[ $MODEL =~ ^${APPROPHO} ]]; then
				HCI=$ENABLE
			fi
			break;	
		fi
	done	
}

SELECT_DISCRETE(){
	# $1 : /dev/video<N>
	readarray -t DISCRETE_ARR < <(v4l2-ctl --list-formats-ext -d $1 | grep 'Size: Discrete' | awk '{print $3}' | sort -n | uniq)

	for (( i=0; i<${#DISCRETE_ARR[@]}; i++ ))
	do
		echo -e "$((i+1)) ${DISCRETE_ARR[$i]}"	
	done
	echo -e "0. exit"

	read -p $'\e[33m'"Please select output stream discrete [0-${#DISCRETE_ARR[@]}] : "$'\e[0m' DISCRETE_IDX	
	
	if [[ ! "$DISCRETE_IDX" =~ ^[0-9]$ ]]; then
		echo -e "${RED}Invalid value! Input should be number [0-${#DISCRETE_ARR[@]}]${NC}"
		SELECT_DISCRETE $1
	elif [ "$DISCRETE_IDX" -eq 0 ]; then
		exit
	fi


}

EVAL_CMD(){
	DEV=$(printf "$_DEV" "$1")
	WIDTH="`echo ${DISCRETE_ARR[$((DISCRETE_IDX - 1))]} | awk -F "x" '{print $1}'`"
	HEIGHT="`echo ${DISCRETE_ARR[$((DISCRETE_IDX - 1))]} | awk -F "x" '{print $2}'`"
	CAM_IDX=$1
	CAM_IDX=$((CAM_IDX + 1))
	ARGVS=( "$LIB_SRC" "$DEV" "$WIDTH" "$HEIGHT" "$CAM_IDX" )
	CMD="`printf "${_CMD[$TYPE]}" "${ARGVS[@]}"`"
	echo -e "CMD : ${CMD}"
	eval ${CMD}
}

START_STREAM(){
	if [ $HCI -eq $DISABLE ]; then
		SELECT_DISCRETE /dev/video0
		for (( k=0; k<${VIDEO_CNT}; k++ ))
		do
			EVAL_CMD $k	
			sleep 5
		done
	else
		for (( k=0; k<${VIDEO_CNT}; k++ ))
                do
			SELECT_DISCRETE /dev/video$k
                        EVAL_CMD $k
                        sleep 5
                done
	fi
}

# Main
GET_VIDEO_CNT
if [ $? -eq $FUN_PASS ]; then
	GET_MODEL
	START_STREAM
else
	echo -e "${RED}Can't find any video node!!${NC}"
	exit
fi

