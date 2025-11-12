# **[ATC3750-6C Kernel Customization] - Jetpack 6.0(GA2)**
> Reference : https://docs.nvidia.com/jetson/archives/r36.3/DeveloperGuide/SD/Kernel/KernelCustomization.html#to-manually-download-and-expand-the-kernel-sources

## 1. Locate and download the Jetson Linux source files for your release.
    https://developer.nvidia.com/embedded/jetson-linux-r363
### 1-1. Extract the .tbz2 file
	   $ tar xf public_sources.tbz2 -C <install-path>/Linux_for_Tegra/..
### 1-2. Extract the kernel and the NVIDIA out-of-tree modules source files
     $ cd <install-path>/Linux_for_Tegra/source
	   $ tar xf kernel_src.tbz2
	   $ tar xf kernel_oot_modules_src.tbz2
	   $ tar xf nvidia_kernel_display_driver_source.tbz2
### 1-3. Extract the sample rootfs and launch apply_binaries.sh   
     $ sudo tar -C <install-path>/Linux_for_Tegra/rootfs -jpxvf <install-path>/Tegra_Linux_Sample-Root-Filesystem_R36.3.0_aarch64.tbz2
	   $ cd <install-path>/Linux_for_Tegra/
	   $ sudo ./apply_binaries.sh

## 2. Copy ATC3750-6C patch file to Linux_for_Tegra BSP directory
### 2-1. Extract ATC3750-6C_patch_v4.0.3.0.tar.gz
       $ tar xvf ATC3750-6C_patch_v4.0.3.0.tar.gz
### 2-2. Copy ATC3750-6C_patch_v4.0.3.0/bsp_patch/* to <install-path>/Linux_for_Tegra
       $ sudo cp -aRP ATC3750-6C_patch_v4.0.3.0/bsp_patch/* <install-path>/Linux_for_Tegra
### 2-3. Copy ATC3750-6C_patch_v4.0.3.0/kernel_patch/* to <install-path>/Linux_for_Tegra
       $ sudo cp -af ATC3750-6C_patch_v4.0.3.0/kernel_patch/* <install-path>/Linux_for_Tegra

## 3. Building the Jetson Linux Kernel(in-tree)
### 3-1. Go to the build directory:
       $ cd <install-path>/Linux_for_Tegra/source
### 3-2. Run the following commands to build the Jetson Linux kernel and its in-tree modules:
	   $ export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-
	   $ make KERNEL_DEF_CONFIG=atc3750-6C_defconfig -C kernel
### 3-3. If the previous step is successful, overwrite the kernel module from ATC3750-6C_patch_v4.0.3.0/module_patch
	   $ sudo cp -af ATC3750-6C_patch_v4.0.3.0/kernel_patch/* <install-path>/Linux_for_Tegra/
### 3-4. Run the following commands to install the kernel and in-tree modules:  
	   $ export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
	   $ sudo -E make install -C kernel
	   $ cp kernel/kernel-jammy-src/arch/arm64/boot/Image <install-path>/Linux_for_Tegra/kernel/Image
	   
## 4. Building the NVIDIA Out-of-Tree Modules
### 4-1. Go to the build directory:
	   $ cd <install-path>/Linux_for_Tegra/source
### 4-2. Run the following commands to build:
	   $ export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-
	   $ export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
	   $ make modules
### 4-3. Run the following commands to install:
	   $ export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
	   $ sudo -E make modules_install

## 5. Building the DTBs
### 5-1. Go to the build directory:
	   $ cd <install-path>/Linux_for_Tegra/source
### 5-2. Run the following commands to build:
	   $ export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-
	   $ export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
	   $ make dtbs
### 5-3. Run the following commands to install:
	   $ cp nvidia-oot/device-tree/platform/generic-dts/dtbs/* <install-path>/Linux_for_Tegra/kernel/dtb/   

## 6. Copy ATC3750-6C patch file to Linux_for_Tegra/rootfs directory
### 6-1. Copy ATC3750-6C_patch_v4.0.3.0/rootfs_patch/* to <install-path>/Linux_for_Tegra/rootfs
	   $ sudo cp -RP ATC3750-6C_patch_v4.0.3.0/rootfs_patch/* <install-path>/Linux_for_Tegra/rootfs
	   
## 7. Flashing the Target Device or generate massflash package
### 7-1. Flashing the Target Device
 	   $ cd <install-path>/Linux_for_Tegra/
	   $ sudo ./flash.sh atc3750-6C-orin mmcblk0p1
### 7-2. Generate massflash package(Read <install-path>/Linux_for_Tegra/tools/kernel_flash/README_initrd_flash.txt for more details)
 	   $ cp -af ATC3750-6C_patch_v4.0.3.0/package_atc3750-6C.sh <install-path>/Linux_for_Tegra/
	   $ sudo -s
	   $ bash ./package_atc3750-6C.sh
