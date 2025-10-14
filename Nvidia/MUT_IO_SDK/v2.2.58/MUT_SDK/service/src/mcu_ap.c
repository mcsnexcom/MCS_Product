/**
 * The program without function menu for accessing MCU.
 *
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	10/07 2020
 */
#include "init.h"

struct timeval start1, end1; // test the throughput(received)
long time_use = 0;			 // test the throughput(time used)

bool EXIT_LOOP = false;

/**
 * Handling the signal from key event(ctrl+c).
 *
 * @param sign_no The number of signal
 */
void handle_signal_from_keyevent(int sign_no) {
	printf("The total received data is %d.\n", receiveCANDataCountOnAP);
    printf("\nReceiving signal from key event. The signal no is %d.\n", sign_no);
    EXIT_LOOP = true;
}

/**
 * The callback function which get event or can data from MCU/CAN.
 *
 * @param callback_data the structure of callback data
 */
void callback_gotEventData(CALLBACK_DATA callback_data) {

#if 1
	///*
	receiveCANDataCountOnAP++;
	gettimeofday(&end1, NULL);
	time_use = ((end1.tv_sec - start1.tv_sec) * 1000) + ((end1.tv_usec - start1.tv_usec) / 1000);
	if(time_use == 60000) { // 60 seconds
		printf("The total received data is %d, time used: %d ms.\n", receiveCANDataCountOnAP, time_use);
		EXIT_LOOP = true;
	}
#endif

#if 0
	int i;
	switch (callback_data.type) {
#if defined(MCU) | defined(ALL)
		case EVENT_TYPE_SYSTEM:
			printf("fd(%d) Receive => ", callback_data.fd);
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
			receiveCANDataCountOnAP++;
			//printf("[REVEIVE] (LIB)receiveCount: %lu, (LIB)receiveErrorCount: %u, (AP)receiveCount: %u, (LIB)sendCommandSuccessCount: %lu, (LIB)sendCommandErrorCount: %u,(LIB)sendCommandTimeCount: %d\nfd(%d) => ID(0x%x), RTR(%d), IDE(%d), Len(%d), Data1~8(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)(0x%x)\n", callback_data.receiveCANDataCount, callback_data.receiveErrorCount, receiveCANDataCountOnAP, callback_data.sendCommandSuccessCount, callback_data.sendCommandErrorCount, callback_data.sendCommandTimeCount, callback_data.fd, callback_data.canData.id, callback_data.canData.rtr, callback_data.canData.ide, callback_data.canData.dlc, callback_data.canData.data[0], callback_data.canData.data[1], callback_data.canData.data[2], callback_data.canData.data[3], callback_data.canData.data[4], callback_data.canData.data[5], callback_data.canData.data[6], callback_data.canData.data[7]);
			break;
#endif
	}
#endif

}

/**
 * Main function.
 */
int main(int argc, char *argv[]) {
	int result = 0, DataInLength = 0, DataOutLength = 0;
	BYTE DataIn[128], DataOut[128];

	// To register sys log(optional)
	/*
	openlog("MCU AP", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "MCU AP start ...");
	*/

	// To register the key event
	signal(SIGINT, handle_signal_from_keyevent);

	// ###### To init MCU or CAN {N} and others [START] ######
	// Initiating MCU (the definition of arguments , please see init.h)
	printf("The result of initiating MCU is %d.\n", LAUNCH_INIT_DEV(NULL, 0, "/dev/ttyS4", 115200, -1));
	// Initiating CAN 1 (the definition of arguments , please see init.h)
	//printf("The result of initiating CAN 1 is %d.\n", LAUNCH_INIT_DEV(NULL, 1, "/dev/ttyS3", 115200, 0));
	// Initiating CAN 2 (the definition of arguments , please see init.h)
	//printf("The result of initiating CAN 2 is %d.\n", LAUNCH_INIT_DEV(NULL, 1, "/dev/ttyS5", 115200, 0));
	// Registerring CallBack function of MCU/CAN Event or data.
	Register_MCU_EventCallBack(1, 1, callback_gotEventData);
	// Initiating the command pool
	INIT_CMD_POOL();
	// ###### To init MCU or CAN {N} and others [END] ######

	// ###### To launch MCU or CAN command [START] ######
	// To retrive the USB 3.0 status from MCU
	///*
	//

//int i=0, count_s=0, count_f=0;
//for (i=0; i<5000; i++)
//{
	int res;
	res = LAUNCH_MCU_COMMAND("ST_SYSTEM_GET_01_01_MCU_VERSION", DataIn, DataInLength, DataOut, &DataOutLength);
	if(res > 0)
	{
		printf("MCU version = %d\n", DataOut[0]);
//		count_s++;
	}
	else
	{
		printf("Get MCU version failure.\n");
//		count_f++;
	}
//}
//printf("SUCCESS: %d, FAIL:%d\n", count_s, count_f);

#if 0
	DataInLength=0;
	DataOut[0]=0x00;
	if(LAUNCH_MCU_COMMAND("ST_SYSTEM_GET_0A_01_IGNITION_STATUS", DataIn, DataInLength, DataOut, &DataOutLength) > 0)
	{
		if(DataOut[0])
			printf("Ignition ON, DataOut = %#x\n", DataOut[0]);
		else
			printf("Ignition OFF, DataOut = %#x\n", DataOut[0]);
	}
	else
		printf("Get Ignition failure.\n");
#endif
	//*/
	// To retrive the firmware version of CAN 1(default is CAN 1 when initiated multiple CAN devices)
	/*
	if (LAUNCH_CAN_COMMAND("NXP_CAN_AP_02_READ_FW_VERSION", DataIn, DataInLength, DataOut, &DataOutLength)) {
		printf("The address is %02X.\n", DataOut[0]);
		printf("The F/W version of CAN 1 is %02X.\n", DataOut[1]);
	}
	*/
	// To switch CAN 2
	//switchCAN(2);
	// To retrive the firmware version of CAN 1(default is CAN 1 when initiated multiple CAN devices)
	/*
	if (LAUNCH_CAN_COMMAND("NXP_CAN_AP_02_READ_FW_VERSION", DataIn, DataInLength, DataOut, &DataOutLength)) {
		printf("The address is %02X.\n", DataOut[0]);
		printf("The F/W version of CAN 2 is %02X.\n", DataOut[1]);
	}
	*/
	// To switch CAN 1
	//switchCAN(1);
	// To set data rate of CAN 1(250Kbps) to receive can data
	/*
	DataInLength = 1;
	DataIn[0] = 0x0C; // 250Kbps
	if(LAUNCH_CAN_COMMAND("NXP_CAN_AP_10_SET_SPEED", DataIn, DataInLength, DataOut, &DataOutLength)) {
		gettimeofday(&start1, NULL);
		while(!EXIT_LOOP)
			usleep(1); // sleep 1 microsecond
	}
	else
		printf("To set data rate of CAN 1 failure.\n");
	*/
	// ###### To launch MCU or CAN command [END] ######

	// ###### To exit the program [START] ######
	LAUNCH_EXIT("CONFIG_MAIN_EXIT", NULL, 0);
	// ###### To exit the program [END] ######

	// To unregister sys log(optional)
	/*
	syslog(LOG_INFO, "MCU AP close ...");
	closelog();
	*/

	exit(EXIT_SUCCESS);
}
