# How to use VTC1920 socket CAN under Linux system

## Test step of VTC1920 Linux SPI to CAN
1. Install Driver
    a. $ sudo -s
    b. $ apt-get update
    c. $ apt-get install build-essential fakeroot gcc-13 make kernel-package net-tools can-utils
    d. $ unzip driver.zip
    e. $ cd driver
    f. $ make clean
    g. $ make
    h. $ make install
2. Reboot system
3. check CAN interface
    ls /sys/class/net/ -al

## Test CAN send/recieve
1. Set CAN bitrate
    a. $ sudo -s
    b. $ ip link set can0 down
    c. $ ip link set can0 type can bitrate 250000
    d. $ ip link set can0 up
2. Send CAN data
    a. $ cansend can0 123#DEADBEEF
3. Recieve CAN data
    a. $ candump can0 -t -d
4. If Buffer is full, it will shows: write : No buffer space available.
    a. You can increase the buffer size by below command:
        $ ifconfig can0 txqueuelen 1000
