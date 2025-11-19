# MUT_SDK Tool Usage Steps Tutorial
### Use root mode and enter service folder
  - sudo -s
  - cd service
### Compilation environment
  - export LD_LIBRARY_PATH=LIB_x86_64
### Execute MUT_SDK
  - ./bin/mcu_menu_ap

![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/MUT_IO_SDK/v2.2.58/MUT_SDK/Sample%20media/MUT_SDK_main-page.png)

##Example:
Enter letters or numbers to select the corresponding option.

- "00" Enter MCU Demo AP<br>

![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/MUT_IO_SDK/v2.2.58/MUT_SDK/Sample%20media/system_or_poe.png)

- "00" Enter system option page<br>

![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/MUT_IO_SDK/v2.2.58/MUT_SDK/Sample%20media/system_main-page.png)

- "00" Enter system get page<br>

![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/MUT_IO_SDK/v2.2.58/MUT_SDK/Sample%20media/system%20page.png)

# Flash MCU firmware steps:
### Use root mode and compilation environment
  - sudo -s
  - export LD_LIBRAY_PATH=LIB_x86_64
### Copy the MCU file to the folder
  - cp "path of MCU file from" FW/MCU/"path of MCU file to"
### Edit the flash script configuration
  - cd configs
  - Select the config file for your desired flash model name.
  - $ vim "model name"
  - Change the file path to the corrected MCU file name, and then save and exit
Like this

![image](https://github.com/mcsnexcom/MCS_Product/blob/main/Nvidia/MUT_IO_SDK/v2.2.58/MUT_SDK/Sample%20media/MCU%20file.png)

### execute flash
  - cd ..
  - ./bin/mcu_upd
