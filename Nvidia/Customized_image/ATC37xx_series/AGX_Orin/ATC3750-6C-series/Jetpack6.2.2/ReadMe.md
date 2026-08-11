# ATC375x Kernel Customization

**JetPack 6.2.2 (r36.5)**

---

## Reference

- NVIDIA Jetson Linux Kernel Customization Guide  
  https://docs.nvidia.com/jetson/archives/r36.5/DeveloperGuide/SD/Kernel/KernelCustomization.html#to-manually-download-and-expand-the-kernel-sources

---

## 1. Download Jetson Linux Sources

### 1-1. Download NVIDIA Jetson BSP

```bash
wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/release/Jetson_Linux_r36.5.0_aarch64.tbz2
```

### 1-2. Extract NVIDIA Jetson BSP

```bash
tar xvf <install-path>/Jetson_Linux_r36.5.0_aarch64.tbz2
```

### 1-3. Download Driver Package Sources

```bash
wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/sources/public_sources.tbz2
```

### 1-4. Extract Kernel Sources

```bash
tar xvf <install-path>/public_sources.tbz2
cd <install-path>/Linux_for_Tegra/source/
tar xf kernel_src.tbz2
tar xf kernel_oot_modules_src.tbz2
tar xf nvidia_kernel_display_driver_source.tbz2
```

### 1-5. Download Sample Root File System

```bash
wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/release/Tegra_Linux_Sample-Root-Filesystem_r36.5.0_aarch64.tbz2
```

### 1-6. Extract Sample Rootfs

```bash
rm -rf <install-path>/Linux_for_Tegra/rootfs/README.txt
sudo tar -C <install-path>/Linux_for_Tegra/rootfs \
    -jpxvf <install-path>/Tegra_Linux_Sample-Root-Filesystem_r36.5.0_aarch64.tbz2
```

### 1-7. Download and Setup Cross Compile Toolchain

```bash
cd <install-path>
wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v3.0/toolchain/aarch64--glibc--stable-2022.08-1.tar.bz2
mkdir toolchain
tar -C toolchain -xvf aarch64--glibc--stable-2022.08-1.tar.bz2
export CROSS_COMPILE=<install-path>/toolchain/aarch64--glibc--stable-2022.08-1/bin/aarch64-buildroot-linux-gnu-
```

---

## 2. Apply ATC375x BSP & Kernel Patches

### 2-1. Extract Patch Package

```bash
sudo tar xvf ATC375x_patch_v4.3.1.2.tar.gz
```

### 2-2. Apply BSP Patch

```bash
sudo cp -aRP ATC375x_patch_v4.3.1.2/bsp_patch/* <install-path>/Linux_for_Tegra
```

### 2-3. Apply Kernel Patch

```bash
sudo cp -af ATC375x_patch_v4.3.1.2/kernel_patch/* <install-path>/Linux_for_Tegra
```

### 2-4. Run apply_binaries.sh

```bash
cd <install-path>/Linux_for_Tegra/
sudo ./apply_binaries.sh
```

---

## 3. Build Jetson Linux Kernel (In-tree)

### 3-1. Enter Source Directory

```bash
cd <install-path>/Linux_for_Tegra/source
```

### 3-2. Build Kernel

```bash
make KERNEL_DEF_CONFIG=atc3xxx_defconfig -C kernel
```

### 3-3. Install Kernel and Modules

```bash
export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
sudo -E make install -C kernel
cp kernel/kernel-jammy-src/arch/arm64/boot/Image \
   <install-path>/Linux_for_Tegra/kernel/Image
```

---

## 4. Build NVIDIA Out-of-Tree Modules

```bash
cd <install-path>/Linux_for_Tegra/source
export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
make modules
export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
sudo -E make modules_install
```

---

## 5. Build Device Tree Blobs (DTBs)

```bash
cd <install-path>/Linux_for_Tegra/source
export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
make dtbs
cp kernel-devicetree/generic-dts/dtbs/* \
   <install-path>/Linux_for_Tegra/kernel/dtb/
```

---

## 6. Apply Rootfs & Firmware Patches

```bash
sudo cp -af ATC375x_patch_v4.3.1.2/rootfs_patch/* \
    <install-path>/Linux_for_Tegra/rootfs

sudo cp -af ATC375x_patch_v4.3.1.2/module_patch/* \
    <install-path>/Linux_for_Tegra/rootfs
```

---

## 7. Update Initramfs

```bash
cd <install-path>/Linux_for_Tegra
sudo mv ./rootfs/etc/systemd/network/10-jetson-onboard-ethernet.link ./rootfs/etc/systemd/network/10-jetson-onboard-ethernet.link.bak
sudo mv ./rootfs/lib/firmware/iwlwifi-ty-a0-gf-a0-66.ucode ./rootfs/lib/firmware/iwlwifi-ty-a0-gf-a0-66.ucode.bak
sudo depmod -b ./rootfs/ 5.15.185-tegra
sudo ./tools/l4t_update_initrd.sh
```

---

