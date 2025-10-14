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
int is_valid_hex(const char *str){
	if(str == NULL || str[0] == '\0' || str[1] == '\0' || str[2] != '\0' ){
		return 0; // Length must be exactly 2
	} 
	return isxdigit(str[0]) && isxdigit(str[1]);
}

void printfCommand(){
	printf("[Error] Input  Error!!!\n");
	printf("[Example] To query ST_SYSTEM_GET_01_01_MCU_VERSION : ./mcu_system_cmd 02(GET) 01 01 (Enter hexadeciaml data.)\n");
	printf("[Example] To query ST_SYSTEM_SET_13_01_ALARM_TIMER : ./mcu_system_cmd 03(SET) 13 01 11 11 11 (Data In) (Enter hexadeciaml data.)\n");	
}
/**
 * Main function.
 */
int main(int argc, char *argv[]) {

	// To register the key event
	signal(SIGINT, handle_signal_from_keyevent);

	// LAUNCH_INIT_DEV(NULL, 0, "/dev/ttyS4", 115200, -1);
	// printf("The result of initiating MCU is %d.\n", LAUNCH_INIT_DEV(NULL, 0, "/dev/ttyS4", 115200, -1));

	// Register_MCU_EventCallBack(1, 1, callback_gotEventData);
	// Initiating the command pool
	// INIT_CMD_POOL();

	FILE *fConfig = LAUNCH_INIT_CONFIG(1, NULL);
	
	if (fConfig == NULL) {
		syslog(LOG_ERR, "Can't find any menu configuration file, please check menu configuration file exist or not");
		syslog(LOG_INFO, "MCU AP close ...");
		return -1;
	}
	printf("\n");
	int result = 0, DataInLength = 0, DataOutLength = 0;
	BYTE DataIn[128], DataOut[128];
	char simple_funName[128],  funName[128];
	memset(&simple_funName[0], 0 , 128 * sizeof(char));
	memset(&funName[0], 0 , 128 * sizeof(char));
	if ( argc < 4 ){
		printfCommand();
		exit(EXIT_SUCCESS);
	}
	else {
		bool is_vaild_hex = true;

		for(int i = 1; i < argc ; i++){			
			if ( !is_valid_hex( argv[i] ) ){
				is_vaild_hex = false;
				break;
			}
			if (i >= 4 ){
				DataIn[i - 4]=(BYTE)strtol(argv[i], NULL, 16);
			}
			// printf("i : %i, %02x \n", i, argv[i]);
		}

		if(!is_vaild_hex){
			printfCommand();
			exit(EXIT_SUCCESS);
		}

		if (strcmp(argv[1], "02") == 0){
			strcpy(simple_funName, "SYSTEM_GET");
		}
		else if(strcmp(argv[1], "03") == 0){
			strcpy(simple_funName, "SYSTEM_SET");
		}
		else{
			printfCommand();	
			exit(EXIT_SUCCESS);	
		}
		if ( (strcmp(argv[1], "02") == 0 && argc > 4) ||  (strcmp(argv[1], "03") == 0 && argc <= 4)  ){
			printfCommand();	
			exit(EXIT_SUCCESS);	
		}
		DataInLength = argc - 4 ;
		sprintf( simple_funName + strlen(simple_funName), "_%s_%s", argv[2], argv[3] );
		if(!FIND_FunName( simple_funName, &funName)){
			printfCommand();	
			exit(EXIT_SUCCESS);				
		}
		// printf("funName: %s , DataInLength : %i\n ", funName, DataInLength);
	}
	
	// // Initiating the command pool
	// INIT_CMD_POOL();
	// for (int i = 0; i < DataInLength; i++)
	// {
	// 	printf("%02x ", DataIn[i]);
	// }

	int res;
	res = LAUNCH_MCU_COMMAND(funName, DataIn, DataInLength, DataOut, &DataOutLength);

	if(res > 0)
	{
		printf("\n[Output] Data out: ");
		for (int i = 0; i < DataOutLength; i++)
		{
			printf("%02x ", DataOut[i]);
		}
		printf("\n\n");
	}
	else
	{
		printf("Get MCU version failure.\n");
//		count_f++;
	}


	// LAUNCH_EXIT("CONFIG_MAIN_EXIT", NULL, 0);
	LAUNCH_EXIT("CONFIG_MAIN_EXIT", fConfig, 1);

	exit(EXIT_SUCCESS);
}
