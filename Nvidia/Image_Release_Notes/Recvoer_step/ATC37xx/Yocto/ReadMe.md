# Comprehensive Guide to Initrd Flashing

This document outlines the prerequisites and step-by-step procedure for flashing a device using the `initrd-flash` script, typically utilized within the OpenEmbedded/Yocto Project ecosystem for NVIDIA Tegra platforms.

Reference: [OE4T/meta-tegra initrd-flashing-support](https://github.com/OE4T/meta-tegra/wiki/initrd-flashing-support)

# Prerequisites and Host Setup

Before proceeding with the flashing process, ensure your host machine is correctly configured.

## 1. Required Host Commands

In addition to the standard tools necessary for building and normal flashing, your build host must have the following utilities available:

|  Command  |  Source Package   | Purpose                                                         |
| :-------: | :---------------: | :-------------------------------------------------------------- |
|  sgdisk   | gdisk or gptfdisk | Used for manipulating GPT partition tables.                     |
| udisksctl |      udisks2      | Used for interacting with the udisks2 daemon (disk management). |
| bmaptool  |    bmap-tools     | (Optional) Used for faster block-based writing.                 |

## 2. Disable Automatic Media Mounting (CRITICAL)

The `initrd-flash` script requires precise control over disk devices. Automatic mounting of removable media by the desktop environment will interfere with the flashing process, potentially causing errors or data corruption.

You must disable the feature that automatically mounts or prompts upon insertion of external storage devices (like USB drives).

### A. Command Line (Recommended for Modern Ubuntu/GNOME)

Use the `gsettings` utility to disable both automatic mounting and automatic opening of media handles for the current user session:

```bash
# Disable automatic mounting of media upon insertion
gsettings set org.gnome.desktop.media-handling automount false

# Disable the automatic opening of a file manager window after mounting
gsettings set org.gnome.desktop.media-handling automount-open false
```

### B. GUI Settings (Ubuntu 22.04+)

If you prefer the graphical interface:

1. Go to Settings (or System Settings).
2. Navigate to Removable Media (or Default Applications/Removable Storage).
3. Ensure the setting related to "Automatically mount removable media" or "Never prompt or start programs on media insertion" is disabled/checked accordingly.

# Flashing Procedure

Once the prerequisites are met, follow these three steps to flash your target device.

## Step 1: Extract the Image Archive

Navigate to the directory containing your compressed image file and extract its contents. The archive contains the necessary binaries, images, and the `initrd-flash` script.

```bash
tar xpf <image_name>.tar.gz
```

Replace `<image_name>.tar.gz` with the actual name of your generated image file.

## Step 2: Enter Recovery Mode

Place the device into Recovery Mode .

## Step 3: Start the Flashing Process

Execute the `initrd-flash` script with `sudo`. The script will detect the device, initiate the flashing sequence, and prompt you for necessary actions .

```bash
sudo ./initrd-flash.sh
```

Wait for the script to complete the entire process, including the partition table creation and data writing.

## (Option) ATC375x – Flash the system onto the NVMe drive.

Edit the `.env.initrd-flash file`:

```
FLASH_HELPER=tegra-flash-helper.sh
- BOOTDEV="mmcblk0p1"
- ROOTFS_DEVICE="mmcblk0"
+ BOOTDEV="nvme0n1p1"
+ ROOTFS_DEVICE="nvme0n1"
CHIPID="0x23"
MACHINE="atc375x"
```

Save the changes, then rerun `Step 2` and `Step 3` to flash the system.`
