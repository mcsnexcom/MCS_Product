/**
 * Demo program(MCU Client).
 *
 * @Team    MR12/MCS
 * @Author  William Ho
 * @Date    4/9 2020
 */
#include <syslog.h>
#include <signal.h>
#include <stdlib.h>
#include "mut.h"

bool EXIT_AP = false;
bool EXIT_LOOP = false;

/**
 * Handling the signal from key event(ctrl+c).
 *
 * @param sign_no The number of signal
 */
void handle_signal_from_keyevent(int sign_no) {
	printf("\nReceive signal from key event. The signal no is %d.\n", sign_no);
        EXIT_LOOP = true;
        EXIT_AP = true;
}

/**
 * The Callback function will get alarm event data from MCU service.
 *
 * @param type the event type(0x01:Key/0x03:Alarm/0x04:GPI_Notice)
 * @param datelen the event datalen
 * @param data the event data
 */
void Receive_Event(int type, BYTE datalen, BYTE *data) {
	//printf("Receive_Event");

	/* No mcu_service */
	if(type == -1)
	{
		printf("No mcu_service running. (CB)\n");
		exit(EXIT_FAILURE);
	}

	switch(type) {
		case 1:
			printf("\nThe data received from key event is: 0x%02X\n", data[0]);
			break;
        	case 3:
			/*
			 * bit 0:  over     voltage alarm
			 * bit 1: lower     voltage alarm
			 * bit 2:  over temperature alarm
			 * bit 3: lower temperature alarm
			 **/
			printf("The data received from alarm event is:\n");
			if ((data[0] & 0x01) == 1)
				printf(" Over voltage alarm occurred.\n");
			if (((data[0] >> 1) & 0x01) == 1)
				printf(" Lower voltage alarm occurred.\n");
			if (((data[0] >> 2) & 0x01) == 1)
				printf(" Over temperature alarm occurred.\n");
			if (((data[0] >> 3) & 0x01) == 1)
				printf(" Lower temperature alarm occurred.\n");
			break;
		case 4:
			/*
			 * bit 0: GPI 1 changed
			 * bit 1: GPI 2 changed
			 * bit 2: GPI 3 changed
			 * bit 3: GPI 4 changed
			 **/
			printf("The data received from GPI notice event is:\n");
			if ((data[0] & 0x01) == 1)
				printf(" GPI 1 is high.\n");
			else
				printf(" GPI 1 is low.\n");
			if (((data[0] >> 1) & 0x01) == 1)
				printf(" GPI 2 high.\n");
			else
				printf(" GPI 2 is low.\n");
			if (((data[0] >> 2) & 0x01) == 1)
				printf(" GPI 3 high.\n");
			else
				printf(" GPI 3 is low.\n");
			if (((data[0] >> 3) & 0x01) == 1)
				printf(" GPI 4 high.\n");
			else
				printf(" GPI 4 is low.\n");
			break;
		default:
			printf("default\n");
			break;
	}
}

/**
 * Bootstrap function.
 */
int main(int argc, char *argv[]) {
	// To register sys log(optional)
	/*
	openlog("MCU Client AP", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "MCU Client AP start ...");
	*/
	signal(SIGINT, handle_signal_from_keyevent);
	signal(SIGTERM, handle_signal_from_keyevent);

	// Set server FIFO name added by William Ho on 3/16/2021
	if(argc == 2) {
		if(Set_Server_FIFO(argv[1]) == 0){
			printf("Can't find mcu_service !!!\n");
			exit(EXIT_FAILURE);
		}
	}else{
		if(Set_Server_FIFO(NULL) == 0){
			printf("Can't find mcu_service !!!\n");
			exit(EXIT_FAILURE);
		}
	}

	/* Register event callback function */
	if(Reg_Event_CF(Receive_Event))
		printf("Registered successfully.\n");
	else
		printf("Registered failure.\n");

	BYTE DataIn[128];
	int DataInLength = 0;
	BYTE DataOut[128];
	int DataOutLength = 0;

	DataIn[0] = 0x00;
	DataInLength = 0;

#if 0
	if (LAUNCH_MCU_CMD("ST_SYSTEM_GET_01_01_MCU_VERSION", DataIn, DataInLength, DataOut, &DataOutLength))
		printf("MCU version = %d\n", DataOut[0]);
	else
		printf("Get MCU version failure.\n");
#else

	int res;
	while(EXIT_AP != true)
	{
		/* Get MCU Version */
		res = (LAUNCH_MCU_CMD("ST_SYSTEM_GET_01_01_MCU_VERSION", DataIn, DataInLength, DataOut, &DataOutLength));
		if(res > 0)
			printf("MCU version = %d\n", DataOut[0]);
		else
			printf("Get MCU version failure.\n");

		/* Get MDI Status */
		res = LAUNCH_MCU_CMD("ST_SYSTEM_GET_22_01_MDI_STATUS", DataIn, DataInLength, DataOut, &DataOutLength);
		if(res > 0)
			printf("MDI Status = %#x\n", DataOut[0]);
		else
			printf("Get MDI Status failure.\n");

		if(EXIT_AP == true)
			break;


#endif

	}

	printf("EXIT_SUCCESS\n");
	exit(EXIT_SUCCESS);
}
