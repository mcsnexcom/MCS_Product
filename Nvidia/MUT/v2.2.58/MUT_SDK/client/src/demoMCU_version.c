/**
 * Demo program(MCU Client).
 *
 * @Team    MR12/MCS
 * @Author  William Ho, Sam Wu
 * @Date    7/4 2022
 * @Description This program retrieves the MCU version from the MCU service on NexYocto.
 */
#include <syslog.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mut.h"

struct timeval utime; // test the throughput(received)
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
	///START FOR VTK62B
		case 1:
			/*
			 * Bit 0: Low Backup Battery
			 * Bit 1: Over Temperature
			 * Bit 2: Under Temperature
			 * Bit 3: Vin Lost
			 * Bit 4~7 is Reserved
			 **/
			printf("The data received from alarm event is:\n");
			if ((data[0] & 0x01) == 1)
				printf(" Low Backup Battery.\n");
			if (((data[0] >> 1) & 0x01) == 1)
				printf(" Over Temperature.\n");
			if (((data[0] >> 2) & 0x01) == 1)
				printf(" Under Temperature.\n");
			if (((data[0] >> 3) & 0x01) == 1)
				printf(" Vin Lost.\n");
			break;
		case 2:
			/*
			* 0x00: OFF
			* 0x01: ON
			**/
			printf("The data received from IGN status event is:\n");
			if (data[0] == 0x00)
				printf(" OFF.\n");
			if (data[0] == 0x01)
				printf(" On.\n");
			break;
		/// END FOR VTK62B

		/*case 1:
			printf("\nThe data received from key event is: 0x%02X\n", data);
			break;
		case 3:
			/*
			 * bit 0:  over     voltage alarm
			 * bit 1: lower     voltage alarm
			 * bit 2:  over temperature alarm
			 * bit 3: lower temperature alarm
			 **/
		/*	printf("The data received from alarm event is:\n");
			if ((data & 0x01) == 1)
				printf(" Over voltage alarm occurred.\n");
			if (((data >> 1) & 0x01) == 1)
				printf(" Lower voltage alarm occurred.\n");
			if (((data >> 2) & 0x01) == 1)
				printf(" Over temperature alarm occurred.\n");
			if (((data >> 3) & 0x01) == 1)
				printf(" Lower temperature alarm occurred.\n");
			break;
		case 4:
			/*
			 * bit 0: GPI 1 changed
			 * bit 1: GPI 2 changed
			 * bit 2: GPI 3 changed
			 * bit 3: GPI 4 changed
			 **/
		/*	printf("The data received from GPI notice event is:\n");
			if ((data & 0x01) == 1)
				printf(" GPI 1 is high.\n");
			else
				printf(" GPI 1 is low.\n");
			if (((data >> 1) & 0x01) == 1)
				printf(" GPI 2 high.\n");
			else
				printf(" GPI 2 is low.\n");
			if (((data >> 2) & 0x01) == 1)
				printf(" GPI 3 high.\n");
			else
				printf(" GPI 3 is low.\n");
			if (((data >> 3) & 0x01) == 1)
				printf(" GPI 4 high.\n");
			else
				printf(" GPI 4 is low.\n");
			break;*/
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

	int res;


	gettimeofday(&utime, NULL);
	/* Get MCU Version */
	res = LAUNCH_MCU_CMD("ST_SYSTEM_GET_01_01_MCU_VERSION", DataIn, DataInLength, DataOut, &DataOutLength);

	/* Get MCU Version */
	if(res > 0)
	{
		// printf("MCU version read successfully.\n");
		// char sys_command[1024];
		// memset(sys_command, 0, 1024 * sizeof(char));	
		// snprintf(sys_command, sizeof(sys_command), " echo \"MCU Version: %c%02d\n\" >> /nexcom/init/info", (char)DataOut[7], DataOut[8]);
		printf("MCU Version: %c%02d\n", (char)DataOut[7], DataOut[8]);
		// system(sys_command);
	}
	else
	{
		// printf("Get MCU version failure.\n");
	}

	return 0;
}
