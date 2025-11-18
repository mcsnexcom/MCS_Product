# **[ATC3540 Jetpack 5.1.2 Kernel Customization]**

## 1.untar patch.tar.gz
	tar xpvf ATC3540_patch_v3.9.0.tar.gz
	
## 2.Copy patch/bsp_patch/* to <BSP_DIR>
	sudo cp -a patch/bsp_patch/* $HOME/<BSP_DIR>
**NOTED : (<BSP_DIR> is Download from {Driver Package (BSP)}: https://developer.nvidia.com/embedded/jetson-linux-r3541)**

## 3.Copy patch/kernel_patch/* to <KERNEL_DIR>
	sudo cp -a patch/kernel_patch/* $HOME/<KERNEL_DIR>
**NOTED: (<KERNEL_DIR> is Download from {Driver Package (BSP) Sources}: https://developer.nvidia.com/embedded/jetson-linux-r3541)**

## 4.Start build kernel
> (Reference : https://docs.nvidia.com/jetson/archives/r35.4.1/DeveloperGuide/text/SD/Kernel/KernelCustomization.html#manually-downloading-and-expanding-kernel-sources)

Build kernel example :
### 1. export variables
			export WORKDIR="$(pwd)"
			export DEFCONFIG="atc3540_defconfig"
			export TOOLCHAIN_PREFIX="${WORKDIR}/toolchain/bin/aarch64-buildroot-linux-gnu-"
			export JETSON_AGX_ORIN_KERNEL_SOURCES="${WORKDIR}/Linux_for_Tegra/sources"
			export TEGRA_KERNEL_OUT="$JETSON_AGX_ORIN_KERNEL_SOURCES/build"
			export KERNEL_MODULES_OUT="$JETSON_AGX_ORIN_KERNEL_SOURCES/modules"
### 2. Run config
			sudo make -C sources/kernel/kernel-5.10 ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra CROSS_COMPILE=${TOOLCHAIN_PREFIX} ${DEFCONFIG}
### 3. Make image、dtbs、modules
			sudo make -C sources/kernel/kernel-5.10 ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra CROSS_COMPILE=${TOOLCHAIN_PREFIX} -j$(nproc) Image	
			sudo make -C sources/kernel/kernel-5.10 ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra CROSS_COMPILE=${TOOLCHAIN_PREFIX} -j$(nproc) dtbs
			sudo make -C sources/kernel/kernel-5.10 ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra CROSS_COMPILE=${TOOLCHAIN_PREFIX} -j$(nproc) modules
### 4. Module install
			sudo make -C sources/kernel/kernel-5.10 ARCH=arm64 O=$TEGRA_KERNEL_OUT LOCALVERSION=-tegra INSTALL_MOD_PATH=$KERNEL_MODULES_OUT modules_install
### 5. Copy files
			sudo cp -rfv $JETSON_AGX_ORIN_KERNEL_SOURCES/build/arch/arm64/boot/Image kernel/
			sudo cp -rfv $JETSON_AGX_ORIN_KERNEL_SOURCES/build/arch/arm64/boot/dts/nvidia/* kernel/dtb/
			sudo cp -arfv $JETSON_AGX_ORIN_KERNEL_SOURCES/modules/lib rootfs/usr/
	
5.Copy patch/module_patch/modules/* to <top>/Linux_for_Tegra/rootfs/
	Notice:
		* If ignore this step, Orin-NX may shows a black screen.
		* module_patch also contains customized .ko files (e.g. GobiSerial.ko、qmi_wwan.ko...)

	sudo cp -a patch/module_patch/*  <top>/Linux_for_Tegra/rootfs/
	depmod -a -b <top>/Linux_for_Tegra/rootfs/ 5.10.120-tegra
	check modules.dep contain these depends
		• extra/opensrc-disp/nvidia-modeset.ko: extra/opensrc-disp/nvidia.ko
		• extra/opensrc-disp/nvidia-drm.ko: extra/opensrc-disp/nvidia-modeset.ko extra/opensrc-disp/nvidia.ko
		• extra/opensrc-disp/nvidia.ko:
> (Reference : https://docs.nvidia.com/jetson/archives/r35.4.1/DeveloperGuide/text/SD/Kernel/KernelCustomization.html#to-build-display-kernel-modules)
	
6.Run the script "package_atc3540.sh" in bsp_patch 
