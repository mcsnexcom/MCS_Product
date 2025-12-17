#!/bin/bash

display_usage() {
  echo -e "\e[1;37m\nUsage: bash v4l2_setmode.sh [anpr / cardvr] [camera NO.]"
  echo -e "Example: bash v4l2_setmode.sh anpr 1 \n\e[0m"
}


videoArray=("" "/dev/video0" "/dev/video1" "/dev/video2" "/dev/video3")

set_ANPR() {

  v4l2-ctl --stream-mmap --stream-count=10 -d ${videoArray[$1]}  &
  sleep 2

  v4l2-ctl -d ${videoArray[$1]} \
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

}

set_carDVR() {

  v4l2-ctl --stream-mmap --stream-count=10 -d ${videoArray[$1]}  &
  sleep 2

  v4l2-ctl -d ${videoArray[$1]} \
  --set-ctrl=power_line_frequency=1 \
  --set-ctrl=ae_max_gain=2 
  wait

}

if [  $# -le 0 ]
  then
  clear
  while :
    do
    echo "Main Menu:"
    echo -e "\t(1) ANPR mode "
    echo -e "\t(2) car DVR mode "
    echo -e "\t(3) Exit"
    echo -n "Please enter your choice:"
    read choice
    clear

    case $choice in
      "1")
      clear
      while :
        do
        echo "ANPR mode menu "
        echo -e "\t(1) set camera 1"
        echo -e "\t(2) set camera 2"
        echo -e "\t(3) set camera 3"
        echo -e "\t(4) set camera 4"
        echo -e "\t(5) Return to main menu"
        echo -n "Please enter your choice:"
        read choice1
        case $choice1 in
          "1")
          echo "set camera 1 to ANPR mode..."
          set_ANPR 1
          ;;
          "2")
          echo "set camera 2 to ANPR mode..."
          set_ANPR 2
          ;;
          "3")
          echo "set camera 3 to ANPR mode..."
          set_ANPR 3
          ;;
          "4")
          echo "set camera 4 to ANPR mode..."
          set_ANPR 4
          ;;
          "5")
          clear
          break
          ;;
          *)
          echo "invalid answer, please try again"
          ;;
        esac
        done
        ;;
      "2")
      clear
      while :
        do
        echo "Car DVR mode menu"
        echo -e "\t(1) set camera 1"
        echo -e "\t(2) set camera 2"
        echo -e "\t(3) set camera 3"
        echo -e "\t(4) set camera 4"
        echo -e "\t(5) Return to main menu"
        echo -n "Please enter your choice:"
        read choice1
        case $choice1 in
          "1")
          echo "set camera 1 to car DVR mode..."
          set_carDVR 1
          ;;
          "2")
          echo "set camera 1 to car DVR mode..."
          set_carDVR 2
          ;;
          "3")
          echo "set camera 1 to car DVR mode..."
          set_carDVR 3
          ;;
          "4")
          echo "set camera 1 to car DVR mode..."
          set_carDVR 4
          ;;
          "5")
          clear
          break
          ;;
          *)
          echo "invalid answer, please try again"
          ;;
        esac
        done
        ;;
      "3")
      exit
      ;;
      *)
      echo "invalid answer, please try again"
      ;;

    esac
    done
    
  else

    inputArray=( "$@" )
    case $inputArray in
      "anpr")
      echo "set camera ${inputArray[1]} to ANPR mode..."
      set_ANPR ${inputArray[1]}
      ;;
      "cardvr")  
      echo "set camera ${inputArray[1]} to CAR dvr mode..."
      set_carDVR ${inputArray[1]}
      ;;
      *)
      echo "Invalid argument."
      display_usage
      ;;
    esac


fi

