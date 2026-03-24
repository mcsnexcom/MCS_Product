# How to use VTC7260 socket CAN under Linux system

## Steps of VTC7260 Linux SPI to CAN 
### 1. OS select 
    a. Enter bios
    b. change to boot page
    c. OS selection select "Intel Linux"
### 2. Open terminal and enter root mode and unzip file.
    $ sudo su
    $ tar xvf SPItoCAN_v1.3.tar.gz 
### 3. Enter folder SPItoCAN_v1.3 then Execute #apt-get update to updatepackages.
    $ apt-get update
### 4. Install packages
    $ apt -y install make libncurses5-dev gcc libelf-dev dwarves zstd can-utils
### 5. Build mcp251xfd_mcs driver.
    $ make
### 6. Load mcp251xfd_mcs driver.
    $ rmmod spidev
    $ modprobe can_dev
    $ insmod mcp251xfd_mcs.ko can0gpio=943 (for Kernel 5.15)
    
### 7. Check net connector.
    $ ls /sys/class/net/ -al
### 8. Set socket can type and bitrate.
    $ ip link set can0 type can bitrate 250000
### 9. Bring up can0 interface.
    $ ip link set up can0

## Test can receiver
### 1. can receiver
    $ candump can0 -t d
