/**
 * Demo program(MCU Client).
 *
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	4/9 2020
 */
#include <syslog.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mut.h"

struct timeval utime; // test the throughput(received)
bool EXIT_AP = false;
bool EXIT_LOOP = false;

// Add by Singo 2021/03/25 Start...
char szProductName[64] = {0x00};
#ifndef ANDROID
char *pFolder = "configs/";
#else
char *pFolder = "/etc/nexcom/mut/configs/";
#endif

#define TEST_LINE_MAX 256

/**
 * Handling the signal from key event(ctrl+c).
 *
 * @param sign_no The number of signal
 */
void handle_signal_from_keyevent(int sign_no)
{
	printf("\nReceiving signal from key event. The signal no is %d.\n", sign_no);
	EXIT_LOOP = true;
	EXIT_AP = true;
}

struct timeval start_t, end_t;

/**
 * The Callback function will get alarm event data from MCU service.
 *
 * @param type the event type(0x01:Key/0x03:Alarm/0x04:GPI_Notice/0x05:ODOmeter/0x06:Heartbeat/0x63:Service_activated)
 * @param datelen the event datalen
 * @param data the event data
 */
void Receive_Event(int type, BYTE datalen, BYTE *data)
{
	printf("\n*************\n");
	printf("Receive_Event\n");
	printf("*************\n");

	if(type == -1)
	{
		printf("Wrong event type\n");
		//exit(EXIT_FAILURE);
	}

	switch (type)
	{
	case 1:
		/*
		 0x81:	Sleep Key
		 */
		// Modify by Singo 2021/04/29 Start...
		printf("The data received from key event is: 0x%02X\n", data[0]);
		// printf(" Sleep Key.\n");
		// Modify by Singo 2021/04/29 End.....
		break;
	case 3:
		/*
		 bit 0:  over     voltage alarm
		 bit 1: lower     voltage alarm
		 */
		printf("The data received from alarm event is:\n");
		if (data[0] & 0x01)
			printf(" Over voltage alarm occurred.\n");
		if (data[0] & 0x02)
			printf(" Lower voltage alarm occurred.\n");
		break;
	case 4:
		/*
		 bit 0: GPI 1 changed
		 bit 1: GPI 2 changed
		 bit 2: GPI 3 changed
		 bit 3: GPI 4 changed
		 bit 4: GPI 5 changed
		 bit 5: GPI 6 changed
		 */
		printf("The data received from GPI notice event is:\n");
		if (data[0] & 0x01)
			printf(" GPI 1 is high.\n");
		else
			printf(" GPI 1 is low.\n");
		if (data[0] & 0x02)
			printf(" GPI 2 is high.\n");
		else
			printf(" GPI 2 is low.\n");
		if (data[0] & 0x04)
			printf(" GPI 3 is high.\n");
		else
			printf(" GPI 3 is low.\n");
		if (data[0] & 0x08)
			printf(" GPI 4 is high.\n");
		else
			printf(" GPI 4 is low.\n");
		if (data[0] & 0x10)
			printf(" GPI 5 is high.\n");
		else
			printf(" GPI 5 is low.\n");
		if (data[0] & 0x20)
			printf(" GPI 6 is high.\n");
		else
			printf(" GPI 6 is low.\n");
		break;
    case 5:
	gettimeofday(&end_t,NULL);
	printf("\n---\n");
	printf("time: %ld\n", (end_t.tv_usec - start_t.tv_usec)/1000 );
	printf("---\n");
		/*
		bit 0~1 : Frequency
        bit 2~5 : Pulse Count
		 */
		printf("The data received from Frequency Pluse event is:\n");
		unsigned char inputFrequencyLow = 0, inputFrequencyHigh = 0;
		unsigned int inputFrequency = 0;
		inputFrequency =(int)(data[1] << 8) + data[0];
		printf("Frequency = %d (0~2000)\n", inputFrequency);

        unsigned long long nPulseCount = 0;
		nPulseCount = data[2] + (data[3] << 8) + (data[4] << 16) + (data[5] << 24);
		printf("pulse count = %lld. (Odometer)\n", nPulseCount);
	gettimeofday(&start_t,NULL);
		break;
	default:
		printf("default\n");
		break;
	case 99:
		printf("\n---\n");
		printf("Service activated!");
		printf("\n---\n");
		break;
	}
}

void heartbeat_fail_handler(void) {
	printf("\n---\n");
	printf("Heartbeat check fail!");
	printf("\n---\n");
}

/**
 * Bootstrap function.
 */
int main(int argc, char *argv[])
{
	gettimeofday(&start_t,NULL);
	// To register sys log(optional)
	/*
	openlog("MCU Client AP", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "MCU Client AP start ...");
	*/
	system("clear");
	signal(SIGINT, handle_signal_from_keyevent);

	// Set server FIFO name added by William Ho on 3/16/2021
	if(argc == 2) {
	if(Set_Server_FIFO(argv[1]) == 0){
			printf("Can't find mcu_service !!!\n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		if(Set_Server_FIFO(NULL) == 0){
			printf("Can't find mcu_service !!!\n");
			exit(EXIT_FAILURE);
		}
	}


	if (Reg_Heartbeat_Monitor(5, heartbeat_fail_handler) == 0)
		printf("Heartbeat monitor registered.\n");
	else
		printf("Failed to register heartbeat monitor.\n");

	/* Register event callback function */
	if (Reg_Event_CF_type(Receive_Event, 4) == 0) 
		printf("Registered event 4 successfully.\n");
	else
		printf("Registered event 4 failure.\n");

	if (Reg_Event_CF_type(Receive_Event, 99) == 0) 
		printf("Registered event 99 successfully.\n");
	else
		printf("Registered event 99 failure.\n");

	BYTE DataIn[128];
	int DataInLength = 0;
	BYTE DataOut[128];
	int DataOutLength = 0;

	DataIn[0] = 0x00;
	DataInLength = 0;

	int res;
	int i=0, count_s=0, count_f=0;
	while(EXIT_AP != true)
    {
		gettimeofday(&utime, NULL);
		/* Get MCU Version */
		//res = LAUNCH_MCU_CMD("ST_SYSTEM_GET_01_01_MCU_VERSION", DataIn, DataInLength, DataOut, &DataOutLength);
		//printf("(%ld.%ld)", utime.tv_sec, utime.tv_usec);
		/* Get MCU Version */
		/*if(res > 0)
		{
			printf("MCU version = %d\n", DataOut[0]);
			count_s++;
		}
		else
		{
			printf("Get MCU version failure.\n");
			count_f++;
		}*/

		if(EXIT_AP == true)
			break;
	}
	exit(EXIT_SUCCESS);
}

