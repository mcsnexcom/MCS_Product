# Flash MCU firmware steps:
### Use root mode and compilation environment
  - sudo -s
  - export LD_LIBRAY_PATH=LIB_x86_64
### Copy the MCU file to the folder
  - cp "path of MCU file from" FW/MCU/"path of MCU file to"
### Edit the flash script configuration
  - cd configs
  - Edit the config of device using
  - **Example :**
    - Sample device : ATC3540
    - $ vim configs/ATC3540
    - find "FILE_PATH:FW/MCU/ATC3540/AT353R11.BIN"
    - modify "AT353R11.BIN" to new file name "AT353R12.BIN"
    - save and exit
### execute flash
  - cd ..
  - ./bin/mcu_upd
