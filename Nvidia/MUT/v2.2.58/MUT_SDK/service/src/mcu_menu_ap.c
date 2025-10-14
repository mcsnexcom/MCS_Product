/**
 * The program with function menu for accessing MCU.
 *
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	10/07 2020
 */
#include "init.h"
#include "AP_MENU_LIB.h"

struct timeval start1, end1; // test the throughput(received)
long time_use = 0;			 // test the throughput(time used)
struct timeval tv;

/**
 * The callback function which get event or can data from MCU/CAN.
 *
 * @param callback_data the structure of callback data
 */
void callback_gotEventData(CALLBACK_DATA callback_data) {

#if 0
	///*
	receiveCANDataCountOnAP++;
	gettimeofday(&end1, NULL);
	time_use = ((end1.tv_sec - start1.tv_sec) * 1000) + ((end1.tv_usec - start1.tv_usec) / 1000);
	if(time_use == 60000) { // 60 seconds
		printf("The total received data is %d, time used: %d ms.\n", receiveCANDataCountOnAP, time_use);
	}
#endif

#if 1
	int i;
	switch (callback_data.type) {
#if defined(MCU) | defined(ALL)
		case EVENT_TYPE_SYSTEM:
			printf("\n\tfd(%d) Receive (EVENT_TYPE_SYSTEM) => ", callback_data.fd);
			for (i = 0; i < callback_data.szDataLength; i++)
				printf("0x%02X ", callback_data.szData[i]);
			printf("\n");
			break;
		case MCU_TYPE_CUSTOMISE:
			for (i = 0; i < nWheelNumber; i++) {
				if (callback_data.szData[3] == TPMS_Data[i].SensorID[0] &&
					callback_data.szData[4] == TPMS_Data[i].SensorID[1] &&
					callback_data.szData[5] == TPMS_Data[i].SensorID[2] &&
					callback_data.szData[6] == TPMS_Data[i].SensorID[3]) {
					TPMS_Data[i].temp = callback_data.szData[7];
					TPMS_Data[i].psi  = callback_data.szData[8];
					TPMS_Data[i].vol  = callback_data.szData[9];
				}
				float fVol = TPMS_Data[i].vol / 50;
				printf("fd(%d) Wheel %d => T=%d, psi=%d, V=%1.1f\n", callback_data.fd, i, (TPMS_Data[i].temp - 25), TPMS_Data[i].psi, fVol);
			}
			break;
#endif
#if defined(CAN) | defined(ALL)
		case EVENT_TYPE_CAN:
			gettimeofday(&tv, NULL);
			receiveCANDataCountOnAP++;
			printf("(%ld.%ld) [REVEIVE] (LIB)receiveCount: %lu, (LIB)receiveErrorCount: %u, (AP)receiveCount: %u, (LIB)sendCommandSuccessCount: %lu, (LIB)sendCommandErrorCount: %u,(LIB)sendCommandTimeCount: %d\nfd(%d) => ID(0x%x), RTR(%d), IDE(%d), Len(%d), Data1~8(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)\n", tv.tv_sec, tv.tv_usec, callback_data.receiveCANDataCount, callback_data.receiveErrorCount, receiveCANDataCountOnAP, callback_data.sendCommandSuccessCount, callback_data.sendCommandErrorCount, callback_data.sendCommandTimeCount, callback_data.fd, callback_data.canData.id, callback_data.canData.rtr, callback_data.canData.ide, callback_data.canData.dlc, callback_data.canData.data[0], callback_data.canData.data[1], callback_data.canData.data[2], callback_data.canData.data[3], callback_data.canData.data[4], callback_data.canData.data[5], callback_data.canData.data[6], callback_data.canData.data[7]);
			break;
#endif
	}
#endif

}

/**
 * To find the function pointer by the function(key) name
 *
 * @param *keyName the pointer of function(key) name
 *
 * @return the pointer of function
 */
handleFun findFunByKey(char *keyName) {
	int i;
	handleFun tmpFun = NULL;
	for (i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++) {
		if (!strcmp(function_map[i].name, keyName)) {
			tmpFun = function_map[i].func;
			break;
		}
	}

	return tmpFun;
}

/**
 * Main function.
 */
int main(int argc, char *argv[]) {
	// To register sys log(optional)
	/*
	openlog("MCU MENU AP", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "MCU MENU AP start ...");
	*/

	if (argc > 1 && !strcmp(argv[1], "help")) {
		printf("****************************************************************\n");
		printf("[Init MCU/CAN device from shell]\n");
		printf("[Usage] ./mcu_menu_ap [help | [{Device Type} {BaudRate} {Device Name}] [{CAN/POE MCU Type} [Prod Name]]]\n");
		printf("[Usage] {Device Type}  0:MCU / 1:CAN\n");
		printf("[Usage] {CAN/POE MCU Type} ST / NXP\n");
		printf("[Example 1] ./mcu_menu_ap                                   (init MCU/CAN device from config file)\n");
		printf("[Example 2] ./mcu_menu_ap 0 115200 /dev/ttyS4               (/dev/ttyS4   is a MCU Device, but MCU function depended on config file)\n");
		printf("[Example 3] ./mcu_menu_ap 1 115200 /dev/ttyUSB0 NXP         (/dev/ttyUSB0 is a NXP CAN Device)\n");
		printf("[Example 4] ./mcu_menu_ap 0 115200 /dev/ttyUSB0 ST  VMD3002 (/dev/ttyUSB0 is VMD3002)\n");
		printf("****************************************************************\n");
		exit(0);
	}

	// ###### To init MCU or CAN {N} and others [START] ######
	// To include registerring CallBack function of MCU/CAN Event or data.
	//            initiating the command pool
	FILE *fConfig = LAUNCH_INIT_CONFIG(argc, argv);
	if (fConfig == NULL)
		return -1;
	// ###### To init MCU or CAN {N} and others [END] ######

	// ###### To initiate the settings of MENU [START] ######
	char mPath[strlen(pFolder) + strlen(szProductName) + strlen("_M")];
	szProductName[strlen(szProductName) - 1] = '\0';
	snprintf(mPath, sizeof(mPath), "%s%s%s", pFolder, szProductName, "_M");
	FILE *mConfig = fopen(mPath, "r");
	if (fConfig == NULL) {
		syslog(LOG_ERR, "Can't find any menu configuration file, please check menu configuration file exist or not");
		syslog(LOG_INFO, "MCU AP close ...");
		return -1;
	}
	INIT_UI_MENU(mConfig, findCommandIndex, findFunByKey);
	fclose(mConfig);
	// ###### To initiate the settings of MENU [END] ######

	// ###### To exit the program [START] ######
	LAUNCH_EXIT("CONFIG_MAIN_EXIT", fConfig, 1);
	// ###### To exit the program [END] ######

	// To unregister sys log(optional)
	/*
	syslog(LOG_INFO, "MCU MENU AP close ...");
	closelog();
	*/

	exit(EXIT_SUCCESS);
}
