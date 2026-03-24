## Test step of VTC1921-IP to CAN

1. Enter the Bios -> Boot page -> OS selection select 【Intel Linux】

2. Open terminal and enter root mode and unzip file SPItoCAN_kernel_6.8.tar.gz
	$ sudo su
	$ tar xvf SPItoCAN_kernel_6.8.tar.gz

3. Enter folder and update packages
	$ cd SPItoCAN_kernel_6.8/mcp251xfd_mcs/
	$ apt-get update

4. Install necessary packages
	$ apt -y install make libncurses5-dev gcc-12 libelf-dev dwarves zstd can-utils

5. Build mcp251xfd_mcs driver
	$ make

6. Load mcp251xfd_mcs driver
	$ rmmod spidev
	$ modprobe can_dev
	$ insmod mcp251xfd_mcs.ko can0gpio=704

7. List net connecotr.
	$ ls /sys/class/net/-al

8. Set socket can type and bitrate.
	$ ip link set can2 type can bitrate 250000

9. Enable the specified CAN
	$ ip link set can2 up

### Test CAN receiver
	$ candump can2
