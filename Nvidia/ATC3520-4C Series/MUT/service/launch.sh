#!/bin/bash

SRV_FIFO="/tmp/mut_serv_fifo"
POE_ARG="0 115200 /dev/ttyUSB0 ST VIOB-POE2-01"

if [ $# -eq 1 ]; then # standard MCU service
	case $1 in
		"stop")
			if [ ! -e /etc/os-release ]; then # For Yocto OS
				TMP_PID=`ps | grep -v grep | grep mcu_service | grep -v "LD_LIBRARY_PATH=LIB_x86_64" | grep -v "mcu_service $POE_ARG" | awk '{print $1}'`
			else
				TMP_PID=`ps aux | grep -v grep | grep mcu_service | grep -v "LD_LIBRARY_PATH=LIB_x86_64" | grep -v "mcu_service $POE_ARG" | awk '{print $2}'`
			fi
			if [ ! "$TMP_PID" = "" ]; then
				kill -9 $TMP_PID
				rm -f $SRV_FIFO
			else
				echo -e "\033[31mStop service failed.\033[0m"
			fi
		;;
		"start")
			LD_LIBRARY_PATH=LIB_x86_64 ./bin/mcu_service &
			if [ $? -eq 0 ]; then
				while [ ! -e $SRV_FIFO ]
				do
					sleep 1
				done
				chmod 0777 $SRV_FIFO
			fi
		;;
	esac
elif [ $# -eq 2 ]; then # POE board MCU service
	SRV_FIFO="/tmp/"$2
	case $1 in
		"stop")
			if [ ! -e /etc/os-release ]; then # For Yocto OS
				TMP_PID=`ps | grep -v grep | grep -v "LD_LIBRARY_PATH=LIB_x86_64" | grep "mcu_service $POE_ARG $2" | awk '{print $1}'`
			else
				TMP_PID=`ps aux | grep -v grep | grep -v "LD_LIBRARY_PATH=LIB_x86_64" | grep "mcu_service $POE_ARG $2" | awk '{print $2}'`
			fi
			if [ ! "$TMP_PID" = "" ]; then
				kill -9 $TMP_PID
				rm -f $SRV_FIFO
			else
				echo -e "\033[31mStop service failed.\033[0m"
			fi
		;;
		"start")
			LD_LIBRARY_PATH=LIB_x86_64 ./bin/mcu_service $POE_ARG $2 &
			if [ $? -eq 0 ]; then
				while [ ! -e $SRV_FIFO ]
				do
					sleep 1
				done
				chmod 0777 $SRV_FIFO
				echo -e "\033[32mThe server FIFO name of PoE board is "$2"\033[0m"
			fi
		;;
	esac
else
	echo -e "\033[32m[USAGE] {sh|bash} launch.sh {action} [fifo name]\033[0m"
	echo -e "\033[32m{action}\033[0m"
	echo -e "\033[32m   start, Start MCU/PoE board service\033[0m"
	echo -e "\033[32m    stop,  Stop MCU/PoE board service\033[0m"
	echo -e "\033[32m[fifo name], If you start/stop PoE board service,\033[0m"
	echo -e "\033[32m             you must provide customized fifo name to program.\033[0m"
fi 
