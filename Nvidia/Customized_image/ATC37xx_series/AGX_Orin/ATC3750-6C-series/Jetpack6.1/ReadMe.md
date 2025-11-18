# [ATC3750-6C Kernel Customization] - Jetpack 6.1(r36.4)
> Reference : https://docs.nvidia.com/jetson/archives/r36.4/DeveloperGuide/SD/Kernel/KernelCustomization.html#to-manually-download-and-expand-the-kernel-sources

## 1. Locate and download the Jetson Linux source files for your release.
> https://developer.nvidia.com/embedded/jetson-linux-r3640
   
### 1-1. Download NVIDIA Jetson BSP
	$ wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v4.0/release/Jetson_Linux_R36.4.0_aarch64.tbz2
### 1-2. Untar NVIDIA Jetson BSP
	$ tar xvf <install-path>/Jetson_Linux_R36.4.0_aarch64.tbz2
### 1-3. Download Driver Package Sources
	$ wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v4.0/sources/public_sources.tbz2

### 1-4. Untar Sources
	$ tar xvf <install-path>/public_sources.tbz2
	$ cd <install-path>/Linux_for_Tegra/source/
	$ tar xf kernel_src.tbz2
	$ tar xf kernel_oot_modules_src.tbz2
	$ tar xf nvidia_kernel_display_driver_source.tbz2
### 1-5. Download Sample Root File System
	$ wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v4.0/release/Tegra_Linux_Sample-Root-Filesystem_R36.4.0_aarch64.tbz2
### 1-6. Extract the sample rootfs and launch apply_binaries.sh
	$ rm -rf <install-path>/Linux_for_Tegra/rootfs/README.txt
	$ sudo tar -C <install-path>/Linux_for_Tegra/rootfs -jpxvf <install-path>/Tegra_Linux_Sample-Root-Filesystem_R36.4.0_aarch64.tbz2
	$ cd <install-path>/Linux_for_Tegra/
	$ sudo ./apply_binaries.sh
### 1-7. Download and Setting Cross Compile Environment
	$ cd <install-path>
	$ wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v3.0/toolchain/aarch64--glibc--stable-2022.08-1.tar.bz2
	$ mkdir <install-path>/toolchain
	$ tar -C <install-path>/toolchain -xvf <install-path>/aarch64--glibc--stable-2022.08-1.tar.bz2
	$ export CROSS_COMPILE=<install-path>/toolchain/aarch64--glibc--stable-2022.08-1/bin/aarch64-buildroot-linux-gnu-

## 2. Copy ATC3750-6C patch file to Linux_for_Tegra BSP directory
### 2-1. Extract ATC3750-6C_patch_v4.1.10.0.tar.gz
       $ tar xvf ATC3750-6C_patch_v4.1.10.0.tar.gz
### 2-2. Copy ATC3750-6C_patch_v4.1.10.0/bsp_patch/* to <install-path>/Linux_for_Tegra
       $ sudo cp -aRP ATC3750-6C_patch_v4.1.10.0/bsp_patch/* <install-path>/Linux_for_Tegra
### 2-3. Copy ATC3750-6C_patch_v4.1.10.0/kernel_patch/* to <install-path>/Linux_for_Tegra
       $ sudo cp -af ATC3750-6C_patch_v4.1.10.0/kernel_patch/* <install-path>/Linux_for_Tegra

## 3. Building the Jetson Linux Kernel(in-tree)
  
### 3-1. Go to the build directory:
       $ cd <install-path>/Linux_for_Tegra/source

### 3-2. Run the following commands to build the Jetson Linux kernel and its in-tree modules:
	$ make KERNEL_DEF_CONFIG=atc3xxx_defconfig -C kernel
	   
### 3-3. Run the following commands to install the kernel and in-tree modules:  
	$ export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
	$ sudo -E make install -C kernel
	$ cp kernel/kernel-jammy-src/arch/arm64/boot/Image <install-path>/Linux_for_Tegra/kernel/Image
	   
## 4. Building the NVIDIA Out-of-Tree Modules

### 4-1. Go to the build directory:
	$ cd <install-path>/Linux_for_Tegra/source

### 4-2. Run the following commands to build:
	$ export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
	$ make modules

### 4-3. Run the following commands to install:
	$ export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
	$ sudo -E make modules_install

## 5. Building the DTBs

### 5-1. Go to the build directory:
	$ cd <install-path>/Linux_for_Tegra/source

### 5-2. Run the following commands to build:
	$ export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
	$ make dtbs

### 5-3. Run the following commands to install:
	$ cp kernel-devicetree/generic-dts/dtbs/* <install-path>/Linux_for_Tegra/kernel/dtb/

## 6. Copy ATC3750-6C patch file to Linux_for_Tegra/rootfs directory

### 6-1. Copy ATC3750-6C_patch_v4.1.10.0/rootfs_patch/* to <install-path>/Linux_for_Tegra/rootfs
	$ sudo cp -RP ATC3750-6C_patch_v4.1.10.0/rootfs_patch/* <install-path>/Linux_for_Tegra/rootfs
 
### 6-2. Copy ATC3750-6C_patch_v4.1.10.0/FW/* to <install-path>/Linux_for_Tegra/rootfs/lib/firmware
        $ sudo cp -aRP ATC3750-6C_patch_v4.1.10.0/FW/* <install-path>/Linux_for_Tegra/rootfs/lib/firmware

### 6-3. Overwrite the kernel module from ATC3750-6C_patch_v4.1.10.0/module_patch
	$ sudo cp -af ATC3750-6C_patch_v4.1.10.0/module_patch/* <install-path>/Linux_for_Tegra/rootfs
	   
## 7. Update the initramfs, run the following commands:

### 7-1. $ cd <install-path>/Linux_for_Tegra
### 7-2. $ sudo depmod -b ./rootfs/ 5.15.148-tegra
### 7-3. $ sudo ./tools/l4t_update_initrd.sh
  
## 8. Flashing the Target Device or generate massflash package

### 8-1. Flashing the Target Device
 	$ cd <install-path>/Linux_for_Tegra/
	$ sudo ./flash.sh atc3750-6C-orin mmcblk0p1
### 8-2. (Option)Generate massflash package(Read <install-path>/Linux_for_Tegra/tools/kernel_flash/README_initrd_flash.sh for more details)

 	$ cp -af ATC3750-6C_patch_v4.1.10.0/package_atc3750-6C.sh <install-path>/Linux_for_Tegra/
	$ sudo -s
	$ bash ./package_atc3750-6C.sh
