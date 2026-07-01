[ATC356x Jetpack 6.2.2 Kernel Customization]

## 1. Linux_for_Tegra
### a. Download driver package (BSP)
	wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/release/Jetson_Linux_r36.5.0_aarch64.tbz2
### b. Untar package<br>
	tar xf <Driver_Package><br>
### c. Download driver package sources
	wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/sources/public_sources.tbz2
### d. Untar sources<br>
	* tar xf <Driver_Sources> -C </install_path/Linux_for_Tegra/..>
	* cd <install_path>/Linux_for_Tegra/source
	* tar xf kernel_src.tbz2
	* tar xf kernel_oot_modules_src.tbz2
	* tar xf nvidia_kernel_display_driver_source.tbz2

## 2. Root filesystem
### a. Clean rootfs's file
	rm -rf <install_path>/Linux_for_Tegra/rootfs/*
### b. Download sample root filesystem<br>
	wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/release/Tegra_Linux_Sample-Root-Filesystem_r36.5.0_aarch64.tbz2
### c. Untar sample root filesystem
	sudo tar xpf <Sample_Root_Filesystem> -C Linux_for_Tegra/rootfs/

## 3. Start build kernel & modules
### a. Copy bsp patch
	cp -a patch/bsp_patch/. Linux_for_Tegra/
### b. Copy kernel patch
	cp -a patch/kernel_patch/. <install-path>/Linux_for_Tegra/<kernel_sources_directory>
### c. Apply binaries
	* cd Linux_for_Tegra/
	* sudo ./apply_binaries.sh
### d. Build kernel & in-tree modules 
> (Reference : https://docs.nvidia.com/jetson/archives/r36.5/DeveloperGuide/SD/Kernel/KernelCustomization.html#building-the-jetson-linux-kernel)
#### 1. Go to the build directory
		cd <install-path>/Linux_for_Tegra/<kernel_sources_directory>
#### 2. Build
		* export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-
		* export KERNEL_DEF_CONFIG=atc3xxx_defconfig
		* make -C kernel
#### 3. Install the kernel & in-tree modules
		* export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
		* sudo -E make install -C kernel
		* cp kernel/kernel-jammy-src/arch/arm64/boot/Image <install-path>/Linux_for_Tegra/kernel/Image
###	e. Build the NVIDIA out-of-tree modules
#### 1. Go to the build directory
		cd <install-path>/Linux_for_Tegra/<kernel_sources_directory>
#### 2. Build
		* export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-
		* export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
		* make modules
#### 3. Install
		* export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/
		* sudo -E make modules_install
### f. Copy module patch to rootfs directory
		* cp -a <path_to_patch>/module_patch/. <install-path>/Linux_for_Tegra/rootfs/
		* depmod -a -b <install-path>/Linux_for_Tegra/rootfs/ 5.15.185-tegra
### g. Update the initramfs
		* cd <install-path>/Linux_for_Tegra
		* sudo ./tools/l4t_update_initrd.sh

## 4. Build the DTBs
### a. Go to the build directory
	cd <install-path>/Linux_for_Tegra/<kernel_sources_directory>
### b. Build
	* export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-
	* export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src
	* make dtbs
### c. Install
	cp -a kernel-devicetree/generic-dts/dtbs/* <install-path>/Linux_for_Tegra/kernel/dtb/

## 5. Run the script "package_atc356x.sh" in Linux_for_Tegra

