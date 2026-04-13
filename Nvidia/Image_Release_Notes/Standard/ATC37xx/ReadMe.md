# How to recover image to ATC37xx

## **Prepare another host PC with an Ubuntu system; it cannot be a virtual machine.**

# Recovery (Image v4.1.10.0 or older)
### 1. The host PC is connected to the ATC37xx via an OTG cable.

![image](https://github.com/mcsnexcom/MCS_Product/tree/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step1.png)

### 2. Execute Putty in host system
	Serial Line : /dev/ttyUSB0
	Speed : 115200 -> Open
	
![image](https://github..com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step2.png)

### 3. Press Enter in putty window and entery password, it will shows the information about update system.

![image](https://github..com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step3.png)

### 4. Entry command in ATC37xx device and password then ATC system into recovery mode.
	$ sudo reboot --force forced-recovery
	
![image](https://github..com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step4.png)

### 5. Go back to image folder and decompress image file:
	$ tar xvf ATC37xx_mfi_"version".tar.gz
	Noted. The commands need to modified according different file names.
	
![image](https://github..com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step5.png)

### 6. Excute recover command:
	$ sudo ./tools/kernel_flash/L4t_initrd_flash.sh --flash-only --massflash 1
	
![image](https://github..com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step6.png)

### 7. When recover process finished, it will shows "Success"

![image](https://github..com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step7.png)

### 8. Reboot ATC37xx device, it will start to configure the system.

![image](https://github..com/mcsnexcom/MCS_Product/blob/main/Nvidia/Image_Release_Notes/Standard/ATC37xx/Media/step8.png)


# Recovery (Image v4.1.11.0 or newer)

### Before performing the above steps, update ATC37xx's MCU to version R15 or later.
