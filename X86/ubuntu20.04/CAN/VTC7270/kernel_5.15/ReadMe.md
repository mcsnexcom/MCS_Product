# How to use VTC7270 socket CAN under Linux system

## VTC7270 Linux SPI to CAN
### 1. Enter the BIOS
    a. Boot page
    b. Os selection select "Intel Linux"
### 2. Open terminal and enter root mode.
    $ sudo su
### 3. Unzip the file
    $  tar zxvf SPIto CAN_v1.3.tar.gz
### 4. Enter folder /SPItoCAN_v1.3/mcp251xfd_MCS then update packages
    $ apt update
### 5. Install packages.
    $ apt -y install make libncurses5-dev gcc libelf-dev dwarves zstd can-utils
### 6. Build mcp251xfd_mcs driver.
    $ make
### 7. Load mcp251xfd_mcs driver
    $ rmmod spidev
    $ modprobe can_dev
    $ insmod mcp251xfd_mcs.ko
### 8. List net connector.
    $ ls /sys/class/net/ -al
### 9. Set socket can type and bitrate.
    $ ip link set can0 type can bitrate 500000
    $ ip link set can1 type can bitrate 500000
### 10. Enable the specified CAN.
    $ ip link set can0 up
    $ ip link set can1 up
