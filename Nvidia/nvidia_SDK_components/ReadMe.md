## build_install_opencv.sh
This script automates the process of building and installing OpenCV version 4.10.0 from source code. Its main purpose is to create a custom OpenCV build specifically configured to use NVIDIA's CUDA and cuDNN libraries, which enables GPU acceleration for computer vision tasks.
  ### **Key points:**
  - Removes any existing OpenCV versions to prevent conflicts.
  - Installs all necessary dependencies, like build tools and libraries for handling various media formats (GStreamer, libv4l, etc.).
  - Downloads the source code for both OpenCV and its companion opencv_contrib repository.
  - Configures and compiles the code with flags that enable support for CUDA, cuDNN, GStreamer, and Python 3.
  - Installs the newly built library and updates system environment variables so applications can find it.

## install_sdk.sh
This script functions as an installer for the NVIDIA JetPack SDK on a compatible device (like an NVIDIA Jetson). It's designed to be run with root privileges.
  ### **Key points:**
  - Checks for prerequisites, ensuring it's run by the root user and that there's at least 10 GB of free disk space.
  - Installs the nvidia-jetpack meta-package, which bundles essential NVIDIA software like CUDA, cuDNN, TensorRT, and others needed for high-performance computing and AI.
  - Optionally installs DeepStream, an SDK for building intelligent video analytics (IVA) pipelines. It finds the available version and asks the user for confirmation before installing it.

# ATC Series OTA Update

\[\!IMPORTANT\]  
Updates are only provided within the same JetPack version. Nexcom OS currently does NOT support cross-version JetPack upgrades (e.g., upgrading from JetPack 6.1 to JetPack 6.2).

## OTA Support Status Table

| OTA Payload Package Name | Rootfs Update Block | Nexcom OS Version | Support Status |
| :---- | :---- | :---- | :---- |
| ATC3750\_6C\_v4.1.10.0\_ota\_payload\_package.tar.gz | eMMC | $v4.1.x.x \\to v4.1.10.0$ | ☑ |
| ATC3750\_8M\_v4.1.10.0\_ota\_payload\_package.tar.gz | eMMC | $v4.1.x.x \\to v4.1.10.0$ | ☑ |
| ATC3750\_NVMe\_6C\_v4.1.10.0\_ota\_payload\_package.tar.gz | NVMe | $v4.1.x.x \\to v4.1.10.0$ | ☑ |
| ATC3750\_NVMe\_8M\_v4.1.10.0\_ota\_payload\_package.tar.gz | NVMe | $v4.1.x.x \\to v4.1.10.0$ | ☑ |
| ATC356x\_v4.2.5.0\_ota\_payload\_package.tar.gz | NVMe | $v4.2.x.x \\to v4.2.5.0$ | ☑ |

* **Nexcom OS v4.1.x.x** corresponds to JetPack 6.1 BSP.  
* **Nexcom OS v4.2.x.x** corresponds to JetPack 6.2 BSP.

### **1 Preparing the OTA Payload Package**

1. Contact the **Nexcom FAE Team** to obtain:  
   * \<atc\_rel\>\_ota\_payload\_package.tar.gz  
   * ota\_tools\_\<rel\>\_aarch64.tbz2

\[\!WARNING\]  
Do NOT download ota\_tools directly from NVIDIA Jetson Linux, as this may result in an incomplete update\!

2. Set up the working directory:  
   mkdir \-p /home/${USER}/work\_dir  
   export WORKDIR=/home/${USER}/work\_dir

3. Unpack the OTA tools:  
   sudo tar \-C $WORKDIR \-xvf ota\_tools\_\<rel\>\_aarch64.tbz2

4. Create the /ota/ directory and place the payload package inside:  
   sudo mkdir \-p /ota/  
   sudo mv /home/${USER}/\<atc\_rel\>\_ota\_payload\_package.tar.gz /ota/

### **2 Backing up and Restoring Files**

NVIDIA's OTA update overwrites the rootfs. To preserve specific data, edit the backup list:

1. Open the configuration file:  
   $WORKDIR/Linux\_for\_Tegra/tools/ota\_tools/version\_upgrade/ota\_backup\_files\_list.txt  
2. Add paths of files or directories you wish to keep (use absolute paths).  
   Example items already included:  
   * /etc/passwd, /etc/shadow  
   * /home/  
   * /etc/NetworkManager/system-connections/  
   * /var/lib/nvpmodel/  
   * /nexcom/camera/nexcom\_cam\_setting

### **3 Start the OTA Update**

1. Navigate to the tool directory:  
   cd ${WORKDIR}/Linux\_for\_Tegra/tools/ota\_tools/version\_upgrade

2. Trigger the update:  
   sudo ./nv\_ota\_start.sh /ota/\<atc\_rel\>\_ota\_payload\_package.tar.gz

\[\!CAUTION\]  
If you see a "storage-type mismatch" error, ensure you are using the correct package (eMMC vs. NVMe) for your specific hardware configuration.

### **4 Update Bootloader (For Orin-NX & Orin-Nano)**

If using **Orin-NX** or **Orin-Nano** and you need to update UEFI:

sudo nv\_bootloader\_capsule\_updater.sh \-q /\<ota\_payload\>/TEGRA\_BL.Cap

*Note: For **AGX Orin**, this is already included in the nv\_ota\_start.sh script.*

### **5 Reboot System**

After triggering the update, reboot to begin the installation:

sudo reboot \-h now

### **6 Updating Bootloader and Rootfs**

* **Serial Console:** You can observe the update progress via the serial console (except on ATC3750-IP7-8M).  
* **Progress:** The system will show "Update Progress \- 100%" and then reboot automatically.

\[\!DANGER\]  
DO NOT POWER OFF the device or interrupt the process during the update\! Any unexpected shutdown can cause system failure and permanent data loss.

### **7 Check OTA Update Result**

1. **Logs:** Check the directory /last\_ota\_update\_log for detailed success/failure logs.  
2. **Version Check:** Verify the updated version:  
   cat /etc/image\_version

   Confirm it matches the version of the \<atc\_rel\> package you used.

**Reference:** [NVIDIA OTA Update Documentation](https://www.google.com/search?q=https://docs.nvidia.com/jetson/archives/r36.4.3/DeveloperGuide/SD/SoftwarePackagesAndTheUpdateMechanism.html%23steps-performed-on-the-jetson-device)
