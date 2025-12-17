# **ATC Series Release Notes**

### **ATC3520 / ATC3560-IP7-NA4C / ATC3561-NA4C / ATC3562-IP7-NA4M / ATC3563-NA8C/NA8CR**

| Date | Jetpack Version | SoM | Image Version | Kernel version | Release note | Other |
| :---- | :---- | :---- | :---- | :---- | :---- | :---- |
| 2025-10-31 | 6.2 | Orin Nano 4G/8G | 4.2.5.0 | 5.15.148-tegra | 1\. Added support for the Sensing "ISX031C-GMSL2F" GMSL2 camera. 2\. GPS LED reflects module connection status. 3\. Restored UEFI recovery boot, removed unbootable flag logic. 4\. Added support for WMX7207 Wi-Fi module. 5\. Added support for LAN8870 module. 6\. Updated MUT version to v2.2.65. 7\. EYY0JNOR-2E00: Fix OTG bug ( No ttyACM0 on host). 8\. ATC3563: Fix OTG bug ( No ttyACM0 while no USB-A device is connected). |  |
| 2025-09-19 | 6.2 | Orin Nano 4G/8G | 4.2.4.0 | 5.15.148-tegra | 1\. Remove NEXCOM from UEFI 2\. Add power mode 25W |  |
| 2025-08-15 | 6.2 | Orin Nano 4G/8G | 4.2.3.0 | 5.15.148-tegra | 1\. Support modules:ATC3520 ATC3560 ATC3561 ATC3562 ATC3563 AIEdge-X80. 2\. Change module name: A. ATC3540 \-\> ATC3560 B. ATC3521, ATC3541 \-\> ATC3561 C. ATC3522, ATC3542 \-\> ATC3562 3\. Need to update MCU version to apply module name changing: A. ATC3561: AT35610R01.bin B. ATC3562: AT35620R01.bin 4\. Orin Nano power mode remove 25w option. 5\. Add different fan control configs for different modules. 6\. Add functionality to configure the POE board via I2C. 7\. If system hangs for over 30 seconds during shutdown, MCU will force a power-off. 8\. Orin-NX 16G: If fails to enter OS, MCU will force a reboot (WDT timeout: 180s). 9\. Add support for OS flashing via USB drive (only for Image versions \> 4.2.3.0). |  |
| 2025-06-27 | 6.2 | Orin Nano 4G/8G | 4.2.2.0 | 5.15.148-tegra | 1\. Support ATC3520, ATC3521, ATC3540, ATC3541. 2\. Add module ID check in bootloader. 3\. Fix "tegrastats" displaying fan rpm as 0\. 4\. Update MUT version to v2.2.53. 5\. Add MCU & Generic Update Tool(GUT). |  |
| 2025-05-30 | 6.2 | Orin Nano 4G/8G | 4.2.1.0 | 5.15.148-tegra | 1\. Support ATC3520, ATC3521. 2\. Remove recovery boot, unbootable lead to direct boot. 3\. Fix sometimes black screen while running nv-oem-config-firstboot issue. |  |
| 2024-12-06 | 5.1.2 | Orin Nano 4G/8G | 3.5.0 | 5.10.120-tegra | 1\. Support ATC3520 series. 2\. Disable screensaver by default. 3\. Update MUT version to v2.2.39. 4\. Fix issue where shutdown is delayed when Ignition is off. 5\. NVIDIA update: PCN\_211361. |  |
| 2024-11-15 | 6.1 | Orin Nano 4G/8G | 4.1.1.0 | 5.15.148-tegra | 1\. Support ATC3520 . |  |
| 2024-07-16 | 5.1.1 | Orin Nano 4G/8G | 2.1.0 | 5.10.104-tegra | 1\. Fix RTC issue. 2\. Disable power saving. 3\. Add acpi event, enable ignition power off. |  |

### **ATC3530**

