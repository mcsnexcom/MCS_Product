/**
 * The program for flashing MCU/CAN device.
 * 
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	4/9 2020
 */
#include "init.h"

/**
 * The callback function which get event or can data from MCU/CAN.
 *
 * @param callback_data the structure of callback data
 */
void callback_gotEventData(CALLBACK_DATA callback_data) {
	//do nothing
}

/**
 * Main function.
 */
int main(int argc, char *argv[]) {
	// To register sys log(optional)
	openlog("MCU/CAN UPDATE", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "Flash MCU/CAN start ...");

	if (argc > 1 && !strcmp(argv[1], "help")) {
		printf("****************************************************************\n");
		printf("[Init MCU/CAN device from shell]\n");
		printf("[Usage] ./mcu_upd [help | [{Device Type} {BaudRate} {Device Name}] [{CAN/POE MCU Type} [Prod Name]]]\n");
		printf("[Usage] {Device Type}  0:MCU / 1:CAN\n");
		printf("[Usage] {CAN/POE MCU Type} ST / NXP\n");
		printf("[Example 1] ./mcu_upd                                   (init MCU/CAN device from config file)\n");
		printf("[Example 2] ./mcu_upd 0 115200 /dev/ttyS4               (/dev/ttyS4   is a MCU Device, but MCU function depended on config file)\n");
		printf("[Example 3] ./mcu_upd 1 115200 /dev/ttyUSB0 NXP         (/dev/ttyUSB0 is a NXP CAN Device)\n");
		printf("[Example 4] ./mcu_upd 0 115200 /dev/ttyUSB0 ST  VMD3002 (/dev/ttyUSB0 is VMD3002)\n");
		printf("****************************************************************\n");
		exit(0);
	}

#if 1
	system("setserial /dev/ttyS4 uart 16550 baud_base 115200");
	system("stty -F /dev/ttyS4 115200");
#endif
	// ###### To init MCU or CAN {N} and others [START] ######
	// To include registerring CallBack function of MCU/CAN Event or data.
	//            initiating the command pool
	FILE *fConfig = LAUNCH_INIT_CONFIG(argc, argv);
	if (fConfig == NULL) {
		syslog(LOG_ERR, "Configuration error");
		closelog();
		exit(EXIT_FAILURE);
	}

	// ###### To init MCU or CAN {N} and others [END] ######
	LAUNCH_MCU_GET_NVARM("ST_IAP_START");
	
	// ###### To exit the program [START] ######
	LAUNCH_EXIT("CONFIG_MAIN_EXIT", NULL, 0);
	// ###### To exit the program [END] ######

	// To unregister sys log(optional)
	syslog(LOG_INFO, "Flash MCU/CAN close ...");
	closelog();

	exit(EXIT_SUCCESS);
}
