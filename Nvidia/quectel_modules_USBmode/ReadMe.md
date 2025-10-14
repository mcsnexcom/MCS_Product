## change_USB_mode.sh
This script's main function is to switch the USB driver mode for cellular modems like the RM520N-GL and EM05-G. It accomplishes this by sending AT commands directly to the modem's communication port.

### Requires Root:
  - It first checks if it's being run by the root user, as this is necessary to communicate with device hardware.

> Mode 0 is for the qmi_wwan driver.
> Mode 2 is for the cdc_mbim driver.

### Reboots the Modem: 
  - After successfully changing the mode, it sends another AT command (AT+CFUN=1,1) to reset the modem, which is required to apply the new setting.