| Date | Jetpack Version | SoM | Image Version | Kernel version | Release note | Other |
| :---- | :---- | :---- | :---- | :---- | :---- | :---- |
| 2025-07-09 | 5.1.3 | Xavier NX 8G/16G | 3.8.0 | 5.10.192-tegra | 1\. Remove recovery boot, unbootable lead to direct boot. |  |
| 2024-10-11 | 5.1.3 | Xavier NX 8G/16G | 3.4.0 | 5.10.192-tegra | 1\. Fix intermittent boot issues with no HDMI display. 2\. Resolve MIPI camera startup failure on specific boards. 3\. Fix occasional USB 3.0 functionality issues during boot. 4\. Add LED functionality for the WMX6218 Wi-Fi module. |  |
| 2024-09-19 | 4.6 | Xavier NX 8G/16G | 2.4.0 | 4.9.253-tegra | 1\. Add LED indicator functionality for the WMX6218 Wi-Fi module. 2\. Fix GPS detection issue with WIFI module WMX6218 . |  |
| 2024-08-02 | 5.1.3 | Xavier NX 8G/16G | 3.3.0 | 5.10.192-tegra | 1\. Support ATC3530 8G/16G. |  |
| 2024-07-17 | 5.0.2 | Xavier NX 8G/16G | 3.1.0 | 5.10.104-tegra | 1\. Fix RTC issue. 2\. Disable power saving. 3\. Add acpi event, enable ignition power off. |  |
| 2023-08-08 | 4.6 | Xavier NX 8G/16G | 2.3.0 | 4.9.253-tegra | 1\. Support ATC3530 8G/16G. |  |
| 2023-04-14 | 4.6 | Xavier NX 8G/16G | 2.2.0 | 4.9.253-tegra | 1\. updated MIPI driver for zoom camera. |  |
| 2023-03-25 | 4.6 | Xavier NX 8G/16G | 2.1.0 | 4.9.253-tegra | 1\. updated MIPI driver for zoom camera. |  |
| 2023-01-07 | 5.0.2 | Xavier NX 8G/16G | 3.0.0 | 5.10.104-tegra | 1\. updated Jetpack version to 5.0.2. |  |
| 2022-08-12 | 4.6 | Xavier NX 8G/16G | 2.0.0 | 4.9.253-tegra | 1\. updated root on SSD & SD card, install SDK script, and User manual. 2\. fixed TX2-NX SD card issue. |  |
|  | TX2-NX |  |  |  |  |  |
| 2022-06-30 | 4.6 | Xavier NX 8G/16G | 1.1.5 | 4.9.253-tegra | 1\. fixed 5G module suspend/resume issue. 2\. added Quectel RM500Q usb mode script and update driver to v1.2.1. 3\. updated MUT 2.1.8 and install script. 4\. opened nvidia l4t sources list. |  |
|  | TX2-NX | 1.2.2 |  |  |  |  |
| 2022-04-28 | 4.6 | Xavier NX 8G/16G | 1.1.4 | 4.9.253-tegra | 1\. updated MUT 2.1.7. 2\. supported Thales PLS62/MV31 modem. 3\. supported Sierra EM7455 modem. 4\. supported Intel 8265 WIFI. 5\. supported Sparklan WPEQ-261ACNI(BT)/ WPEQ-262ACNI(BT) WIFI. 6\. fixed cpu/gpu/cv loading issue. |  |
|  | TX2-NX | 1.2.1 |  |  |  |  |
| 2022-03-23 | 4.6 | Xavier NX 8G/16G | 1.1.3 | 4.9.253-tegra | 1\. updated MUT 2.1.6. 2\. supported Quectel EM05/EM06/RM500Q/RM502Q modem. 3\. supported Huawei ME909s-120/ME909s-821 modem. 4\. supported Sierra EM7430 modem. 5\. supported u-blox TOBY-L2 modem. 6\. fixed fan speed issue. |  |
|  | TX2-NX | 1.2.0 |  |  |  |  |
| 2022-03-03 | 4.6 | Xavier NX 8G/16G | 1.1.2 | 4.9.253-tegra | 1\. updated MUT 2.1.5. 2\. updated CAN bus script. 3\. supported Sparklan WPEQ-256ACNI WIFI. |  |
| 2022-02-18 | 4.6 | Xavier NX 8G/16G | 1.1.1 | 4.9.253-tegra | 1\. supported Telit LM960A18 modem. 2\. supported Sparklan WPEQ-261ACNI(BT)/ WPEQ-262ACNI(BT) WIFI. 3\. fixed cpu/gpu/cv loading issue. |  |
| 2022-01-26 | 4.6 | Xavier NX 8G/16G | 1.1.0 | 4.9.253-tegra | 1\. first formal version. |  |
|  | TX2-NX | 1.1.0 |  |  |  |  |

