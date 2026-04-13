# How to recover image to ATC35xx

## **Prepare another host PC with an Ubuntu system; it cannot be a virtual machine.**

# Recovery
### 1. Using Micro USB cable connects Host system to ATC serial OTG USB port.
### 2. The host PC is connected to the ATC35xx via an OTG cable.
### 3. Execute Putty in host system
	Serial Line : /dev/ttyUSB0
	Speed : 115200 -> Open
### 4. Press Enter in putty window and entery password, it will shows the information about update system.
### 5. Entry command and password then ATC system into recovery mode.
	$ sudo reboot --force forced-recovery
### 6. Go back to image folder and decompress image file:
	$ tar xvf ATC35xx_mfi_"version".tar.gz
	Noted. The commands need to modified according different file names.
### 7. Excute recover command:
	$ sudo ./tools/kernel_flash/L4t_initrd_flash.sh --flash-only --massflash 1
### 8. When recover process finished, it will shows "Success"
### 9. Reboot ATC35xx device, it will start to configure the system.
