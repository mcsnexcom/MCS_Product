# [ATC3750-8M Jetpack 5.1.1 Kernel Customization]
> Reference :
https://developer.nvidia.com/embedded/jetson-linux-r3531
https://docs.nvidia.com/jetson/archives/r35.3.1/DeveloperGuide/text/SD/Kernel/KernelCustomization.html#manually-downloading-and-expanding-kernel-sources

## 1. Linux_for_Tegra
### a. Download NVIDIA Jetson BSP
    $ wget https://developer.nvidia.com/downloads/embedded/l4t/r35_release_v3.1/release/jetson_linux_r35.3.1_aarch64.tbz2
### b. Untar NVIDIA Jetson BSP
		$ tar xvf <install-path>/jetson_linux_r35.3.1_aarch64.tbz2
### c. Download Driver Package Sources
		wget https://developer.nvidia.com/downloads/embedded/l4t/r35_release_v3.1/sources/public_sources.tbz2
### d. Untar Sources
		$ tar xvf <install-path>/public_sources.tbz2
		$ cd <install-path>/Linux_for_Tegra/source
		$ mv ./public/kernel_src.tbz2 ./
		$ tar xvf kernel_src.tbz2

## 2. Root Filesystem
### a. Remove Rootfs Text File
		$ rm -rf <install-path>/Linux_for_Tegra/rootfs/README.txt
### b. Download Sample Root Filesystem
		$ wget https://developer.nvidia.com/downloads/embedded/l4t/r35_release_v3.1/release/tegra_linux_sample-root-filesystem_r35.3.1_aarch64.tbz2
### c. Untar Sample Root Filesystem
		$ sudo tar xjpvf <install-path>/tegra_linux_sample-root-filesystem_r35.3.1_aarch64.tbz2 -C <install-path>/Linux_for_Tegra/rootfs/
### d. Apply Binaries
		$ cd <install-path>/Linux_for_Tegra
		$ sudo ./apply_binaries.sh
	
## 3. Start Build Kernel
### a. Download Cross Compile [Bootlin Toolchain gcc 9.3] : https://developer.nvidia.com/embedded/jetson-linux-r3531
		$ cd <install-path>
		$ mkdir toolchain
		$ tar xvf <install-path>/aarch64--glibc--stable-final.tar.gz -C <install-path>/toolchain
### b. Copy bsp patch
		$ cp -RP <install-path>/ATC3750-8M_patch_v2.2.0/bsp_patch/* <install-path>/Linux_for_Tegra/
### c. Copy kernel patch
		$ cp -af <install-path>/ATC3750-8M_patch_v2.2.0/kernel_patch/* <install-path>/Linux_for_Tegra/
### d. Build Kernel
> (Reference : https://docs.nvidia.com/jetson/archives/r35.3.1/DeveloperGuide/text/SD/Kernel/KernelCustomization.html#manually-downloading-and-expanding-kernel-sources)
		Build kernel example :
### I. Setting Kernel Config
        $ cd <install-path>
				$ make -C `pwd`/Linux_for_Tegra/source/kernel/kernel-5.10 ARCH=arm64 O=`pwd`/Linux_for_Tegra/source/build LOCALVERSION=-tegra 	CROSS_COMPILE=`pwd`/toolchain/bin/aarch64-buildroot-linux-gnu- atc3750-8M_defconfig
### II. Make image, dtbs, modules
				$ make -C `pwd`/Linux_for_Tegra/source/kernel/kernel-5.10 ARCH=arm64 O=`pwd`/Linux_for_Tegra/source/build LOCALVERSION=-tegra  CROSS_COMPILE=`pwd`/toolchain/bin/aarch64-buildroot-linux-gnu- -j$(nproc) Image
				$ make -C `pwd`/Linux_for_Tegra/source/kernel/kernel-5.10 ARCH=arm64 O=`pwd`/Linux_for_Tegra/source/build LOCALVERSION=-tegra  CROSS_COMPILE=`pwd`/toolchain/bin/aarch64-buildroot-linux-gnu- -j$(nproc) dtbs
				$ make -C `pwd`/Linux_for_Tegra/source/kernel/kernel-5.10 ARCH=arm64 O=`pwd`/Linux_for_Tegra/source/build LOCALVERSION=-tegra  CROSS_COMPILE=`pwd`/toolchain/bin/aarch64-buildroot-linux-gnu- -j$(nproc) modules

## 4. Modules Install
### a. Copy Module Patch
		$ cd <install-path>
		$ sudo cp -af <install-path>/ATC3750-8M_patch_v2.2.0/modules_patch/* <install-path>/Linux_for_Tegra/

### b. Install Modules
		$ sudo make -C `pwd`/Linux_for_Tegra/source/kernel/kernel-5.10 ARCH=arm64 O=`pwd`/Linux_for_Tegra/source/build LOCALVERSION=-tegra INSTALL_MOD_PATH=`pwd`/Linux_for_Tegra/source/modules -j$(nproc) modules_install
	
## 5. Copy Image,dtb,kernel driver
	$ sudo cp -rfv <install-path>/ATC3750-6C_patch_v2.2.0/kernel/Image <install-path>/Linux_for_Tegra/kernel/
	$ sudo cp -rfv <install-path>/Linux_for_Tegra/source/build/arch/arm64/boot/dts/nvidia/* <install-path>/Linux_for_Tegra/kernel/dtb/
	$ sudo cp -af <install-patch>/Linux_for_Tegra/source/build/arch/arm64/boot/dts/nvidia/tegra234-p3701-0004-atc3750-8M-sturdecam* <install-patch>/Linux_for_Tegra/rootfs/boot
	$ sudo cp -af <install-patch>/Linux_for_Tegra/source/build/arch/arm64/boot/dts/nvidia/tegra234-p3701-0005-atc3750-8M-sturdecam* <install-patch>/Linux_for_Tegra/rootfs/boot
	$ sudo cp -rfv <install-path>/Linux_for_Tegra/source/modules/lib <install-path>/Linux_for_Tegra/rootfs/usr/
	$ sudo cp -af <install-path>/ATC3750-8M_patch_v2.2.0/rootfs_patch/* <install-path>/Linux_for_Tegra/rootfs/
	
	
## 6. *(option) Generate massflash package(Read <install-path>/Linux_for_Tegra/tools/kernel_flash/README_initrd_flash.txt for more details)
 	$ cp -af <install-path>/ATC3750-8M_patch_v2.2.0/package_atc3750-8M.sh <install-path>/Linux_for_Tegra/
	$ sudo -s && cd <install-path>/Linux_for_Tegra/
	$ bash ./package_atc3750-8M.sh