### **ATC3540 / ATC3560-IP7-NX4C/NX4CF / ATC3560-IP7-NXAI4CR / ATC3561-NX4CF / ATC3562-IP7-NX4MF / ATC3563-NX8C/NXA8CR**

| Date | Jetpack Version | SoM | Image Version | Kernel version | Release note | Other |
| :---- | :---- | :---- | :---- | :---- | :---- | :---- |
| 2025-10-31 | 6.2 | Orin NX 8G/16G | 4.2.5.0 | 5.15.148-tegra | 1\. Added support for the Sensing "ISX031C-GMSL2F" GMSL2 camera. 2\. GPS LED reflects module connection status. 3\. Restored UEFI recovery boot, removed unbootable flag logic. 4\. Added support for WMX7207 Wi-Fi module. 5\. Added support for LAN8870 module. 6\. Updated MUT version to v2.2.65. 7\. EYY0JNOR-2E00: Fix OTG bug ( No ttyACM0 on host). 8\. ATC3563: Fix OTG bug ( No ttyACM0 while no USB-A device is connected). |  |
| 2025-09-19 | 6.2 | Orin NX 8G/16G | 4.2.4.0 | 5.15.148-tegra | 1\. Remove NEXCOM from UEFI 2\. Add power mode 25W |  |
| 2025-08-15 | 6.2 | Orin NX 8G/16G | 4.2.3.0 | 5.15.148-tegra | 1\. Support modules:ATC3520 ATC3560 ATC3561 ATC3562 ATC3563 AIEdge-X80. 2\. Change module name: A. ATC3540 \-\> ATC3560 B. ATC3521, ATC3541 \-\> ATC3561 C. ATC3522, ATC3542 \-\> ATC3562 3\. Need to update MCU version to apply module name changing: A. ATC3561: AT35610R01.bin B. ATC3562: AT35620R01.bin 4\. Orin Nano power mode remove 25w option. 5\. Add different fan control configs for different modules. 6\. Add functionality to configure the POE board via I2C. 7\. If system hangs for over 30 seconds during shutdown, MCU will force a power-off. 8\. Orin-NX 16G: If fails to enter OS, MCU will force a reboot (WDT timeout: 180s). 9\. Add support for OS flashing via USB drive (only for Image versions \> 4.2.3.0). |  |
| 2025-06-27 | 6.2 | Orin NX 8G/16G | 4.2.2.0 | 5.15.148-tegra | 1\. Support ATC3520, ATC3521, ATC3540, ATC3541. 2\. Add module ID check in bootloader. 3\. Fix "tegrastats" displaying fan rpm as 0\. 4\. Update MUT version to v2.2.53. 5\. Add MCU & Generic Update Tool(GUT). |  |
| 2025-05-30 | 6.2 | Orin NX 8G/16G | 4.2.1.0 | 5.15.148-tegra | 1\. Support ATC3540, ATC3541. 2\. Remove recovery boot, unbootable lead to direct boot. 3\. Fix sometimes black screen while running nv-oem-config-firstboot issue. |  |
| 2025-02-27 | 6.2 | Orin NX 8G/16G | 4.2.0.0 | 5.15.148-tegra | 1\. Support ATC3540, ATC3541 and AIEdge-X80. |  |
| 2024-12-13 | 5.1.2 | Orin NX 8G/16G | 3.1.5 | 5.10.120-tegra | 1\. Update MUT version to v2.2.41 . 2\. Update realtek driver to fix iperf issue . |  |
| 2024-08-19 | 5.1.2 | Orin NX 8G/16G | 3.1.4 | 5.10.120-tegra | Fixed network interface. |  |
| 2024-06-21 | 5.1.2 | Orin NX 8G/16G | 3.1.3 | 5.10.120-tegra | Fix BT transfer problem. |  |
| 2024-06-04 | 5.1.2 | Orin NX 8G/16G | 3.1.2 | 5.10.120-tegra | Fixed boot up problem. |  |
| 2024-06-03 | 5.1.2 | Orin NX 8G/16G | 3.1.1 | 5.10.120-tegra | 1\. Update MUT version to v2.2.36. 2\. Set Ubuntu 'Power Saving \-\> Blank Screen' option to 'Never' as default. 3\. Disable ubuntu 'logout-prompt' to fixed ignition off can't power-off issue. 4\. NVIDIA update: PCN\_211361. |  |
| 2024-11-01 | 6.1 | Orin NX 8G/16G | 4.1.0.0 | 5.15.148-tegra | 1\. Support ATC3540 8G/16G. 2\. Set fan control "Quiet" mode as default. |  |
| 2024-08-14 | 6 | Orin NX 8G/16G | 4.0.1.0 | 5.15.136-tegra | 1\. Support ATC3540 8G/16G. |  |
| 2024-07-16 | 5.1.1 | Orin NX 8G/16G | 2.1.0 | 5.10.104-tegra | 1\. Fix RTC issue. 2\. Disable power saving. 3\. Add acpi event, enable ignition power off. |  |
| 2024-03-29 | 5.1.2 | Orin NX 8G/16G | 3.0.0 | 5.10.120-tegra | 1\. Update to Jetpack 5.1.2. |  |
| 2023-11-09 | 5.1.1 | Orin NX 8G/16G | 1.9.0 | 5.10.104-tegra | 1\. Fix otg hot-plug issue. 2\. Fix NVMe status led always on. |  |
| 2023-10-13 | 5.1.1 | Orin NX 8G/16G | 1.8.0 | 5.10.104-tegra | 1\. Fix i210 can't link up after reboot. 2\. Fix X710 can't link up after reboot. 3\. Set fan profile to "Quiet" by default. 4\. Add "Cool" and "Performance" fan profile. 5\. Support NVMe Gen4. 6\. Support rtl8822ce. 7\. Add watchdog service. |  |
| 2023-09-08 | 5.1.1 | Orin NX 8G/16G | 1.7.0 | 5.10.104-tegra | 1\. Support ATC3540 8G/16G. |  |

