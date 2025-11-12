# Flash MCU firmware steps:
### Use root mode and compilation environment
  - sudo -s
  - export LD_LIBRAY_PATH=LIB_x86_64
### Copy the MCU file to the folder
  - cp "path of MCU file from" FW/MCU/"path of MCU file to"
### Edit the flash script configuration
  - cd configs
  - select the config
### execute flash
  - cd ..
  - ./bin/mcu_upd
