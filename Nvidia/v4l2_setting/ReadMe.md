## v4l2set.sh
This is a straightforward, non-interactive script for applying a single, predefined configuration to one or more video devices.
You must provide the script with the path to the video devices you want to configure (e.g., bash v4l2set.sh /dev/video0 /dev/video1).

### **Applies a Fixed Preset:** 
  - It iterates through each specified device and uses v4l2-ctl to set a hardcoded list of parameters, including Wide Dynamic Range (WDR), shutter speed, gain, and white balance.
  This is useful for quickly setting multiple cameras to the exact same state for a specific task.

## v4l2_setmode.sh
This is a more flexible and user-friendly script that allows a user to apply one of two different camera setting profiles to a specific camera.

### **ANPR mode:** 
  - A detailed configuration for Automatic Number Plate Recognition, with specific settings for WDR, shutter, and white balance.
### **carDVR mode:** 
  - A much simpler configuration, likely for general-purpose recording in a vehicle.
### **Dual Operation:** 
The script can be used in two ways:
  - Interactive Menu: If run without arguments, it presents a text menu that guides the user to select a mode (ANPR or carDVR) and then choose which camera (1-4) to apply it to.
  - Command-Line Arguments: It can be run directly with arguments (e.g., bash v4l2_setmode.sh anpr 1) to apply a specific mode to a camera without the menu, making it suitable for automation.
