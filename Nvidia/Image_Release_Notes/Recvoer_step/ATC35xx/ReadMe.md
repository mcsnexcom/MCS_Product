# How to recover image to ATC35xx

## **Prepare another host PC with an Ubuntu system; it cannot be a virtual machine.**

# Recovery
### 1. The host PC is connected to the ATC35xx via an OTG cable.
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step1.png)
### 2. Execute Putty in host system
	Serial Line : /dev/ttyUSB0
	Speed : 115200 -> Open
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step2.png)
### 3. Press Enter in putty window and entery password, it will shows the information about update system.
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step3.png)

### 4. Entry command and password then ATC system into recovery mode.
	$ sudo reboot --force forced-recovery
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step4.png)
### 5. Go back to image folder and decompress image file:
	$ tar xvf ATC35xx_mfi_"version".tar.gz
	Noted. The commands need to modified according different file names.
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step5.png)
### 6. Excute recover command:
	$ sudo ./tools/kernel_flash/L4t_initrd_flash.sh --flash-only --massflash 1
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step6.png)

### 7. When recover process finished, it will shows "Success"
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step7.png)

### 8. Reboot ATC35xx device, it will start to configure the system.
![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC35xx/image/step8.png)
