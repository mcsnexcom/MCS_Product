/**
 * Demo program(CAN Client).
 *
 * @Team    MR12/MCS
 * @Author  William Ho
 * @Date    8/17 2020
 */
#include <syslog.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mut.h"

bool EXIT_LOOP = false;

struct timeval utime; // test the throughput(received)
long time_use = 0;           // test the throughput(time used)
unsigned int dataCanCnt = 0;
unsigned int receiveCANDataCountOnAP=0;
typedef unsigned  char  BYTE;
typedef unsigned  long DWORD;

/**
 * Handling the signal from key event(ctrl+c).
 *
 * @param sign_no The number of signal
 */
void handle_signal_from_keyevent(int sign_no) {
	printf("\nReceive signal from key event. The signal no is %d.\n", sign_no);
	if(UnReg_CAN() == 1)
		printf("UnRegistered CAN successfully.\n");
	else
		printf("UnRegistered CAN failure.\n");
	EXIT_LOOP = true;
}

/**
 * The function dealed CAN information.
 *
 * @param id        CAN ID
 * @param *DataOut  CAN data
 */
void Deal_CAN_Info_from_AP(int id, BYTE *DataOut) {
    int i = 0, len = 0, tmpData3 = 0, t_cnt = 0;
    unsigned long tmpData1 = 0;
    unsigned int tmpData2 = 0;

    if(id == -2)
    {
        printf("No mcu_service running. (CB)\n");
	exit(EXIT_FAILURE);
    }

    gettimeofday(&utime, NULL);
    receiveCANDataCountOnAP++;

    // big endian
    printf("%ld.%ld, %u,", utime.tv_sec, utime.tv_usec, receiveCANDataCountOnAP);

    // ID
    printf(" ID(0x%02X),", id);

    // RTR
    len = (t_cnt + 2), tmpData3 = 0;
    for (i = t_cnt; i < len ; i++, t_cnt++)
        tmpData3 |= (DataOut[i] << ((len - (i + 1)) * 8));
    printf(" RTR(%d),", tmpData3);

    // IDE
    len = (t_cnt + 2), tmpData3 = 0;
    for (i = t_cnt; i < len ; i++, t_cnt++)
        tmpData3 |= (DataOut[i] << ((len - (i + 1)) * 8));
    printf(" IDE(%d),", tmpData3);

    // CAN Data
    len = (t_cnt + 2), tmpData3 = 0;
    for (i = t_cnt; i < len ; i++, t_cnt++)
        tmpData3 |= (DataOut[i] << ((len - (i + 1)) * 8));
    printf(" Len(%d), Data 1~8", tmpData3);

    /* CAN Data */
    for(i = 0; i < 8; i++)
        printf(" ,0x%02X", DataOut[(i + 6)]);
        //printf(" (0x%02X)", DataOut[(i + 36)]);
    printf("\n");
}

/**
 * The Callback function will get CAN data from MCU service.
 * The array of BYTE(big endian) is receiveCANDataCount(8 bytes)+receiveErrorCount(4 bytes)+sendCommandSuccessCount(8 bytes)
 *                                  +sendCommandErrorCount(4 bytes)+sendCommandTimeCount(4 bytes)+fd(2 bytes)+ide(2 bytes)
 *                                  +rtr(2 bytes)+dlc(2 bytes) = 36 bytes
 *
 * @param id        CAN ID
 * @param *DataOut  CAN data
 */
void Receive_CAN(int id, BYTE *DataOut) {

	Deal_CAN_Info_from_AP(id, DataOut);
}

//------------------------------------------------------------------------------------------------------
/**
 * Set Filter
 */
