# `Please unzip the Driver after downloading`

## GMSL2 camera supported list:
| Camera Vendor | GMSL2 Model Name | Minimum Supported Version |
| :---- | :---- | :---- |
| e-con System | [STURDeCAM21](https://www.e-consystems.com/camera-modules/ip67-ar0233-gmsl2-hdr-camera.asp) <br> [STUDeCAM25](https://www.e-consystems.com/camera-modules/gmsl2-ar0234-global-shutter-camera.asp) <br> [STURDeCAM31](https://www.e-consystems.com/camera-modules/sony-isx031-ip69k-gmsl2-hdr-camera.asp) | v4.1.4.0 |
| ApproPho | [AP-AR0234](https://www.appropho.com/products_iii_en.html?pdid=151&type=36&cID=196) <br> [AP-IMX335](https://www.appropho.com/products_iii_en.html?pdid=150&type=36&cID=196) <br> [AP-IMX415](https://www.appropho.com/products_iii_en.html?pdid=149&type=36&cID=196) | v4.1.5.0 |
| Leopard Imaging | [LI-AR0234-OWL](https://leopardimaging.com/product/automotive-cameras/cameras-by-interface/adi-gmsl2-cameras/li-ar0234cs-gmsl2-owl/li-ar0234cs-gmsl2-owl/) <br> [LI-AR0234-HAWK](https://leopardimaging.com/product/automotive-cameras/cameras-by-interface/adi-gmsl2-cameras/li-ar0234cs-stereo-gmsl2/li-ar0234cs-stereo-gmsl2-30/) | v.4.1.6.0 |
| Stereolabs | [ZED-X](https://www.stereolabs.com/en-tw/store/products/zed-x-stereo-camera) | v4.1.10.0 |
| Sensing | [JSX031C-GMSL2F](https://www.sensing-world.com/en/h-pd-286.html) | v4.1.10.0|
| ORBBEC | [gemini-335lg](https://store.orbbec.com/products/gemini-335le) | 4.3.1.2 |

NOTED: The minimum supported version only allows for connection and use; some functions may be incomplete (e.g., synchronization, simultaneous operation of multiple cameras, etc.).


## **gmsl2_stream.sh**
This script is a diagnostic tool designed to view live video streams from currently connected and configured GMSL2 cameras. It uses the GStreamer multimedia framework to display the feed.

### **Functions:**
  - **Auto-Detects Camera Type:** The script first checks which camera driver module (e.g., nv_ar0234, ap_cam_gmsl) is active on the system.
  - **Builds a Custom GStreamer Pipeline:** Based on the detected driver, it automatically selects the correct GStreamer source element (nvarguscamerasrc, v4l2src, etc.) to build a valid command.
  - Interactive Resolution Selection: It lists the available resolutions for the camera(s) and prompts the user to choose one before starting the stream.
  - Launches Video Streams: It starts a separate GStreamer video stream for each detected video device (/dev/video*), overlaying the camera's number on the image for easy identification.

## **camera.sh**
This script is a user-friendly tool for installing the correct camera driver and device tree files for different camera models on specific hardware products.

### **Function:**
  - Product-Specific Menu: It first identifies the hardware it's running on (e.g., ATC3562 or ATC3750-8M) and then displays an interactive menu using the dialog utility, showing only the cameras compatible with that product.
  - Applies Configuration: Once the user selects a camera, the script copies the corresponding kernel driver files (.ko) and the appropriate Device Tree Overlay (.dtbo) file into the system's boot and module directories.
  - Prompts for Reboot: Since changes to kernel drivers and the device tree require a restart to take effect, the script asks the user if they want to shut down the system immediately after the files are applied.

## **ATC3750-8M_camera.sh**
This script is also for installing and configuring camera drivers, but it's specifically tailored for the ATC3750-8M product and uses a different method for applying the configuration.

### **Function:**
  - Modifies the Bootloader Configuration: Instead of just copying a DTBO file, its main action is to modify the /boot/extlinux/extlinux.conf file. It adds an OVERLAYS line that tells the bootloader to load the correct device tree overlay for the user-selected camera at boot time.
  - Command-Line Menu: It provides a simple text-based menu in the terminal (without using dialog) for the user to select from a list of compatible cameras.
  - Installs Drivers: Like the previous script, it also copies the necessary kernel driver files into the system and updates the module dependencies.
  - Requires Shutdown: It warns the user that a system shutdown is required to apply the changes and prompts for confirmation.