### **ATC3750-6C series**

| Date | Jetpack Version | SoM | Image Version | Kernel version | Release note | Other |
| :---- | :---- | :---- | :---- | :---- | :---- | :---- |
| 2025-10-09 | 6.1 | AGX Orin 32G/64G | 4.1.10.0 4.1.10.0\_NVMe | 5.15.148-tegra | 1\. NVIDIA’s official bug-fix patches. (https://elinux.org/Jetson/L4T/r36.4.x\_patches) |  |
| 2025-08-22 | 6.1 | AGX Orin 32G/64G | 4.1.7.0 4.1.7.0\_NVMe | 5.15.148-tegra | 1\. UEFI remove nexcom logo. 2\. Fixed RS232 communction failure at baud rates below 9600 bps. |  |
| 2025-05-09 | 6.1 | AGX Orin 32G/64G | 4.1.2.0\_NVMe | 5.15.148-tegra | 1\. Supported AGX Orin flash to NVMe. |  |
| 2024-11-01 | 6.1 | AGX Orin 32G/64G | 4.1.0.0 | 5.15.148-tegra | 1\. Added MUT 2.2.36. 2\. Support ATC3750-6C 32G/64G. |  |
| 2024-12-30 | 5.1.1 | AGX Orin 32G/64G | 2.2.0\_NVMe | 5.10.104-tegra | 1\. Supported AGX Orin flash to NVMe. |  |
| 2024-11-25 | 5.1.1 | AGX Orin 32G/64G | 2.2.0 | 5.10.104-tegra | 1\. Added MUT 2.2.38. 2\. Fixed otg(host) can't detect device at first time. 3\. Set Ubuntu 'Power Saving \-\> Blank Screen' option to 'Never' as default. 4\. Disable ubuntu 'logout-prompt' to fixed ignition off can't power-off issue. 5\. NVIDIA PCN\_210100 patch. |  |
| 2023-09-22 | 5.1.1 | AGX Orin 32G/64G | 1.4.0 | 5.10.104-tegra | 1\. Fixed ZQ802XRACB(rtl8821ae) panic issue. 2\. Fixed AX-210 bluetooth can't connect issue. 3\. Fixed Azurewave AW-XM458MA reboot won't detect issue. 4\. Enabled KSZ9477 Jumbo Frame setting. |  |
| 2023-06-09 | 5.1.1 | AGX Orin 32G/64G | 1.2.0 | 5.10.104-tegra | 1\. Supported Telit LN960A16 modules. 2\. Fixed Azurewave AW-XM458MA can't detect Wi-Fi issue. 3\. NVIDIA fixed an issue with booting temperature below \-20 degree centigrade. |  |
| 2023-05-24 | 5.1.1 | AGX Orin 32G/64G | 1.1.0 | 5.10.104-tegra | 1\. Disabled Suspend function. |  |
| 2023-05-10 | 5.1.1 | AGX Orin 32G/64G | 1.0.0 | 5.10.104-tegra | 1\. Support AGX Orin 32/64 GB ram SoM. 2\. Update xusb firmware for UART receiving data bug. |  |
| 2023-04-14 | 5.0.2 | AGX Orin 32G/64G | 2.0.0 | 5.10.104-tegra | 1\. Update to Jetpack 5.0.2. 2\. Update xusb firmware for UART receiving data bug. |  |
| 2023-01-09 | 5.0.2 | AGX Orin 32G | 1.0.0 | 5.10.104-tegra | 1\. Support AGX Orin 32GB ram SoM. |  |

### **ATC3750-IP7-8M series**

| Date | Jetpack Version | SoM | Image Version | Kernel version | Release note | Other |
| :---- | :---- | :---- | :---- | :---- | :---- | :---- |
| 2025-10-09 | 6.1 | AGX Orin 32G/64G | 4.1.10.0 4.1.10.0\_NVMe | 5.15.148-tegra | 1\. Added support for the Sensing "ISX031C-GMSL2F" GMSL2 camera. 2\. Update the StereoLabs GMSL2 driver. 3\. Fixed an issue where the e-con Systems "STURDeCAM31" could not erase/write the SPI flash. 4\. Applied NVIDIA’s official bug-fix patches. (https://elinux.org/Jetson/L4T/r36.4.x\_patches) |  |
| 2025-08-22 | 6.1 | AGX Orin 32G/64G | 4.1.7.0 4.1.7.0\_NVMe | 5.15.148-tegra | 1\. UEFI remove nexcom logo. 2\. Fixed RS232 communction failure at baud rates below 9600 bps. 3\. Fix "STURDeCAM31" GMSL2 camera compatibility issue. 4\. Added support for the "STURDeCAM25" GMSL2 camera. 5\. Added support for the "StereoLabs" GMSL2 camera. |  |
| 2025-05-09 | 6.1 | AGX Orin 32G/64G | 4.1.2.0\_NVMe | 5.15.148-tegra | 1\. Supported AGX Orin flash to NVMe. |  |
| 2024-12-30 | 5.1.1 | AGX Orin 32G/64G | 2.2.0\_NVMe | 5.10.104-tegra | 1\. Supported AGX Orin flash to NVMe. |  |
| 2024-11-25 | 5.1.1 | AGX Orin 32G/64G | 2.2.0 | 5.10.104-tegra | 1\. Added MUT 2.2.38. 2\. Fixed otg(host) can't detect device at first time. 3\. Set Ubuntu 'Power Saving \-\> Blank Screen' option to 'Never' as default. 4\. Disable ubuntu 'logout-prompt' to fixed ignition off can't power-off issue. 5\. NVIDIA PCN\_210100 patch. |  |
| 2024-11-01 | 6.1 | AGX Orin 32G/64G | 4.1.0.0 | 5.15.148-tegra | 1\. Added MUT 2.2.36. 2\. Support ATC3750-8M 32G/64G. 3\. Added support for the "STURDeCAM31" GMSL2 camera. (Currently, only supports 4 cameras) |  |
| 2023-09-22 | 5.1.1 | AGX Orin 32G/64G | 1.4.0 | 5.10.104-tegra | 1\. Fixed ZQ802XRACB(rtl8821ae) panic issue. 2\. Fixed AX-210 bluetooth can't connect issue. 3\. Fixed Azurewave AW-XM458MA reboot won't detect issue. 4\. Enabled KSZ9477 Jumbo Frame setting. |  |
| 2023-06-09 | 5.1.1 | AGX Orin 32G/64G | 1.2.0 | 5.10.104-tegra | 1\. Supported Telit LN960A16 modules. 2\. Fixed Azurewave AW-XM458MA can't detect Wi-Fi issue. 3\. NVIDIA fixed an issue with booting temperature below \-20 degree centigrade. |  |
| 2023-05-24 | 5.1.1 | AGX Orin 32G/64G | 1.1.0 | 5.10.104-tegra | 1\. Disabled Suspend function. |  |
| 2023-05-10 | 5.1.1 | AGX Orin 32G/64G | 1.0.0 | 5.10.104-tegra | 1\. Support AGX Orin 32/64 GB ram SoM. 2\. Update xusb firmware for UART receiving data bug. |  |

