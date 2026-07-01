[ATC356x Jetpack 6.2.2 Kernel Customization]

1. Linux_for_Tegra<br>
	a. Download driver package (BSP)<br>
		wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/release/Jetson_Linux_r36.5.0_aarch64.tbz2<br>
	b. Untar package<br>
		tar xf <Driver_Package><br>
	c. Download driver package sources<br>
		wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/sources/public_sources.tbz2<br>
	d. Untar sources<br>
		* tar xf <Driver_Sources> -C </install_path/Linux_for_Tegra/..><br>
		* cd <install_path>/Linux_for_Tegra/source<br>
		* tar xf kernel_src.tbz2<br>
		* tar xf kernel_oot_modules_src.tbz2<br>
		* tar xf nvidia_kernel_display_driver_source.tbz2<br>
<br>
2. Root filesystem<br>
	a. Clean rootfs's file<br>
		rm -rf <install_path>/Linux_for_Tegra/rootfs/*<br>
	b. Download sample root filesystem<br>
		wget https://developer.nvidia.com/downloads/embedded/l4t/r36_release_v5.0/release/Tegra_Linux_Sample-Root-Filesystem_r36.5.0_aarch64.tbz2<br>
	c. Untar sample root filesystem<br>
		sudo tar xpf <Sample_Root_Filesystem> -C Linux_for_Tegra/rootfs/<br>
<br>
3. Start build kernel & modules<br>
	a. Copy bsp patch<br>
		cp -a patch/bsp_patch/. Linux_for_Tegra/<br>
	b. Copy kernel patch<br>
		cp -a patch/kernel_patch/. <install-path>/Linux_for_Tegra/<kernel_sources_directory><br>
	c. Apply binaries<br>
		* cd Linux_for_Tegra/<br>
		* sudo ./apply_binaries.sh<br>
	d. Build kernel & in-tree modules<br>
		* (Reference : https://docs.nvidia.com/jetson/archives/r36.5/DeveloperGuide/SD/Kernel/KernelCustomization.html#building-the-jetson-linux-kernel)<br>
		1. Go to the build directory<br>
			cd <install-path>/Linux_for_Tegra/<kernel_sources_directory><br>
		2. Build<br>
			* export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-<br>
			* export KERNEL_DEF_CONFIG=atc3xxx_defconfig<br>
			* make -C kernel<br>
		3. Install the kernel & in-tree modules<br>
			* export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/<br>
			* sudo -E make install -C kernel<br>
			* cp kernel/kernel-jammy-src/arch/arm64/boot/Image <install-path>/Linux_for_Tegra/kernel/Image<br>
	e. Build the NVIDIA out-of-tree modules<br>
		1. Go to the build directory<br>
			cd <install-path>/Linux_for_Tegra/<kernel_sources_directory><br>
		2. Build<br>
			* export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-<br>
			* export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src<br>
			* make modules<br>
		3. Install<br>
			* export INSTALL_MOD_PATH=<install-path>/Linux_for_Tegra/rootfs/<br>
			* sudo -E make modules_install<br>
	f. Copy module patch to rootfs directory<br>
		* cp -a <path_to_patch>/module_patch/. <install-path>/Linux_for_Tegra/rootfs/<br>
		* depmod -a -b <install-path>/Linux_for_Tegra/rootfs/ 5.15.185-tegra<br>
	g. Update the initramfs<br>
		* cd <install-path>/Linux_for_Tegra<br>
		* sudo ./tools/l4t_update_initrd.sh<br>
<br>
4. Build the DTBs<br>
	a. Go to the build directory<br>
		cd <install-path>/Linux_for_Tegra/<kernel_sources_directory><br>
	b. Build<br>
		* export CROSS_COMPILE=<toolchain-path>/bin/aarch64-buildroot-linux-gnu-<br>
		* export KERNEL_HEADERS=$PWD/kernel/kernel-jammy-src<br>
		* make dtbs<br>
	c. Install<br>
		cp -a kernel-devicetree/generic-dts/dtbs/* <install-path>/Linux_for_Tegra/kernel/dtb/<br>

5. Run the script "package_atc356x.sh" in Linux_for_Tegra<br>