int setFilter(unsigned int chanel, int enable, int dataMode, DWORD filter_id, DWORD filter_mask_id)
{
	int DataInLength = 0, DataOutLength = 0;
	BYTE DataIn[128], DataOut[128];

    	DataInLength = 10;

	/*
         * DATA 0 : Filter Number
         * DATA 1 : Filter ID_HIGH_Low byte
         * DATA 2 : Filter ID_HIGH_High byte
         * DATA 3 : Filter ID_LOW_Low byte
         * DATA 4 : Filter ID_LOW_High byte
         * DATA 5 : Filter MASK_ID_HIGH_Low byte
         * DATA 6 : Filter MASK_ID_HIGH_High byte
         * DATA 7 : Filter MASK_ID_LOW_Low byte
         * DATA 8 : Filter MASK_ID_LOW_High byte
         * DATA 9 : Filter Control
         */

	// Number 0~13
        DataIn[0] = chanel;

	int nIDE;		// 0:Standard Format (11bits), 1:Extended Format (29bits)
	int nRTR=0;		// 0:Remote mode, 1:Data mode
	int nFilterMode=0;	// 0: Identifier mask mode (Default), 1: Identifier list mode. 
	int nFilterScale=1;	// 0: Two 16-bit filters, 1: One 32-bit filter (Default).
       	int nActivation;	// 0: Filter DISABLE, 1: Filter ENABLE (Default).
	DWORD nID;
	DWORD nMaskID;

	nIDE=dataMode;
	nActivation=enable; 
	nID=filter_id;
	nMaskID=filter_mask_id;

	if(filter_id == 0)
		nMaskID = 0x00000000;

        // ID
        switch (nIDE) {
                case 0: // Standard Format (11bits)
                {
                        DWORD nTempID;
                        nTempID = nID << 21; // ID Mapping

                        if (nRTR)
                                nTempID |= 0x02;
                        if (nIDE)
                                nTempID |= 0x04;

                        WORD wIDHigh = nTempID >> 16;
                        WORD wIDLow = nTempID;
                        BYTE byIDHigh_l = (BYTE) wIDHigh;
                        BYTE byIDHigh_h = wIDHigh >> 8;
                        BYTE byIDLow_l = (BYTE) wIDLow;
                        BYTE byIDLow_h = wIDLow >> 8;
                        DataIn[1] = byIDHigh_l;
                        DataIn[2] = byIDHigh_h;
                        DataIn[3] = byIDLow_l;
                        DataIn[4] = byIDLow_h;
                }
                break;

                case 1: // Extended Format (29bits)
                {
                        DWORD nTempID;
                        nTempID = nID << 3; // ID Mapping

                        if (nRTR)
                                nTempID |= 0x02;
                        if (nIDE)
                                nTempID |= 0x04;

                        WORD wIDHigh = nTempID >> 16;
                        WORD wIDLow = nTempID;
                        BYTE byIDHigh_l = (BYTE) wIDHigh;
                        BYTE byIDHigh_h = wIDHigh >> 8;
                        BYTE byIDLow_l = (BYTE) wIDLow;
                        BYTE byIDLow_h = wIDLow >> 8;
                        DataIn[1] = byIDHigh_l;
                        DataIn[2] = byIDHigh_h;
                        DataIn[3] = byIDLow_l;
                        DataIn[4] = byIDLow_h;
                }
                break;
        }

	// Mask ID
        WORD wMaskIDHigh = nMaskID >> 16;
        WORD wMaskIDLow = nMaskID;
        BYTE byMaskIDHigh_l = (BYTE) wMaskIDHigh;
        BYTE byMaskIDHigh_h = wMaskIDHigh >> 8;
        BYTE byMaskIDLow_l = (BYTE) wMaskIDLow;
        BYTE byMaskIDLow_h = wMaskIDLow >> 8;
        DataIn[5] = byMaskIDHigh_l;
        DataIn[6] = byMaskIDHigh_h;
        DataIn[7] = byMaskIDLow_l;
        DataIn[8] = byMaskIDLow_h;

        // Filter Control
        BYTE byFilterControl;

        byFilterControl = 0x00;
        if (nFilterMode == 1)
                byFilterControl |= 0x01;
        if (nFilterScale == 1)
                byFilterControl |= 0x02;
        if (nActivation == 1)
                byFilterControl |= 0x80;

	DataIn[9] = byFilterControl;

	printf("LAUNCH_CAN_CMD ST_CAN1_SET_02_01_FILTER.\n");
	if (LAUNCH_CAN_CMD("ST_CAN1_SET_02_01_FILTER", DataIn, DataInLength, DataOut, &DataOutLength)) {
		printf("Set filter success.\n");
	}
	else
		printf("Set filter fail !!!\n");

	usleep(200000); // sleep 200 microsecond
}
//------------------------------------------------------------------------------------------------------

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

	/*
	 * Command return
	 * 0: fail
	 * -4 Time Out
	 */

#if 1	
	/* All ID can pass */
	setFilter(0, 1, 0, 0, 0);
	setFilter(1, 1, 1, 0, 0);
	//setFilter(2, 0, 1, 0, 0);
	//setFilter(3, 0, 1, 0, 0);
	//setFilter(4, 0, 1, 0, 0);
	//setFilter(5, 0, 1, 0, 0);
	//setFilter(6, 0, 1, 0, 0);
#else
	/* Filter ID be passed as below */
	setFilter(0, 1, 1, 0x18FEF100, 0xFFFFFF00); // 0x18FEF1xx (xx: 00 - FF)
	setFilter(1, 1, 1, 0x0CF00400, 0xFFFFFF00); // 0x0CF004xx (xx: 00 - FF)
	setFilter(2, 1, 1, 0x18FEC100, 0xFFFFFF00); // 0x18FEC1xx (xx: 00 - FF)
	setFilter(3, 1, 1, 0x18FEE900, 0xFFFFFF00); // 0x18FEE9xx (xx: 00 - FF)
	setFilter(4, 1, 1, 0x18FEFC00, 0xFFFFFF00); // 0x18FEFCxx (xx: 00 - FF)
	setFilter(5, 1, 1, 0x18FEF200, 0xFFFFFF00); // 0x18FEF2xx (xx: 00 - FF)
	setFilter(6, 1, 1, 0x18FD7D00, 0xFFFFFF00); // 0x18FD7Dxx (xx: 00 - FF)

	/* Only filter ID 0x18FEF100 pass */
	//setFilter(0, 1, 1, 0x18FEF101, 0xFFFFFFFF); // 0x18FEF1xx (xx: 00 - FF)

	usleep(200000); // sleep 200 microsecond
#endif	

	/*
	 * To set data rate of CAN 1(250Kbps) to receive can data
	 */
        DataInLength = 1;
        DataIn[0] = 0x0C; // 250Kbps
        if(LAUNCH_CAN_CMD("ST_CAN1_SET_01_01_SPEED", DataIn, DataInLength, DataOut, &DataOutLength))
		printf("Send ST_CAN1_SET_01_01_SPEED success.\n");
	else
		printf("Send ST_CAN1_SET_01_01_SPEED fail. \n");

	usleep(200000); // sleep 200 microsecond

	/*
	 * Register CAN callback function
	 */
	if(Reg_CAN_CF(Receive_CAN)) {
		printf("Registered successfully.\n");
		//can_loop=1;
		while (!EXIT_LOOP)
			usleep(1000); // sleep 200 microsecond
	}
	else
		printf("Registered failure.\n");

	// To unregister sys log(optional)
	/*
	syslog(LOG_INFO, "CAN client AP close ...");
	closelog();
	*/

	exit(EXIT_SUCCESS);
}
