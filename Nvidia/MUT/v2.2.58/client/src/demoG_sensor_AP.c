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
	int res;

	/* Enable G-Sensor */
    	DataIn[0] = 0x2D; // Start of register Index - > POWER_CTL
    	DataIn[1] = 0x01; // Data Length
    	DataIn[2] = 0x0A; // Data
    	DataInLength = 3;

	res = LAUNCH_MCU_CMD("ST_SYSTEM_SET_23_01_G_SENSOR_DATA", DataIn, DataInLength, DataOut, &DataOutLength);
	if(res > 0)
		printf("Enable G-Sensor Success.\n");
	else
	{
		printf("Enable G-Sensor Fail !!!\n");
		exit(EXIT_SUCCESS);
	}
	
	while(EXIT_AP != true)
	{
    		DataIn[0] = 0x32; // Start of register Index - > X0 X1 Y0 Y1 Z0 Z1
    		DataIn[1] = 0x06; // Data Length
    		DataInLength = 2;

		/* Get G-Sensor Data */
		res = LAUNCH_MCU_CMD("ST_SYSTEM_GET_23_01_GSENSOR_DATA", DataIn, DataInLength, DataOut, &DataOutLength);
		if(res > 0)
		{
			//printf("DataOutLength = %d\n", DataOutLength);
			printf("x0:%02X  x1:%02X  y0:%02X  y1:%02X  z0:%02X  z1:%02X", 
				DataOut[1], DataOut[2], DataOut[3], DataOut[4], DataOut[5], DataOut[6]);
			printf("\n");
		}
		else
			printf("Get MDI Status failure.\n");

		if(EXIT_AP == true)
			break;
	}

	exit(EXIT_SUCCESS);
}
