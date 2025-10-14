#!/bin/bash

function check_file(){

    flash_type="MCU_UPDATE_INFO"

    if [ "$1" == "1" ]; then
        flash_type="MCU_UPDATE_INFO"
    elif [ "$1" == "2" ]; then
        flash_type="CAN_UPDATE_INFO"
    fi

    if [[ "$(uname -m)" =~ ^(arm|aarch64)$ ]]; then
	    product_name=$(cat /proc/device-tree/product 2>/dev/null || echo "Unknown")
    else
    	    product_name=$(dmidecode -s system-product-name 2>/dev/null || echo "Unknown")
    fi

    input_file="configs/$product_name"

    MCU_PATH=$(sed -n '/<'$flash_type'>/,/<\/'$flash_type'>/s/.*FILE_PATH:\(.*\)/\1/p' "$input_file")

    # echo "MCU_PATH : $MCU_PATH"


    # MCU_PATH=$(echo "$MCU_PATH" | awk -F'/' '{print $NF}')
    Bin=""

    if [ ! -z "$2" ];then 
        MCU_PATH=$2
    fi

    if echo "$MCU_PATH" | grep "\.bin";then
        Bin=".bin"
        echo "The $MCU_PATH contains $Bin."
    elif echo "$MCU_PATH" | grep "\.BIN";then
        Bin=".BIN"
        echo "The $MCU_PATH contains $Bin."
    else
        echo "The $MCU_PATH doesn't contain .bin."
        return 1
    fi

    suffix=${MCU_PATH#*$Bin}

    # echo "suffix : $suffix"

    if [ -n "$suffix" ]; then
        # echo "There are characters after $Bin : $suffix"
        md5=${suffix#*.}
        # echo "md5 : $md5"
        mcu_md5=$(md5sum $MCU_PATH | awk '{print $1}')
        # echo "mcu_md5 : $mcu_md5"
        if [ "${mcu_md5}" == "${md5}" ]; then
            echo "md5 matches"
            return 0
        else
            echo "md5 not matches"
            return 1
        fi
    else
        echo "There are no characters after $Bin"
        return 0
    fi
    return 0
}


function main(){
	POE_ARG="0 115200 /dev/ttyUSB0 ST VIOB-POE2-01"

	read -p "Which MCU type do you want to flash? (1: Standard MCU / 2: POE board)" TYPE 
    mcu_bin_path=""
    if [ ! -z "$1" ];then
        mcu_bin_path=$1
    fi

	case "$TYPE" in
		"1") # Standard MCU
			check_file 1 $mcu_bin_path
			res=$?
			if [ "$res" != "0" ];then
				echo "The bin file has an issue."
				return 1
			fi
			sudo LD_LIBRARY_PATH=LIB_x86_64 ./bin/mcu_upd $mcu_bin_path
			;;
		"2") # POE board
			check_file 2
			res=$?
			if [ "$res" != "0" ];then
				echo "The bin file has an issue."
				return 1
			fi
			sudo LD_LIBRARY_PATH=LIB_x86_64 ./bin/mcu_upd $POE_ARG
			;;
	esac

	if [ $? -eq 0 ]; then
		echo -e "\033[32mFlashing MCU successfully.\033[0m"
	#	if [ `cat /etc/issue | grep "Ubuntu 14.04" | wc -l` -eq 1 ]; then
		if [ "$TYPE" = "1" ]; then
			sleep 3
			sudo shutdown -h now
		fi
	else
		echo -e "\033[31m\nFlashing MCU failed.\033[0m"
		echo -e "\033[36mWill reflash MCU automatically after 10 seconds.\033[0m"
		sleep 10
		bash flash_mcu.sh
	fi
}

main $1
