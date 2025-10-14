/**
 * Demo program(CAN Client).
 * 
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	8/17 2020
 */
#include <syslog.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mut.h"

bool EXIT_LOOP = false;

struct timeval start1, end1; // test the throughput(received)
long time_use = 0;			 // test the throughput(time used)
unsigned int dataCanCnt = 0;

/**
 * Handling the signal from key event(ctrl+c).
 *
 * @param sign_no The number of signal
 */
void handle_signal_from_keyevent(int sign_no) {
	printf("\nThe total received data is %d.\n", dataCanCnt);
	printf("\nReceiving signal from key event. The signal no is %d.\n", sign_no);
	if(UnReg_CAN() == 1)
		printf("UnRegistered CAN successfully.\n");
	else
		printf("UnRegistered CAN failure.\n");
	EXIT_LOOP = true;
}

/**
 * The function dealed CAN information.
 *
 * @param id		CAN ID
 * @param *DataOut	CAN data
 */
void Deal_CAN_Info_from_AP(int id, BYTE *DataOut) {
	int i = 0, len = 0, tmpData3 = 0, t_cnt = 0;
	unsigned long tmpData1 = 0;
	unsigned int tmpData2 = 0;

	// big endian
	printf("[REVEIVE]");

	len = (t_cnt + 8);
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData1 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" (LIB)receiveCount: %lu,", tmpData1);

	len = (t_cnt + 4);
	for (i = t_cnt; i < len; i++, t_cnt++)
		tmpData2 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" (LIB)receiveErrorCount: %u,", tmpData2);

	printf(" (AP)receiveCount: %u,", dataCanCnt);

	len = (t_cnt + 8), tmpData1 = 0;
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData1 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" (LIB)sendCommandSuccessCount: %lu,", tmpData1);

	len = (t_cnt + 4), tmpData2 = 0;
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData2 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" (LIB)sendCommandErrorCount: %u,", tmpData2);

	len = (t_cnt + 4), tmpData2 = 0;
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData2 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" (LIB)sendCommandTimeCount: %u\n", tmpData2);

	len = (t_cnt + 2), tmpData3 = 0;
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData3 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf("nfd(%d) =>", tmpData3);

	printf(" ID(0x%02X),", id);

	len = (t_cnt + 2), tmpData3 = 0;
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData3 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" RTR(%d),", tmpData3);

	len = (t_cnt + 2), tmpData3 = 0;
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData3 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" IDE(%d),", tmpData3);

	len = (t_cnt + 2), tmpData3 = 0;
	for (i = t_cnt; i < len ; i++, t_cnt++)
		tmpData3 |= (DataOut[i] << ((len - (i + 1)) * 8));
	printf(" Len(%d), Data 1~8", tmpData3);
}

/**
 * The Callback function will get CAN data from MCU service.
 * The array of BYTE(big endian) is receiveCANDataCount(8 bytes)+receiveErrorCount(4 bytes)+sendCommandSuccessCount(8 bytes)
 *                                  +sendCommandErrorCount(4 bytes)+sendCommandTimeCount(4 bytes)+fd(2 bytes)+ide(2 bytes)
 *                                  +rtr(2 bytes)+dlc(2 bytes) = 36 bytes
 *
 * @param id		CAN ID
 * @param *DataOut	CAN data
 */
void Receive_CAN(int id, BYTE *DataOut) {
	gettimeofday(&end1, NULL);
	time_use = ((end1.tv_sec - start1.tv_sec) * 1000) + ((end1.tv_usec - start1.tv_usec) / 1000);
	if (time_use == 60000) { // 60 seconds
		if(UnReg_CAN() == 1)
			printf("UnRegistered CAN successfully.\n");
		else
			printf("UnRegistered CAN failure.\n");
		printf("The total received data is %d, time used: %ld ms.\n", ++dataCanCnt, time_use);
		EXIT_LOOP = true;
	}
	///*
	Deal_CAN_Info_from_AP(id, DataOut);
	int i;
	for(i = 0; i < 8; i++)
		printf(" (0x%02X)", DataOut[(i + 36)]);
	printf("\n");
	//*/
}

/**
 * Bootstrap function.
 */
int main(int argc, char *argv[]) {
	int DataInLength = 0, DataOutLength = 0;
	BYTE DataIn[128], DataOut[128];
	// To register sys log(optional)
	/*
	openlog("CAN Client AP", LOG_CONS | LOG_PID, 0);
	syslog(LOG_INFO, "CAN AP start ...");
	*/
	signal(SIGINT, handle_signal_from_keyevent);

	// Set server FIFO name added by William Ho on 3/16/2021
	if(argc == 2) {
		if(Set_Server_FIFO(argv[1]))
			exit(EXIT_FAILURE);
	}
	else
		Set_Server_FIFO(NULL);

	if (LAUNCH_CAN_CMD("NXP_CAN_AP_DEVICE_CNT", DataIn, DataInLength, DataOut, &DataOutLength)) {
		printf("The CAN amount is %d.\n", DataOut[0]);
		if(DataOut[0] > 0) {
			DataInLength = 1;
			DataIn[0] = 0; // select CAN 1
			if (LAUNCH_CAN_CMD("NXP_CAN_AP_SELECT_DEVICE", DataIn, DataInLength, DataOut, &DataOutLength)) {
				printf("Setting CAN device successfully.\n");
				if(LAUNCH_CAN_CMD("NXP_CAN_AP_02_READ_FW_VERSION", DataIn, DataInLength, DataOut, &DataOutLength)) {
					if(DataOutLength > 0)
						printf("The F/W version is %d.\n", DataOut[1]);
				}
				if(Reg_CAN_CF(Receive_CAN)) {
					printf("Registered successfully.\n");
					// To set data rate of CAN 1(250Kbps) to receive can data
					DataInLength = 1;
					DataIn[0] = 0x0C; // 250Kbps
					if (LAUNCH_CAN_CMD("NXP_CAN_AP_10_SET_SPEED", DataIn, DataInLength, DataOut, &DataOutLength)) {
						gettimeofday(&start1, NULL);
						while (!EXIT_LOOP)
							usleep(10); // sleep 10 microsecond
					}
					else
						printf("To set data rate of CAN 1 failure.\n");
				}
				else
					printf("Registered failure.\n");
			}
			else
				printf("Setting CAN device failure.\n");
		}
	}
	else
		printf("Getting CAN devices failure.\n");

	// To unregister sys log(optional)
	/*
	syslog(LOG_INFO, "MCU client AP close ...");
	closelog();
	*/

	exit(EXIT_SUCCESS);
}