## 8. (Optional) ATC3750-IP7-8Me Set Default GMSL2 Camera

## GMSL2 Camera DTBO Mapping

| Camera Module             | DTBO File                                                         |
| ------------------------- | ----------------------------------------------------------------- |
| **ApproPho**              | `tegra234-p3737-camera-overlay_appropho_gmsl_8ch.dtbo`            |
| **STURDeCAM21**           | `tegra234-p3737-camera-overlay_ecam_sturdecam21.dtbo`             |
| **STURDeCAM25**           | `tegra234-p3737-camera-overlay_ecam_sturdecam25.dtbo`             |
| **STURDeCAM31**           | `tegra234-p3737-camera-overlay_ecam_sturdecam31.dtbo`             |
| **Leopard Hawk + Owl**    | `tegra234-p3737-camera-overlay_leopard_imaging_hawk_and_owl.dtbo` |
| **Leopard Owl + Hawk**    | `tegra234-p3737-camera-overlay_leopard_imaging_owl_and_hawk.dtbo` |
| **StereoLabs ZED-X**      | `tegra234-p3737-camera-atc3750-sl-overlay.dtbo`                   |
| **Sensing ISX031C**       | `tegra234-sensing-gmsl2x8-overlay.dtbo`                           |
| **Orbbec gemini-335lg**   | `tegra234-sensing-gmsl2x8-overlay.dtbo`                           |

All supported GMSL2 DTBOs are copied to:

```
<install-path>/Linux_for_Tegra/kernel/dtb/
```

e.g. Set `STURDeCAM25` to default GMSL2 Camera

```diff
diff --git a/flash.sh b/flash.sh
index 57b7ab5..38feeff 100755
--- a/flash.sh
+++ b/flash.sh
@@ -1868,7 +1868,7 @@ function add_overlay_dtb_files(){
        if [[ $ext_target_board =~ atc356 ]]; then
                DEFAULT_CAMERA="tegra234-p3768-camera-overlay-econsystem-25.dtbo"
        elif [[ $ext_target_board =~ atc3750-8M ]]; then
-               DEFAULT_CAMERA=""
+               DEFAULT_CAMERA="tegra234-p3737-camera-overlay_ecam_sturdecam25.dtbo"
        fi

        # Copy files to mnt/boot & rootfs/boot
```

Copy `STURDeCAM25` driver from ATC375x_patch_v4.3.1.2/

```bash
    sudo cp -af ATC375x_patch_v4.3.1.2/rootfs_patch/nexcom/camera/.driver/STURDeCAM25/driver/* <install-path>/Linux_for_Tegra/rootfs/usr/lib/modules/5.15.185-tegra/
    cd <install-path>/Linux_for_Tegra/
    sudo depmod -b ./rootfs/ 5.15.185-tegra
```

---

## ⚠️ MCU Firmware Requirement (Important)

Before flashing **v4.3.1.2**, ensure the MCU firmware version meets the required minimum.

### Required MCU Firmware Versions

- **ATC3750-IP7-8Me**: `AT376R04.bin`
- **ATC3750-6C / IP7-6C**: `AT375R15.bin`

If not, please copy the following file to the ATC system and perform the MCU update:

```text
ATC375x_patch_v4.3.1.2/rootfs_patch/nexcom/MUT/
FLASH_MCU-linux_v2.2.72.tar.xz.58d643333c27f7e9d43e271a7d15c304
```

---

## 9. Flashing or Generating Massflash Package

### 9-1. Flash Target Device

#### ATC3750-6C / IP7-6C

eMMC:

```bash
cd <install-path>/Linux_for_Tegra/
sudo ./flash.sh atc3750-6C-orin mmcblk0p1
```

NVMe:

```bash
sudo ./tools/kernel_flash/l4t_initrd_flash.sh \
  --external-device nvme0n1p1 \
  -c tools/kernel_flash/flash_l4t_t234_nvme.xml \
  -p "-c bootloader/generic/cfg/flash_t234_qspi.xml" \
  --showlogs --network usb0 atc3750-6C-orin external
```

#### ATC3750-IP7-8Me

eMMC:

```bash
sudo ./flash.sh atc3750-8M-orin mmcblk0p1
```

NVMe:

```bash
sudo ./tools/kernel_flash/l4t_initrd_flash.sh --external-device nvme0n1p1 -c tools/kernel_flash/flash_l4t_t234_nvme.xml -p "-c bootloader/generic/cfg/flash_t234_qspi.xml" --showlogs --network usb0 atc3750-8M-orin external
```

---

### 9-2. (Optional) Generate Massflash Package

```bash
cp -af ATC375x_patch_v4.3.1.2/generate_mass_flash_package/* \
    <install-path>/Linux_for_Tegra/

sudo -s
cd <install-path>/Linux_for_Tegra/
bash ./package_atc375x.sh
```

**Note:**  
The `package_atc375x.sh` script packages firmware OS images for **all ATC3750-6C and ATC3750-IP7-8Me platforms**, including **eMMC and NVMe configurations**.
