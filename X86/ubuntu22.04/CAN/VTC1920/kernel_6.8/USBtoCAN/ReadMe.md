# How to use VTC1920 USB to CAN under Linux system

## Test step of VTC1920 Linux USB to CAN
1. OS select 
    a. Enter bios
    b. change to boot page
    c. OS selection select "Intel Linux"
2. Open terminal and enter root mode and unzip file.
    $ sudo su
    $ tar xvf SPItoCAN_kernel_6.8.tar.gz
3. Enter folder SPItoCAN_kernel_6.8/mcp251xfd_MCS then Execute #apt-get update to updatepackages.
    $ apt-get update
4. Install packages
    $ apt -y install make libncurses5-dev gcc libelf-dev dwarves zstd can-utils
5. Build mcp251xfd_mcs driver.
    $ make
6. Load mcp251xfd_mcs driver.
    $ rmmod spidev
    $ modprobe can_dev
    $ insmod mcp251xfd_mcs.ko can0gpio=704
7. Check net connector.
    $ ls /sys/class/net/ -al
8. Set socket can type and bitrate.
    $ ip link set can2 type can bitrate 250000
9. Bring up can2 interface.
    $ ip link set up can2

## Test can receiver
1. can receiver
    $ candump can2 -t d
