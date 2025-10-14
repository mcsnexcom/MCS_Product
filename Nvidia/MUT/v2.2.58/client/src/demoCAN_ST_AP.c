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

struct timeval start1, end1; // test the throughput(received)
long time_use = 0;           // test the throughput(time used)
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
 * @param id        CAN ID
 * @param *DataOut  CAN data
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
 * @param id        CAN ID
 * @param *DataOut  CAN data
 */
void Receive_CAN(int id, BYTE *DataOut) {
    gettimeofday(&end1, NULL);
    time_use = 0;
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

	/*
	 * Command return
	 * 0: fail
	 * -4 Time Out
	 */

//------------------------------------------------------------------------------------------------------
#if 0
	/* 
	 * Set filter - Only ID feea00 can pass.
	 */

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
        DataIn[0] = 0;

	typedef unsigned  char  BYTE;
	typedef unsigned  long DWORD;
	int nIDE=1;        // 0:Standard Format (11bits), 1:Extended Format (29bits)
	int nRTR=0;        // 0:Remote mode, 1:Data mode
	int nFilterMode=0; // 0: Identifier mask mode (Default), 1: Identifier list mode. 
	int nFilterScale=1;// 0: Two 16-bit filters, 1: One 32-bit filter (Default).
       	int nActivation=1; // 0: Filter DISABLE, 1: Filter ENABLE (Default).
	DWORD nID=0x00feea00;
	DWORD nMaskID=0xffffffff;

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

	if (LAUNCH_CAN_CMD("ST_CAN1_SET_02_01_FILTER", DataIn, DataInLength, DataOut, &DataOutLength)) {
		printf("Set filter success.\n");
	}
	else
		printf("Set filter fail !!!\n");
#endif
//------------------------------------------------------------------------------------------------------


	/*
	 * To set data rate of CAN 1(250Kbps) to receive can data
	 */
        DataInLength = 1;
        DataIn[0] = 0x0C; // 250Kbps
        if(LAUNCH_CAN_CMD("ST_CAN1_SET_01_01_SPEED", DataIn, DataInLength, DataOut, &DataOutLength))
		printf("Send ST_CAN1_SET_01_01_SPEED success.\n");
	else
		printf("Send ST_CAN1_SET_01_01_SPEED fail. \n");

	/*
	 * Register CAN callback function
	 */
	if(Reg_CAN_CF(Receive_CAN)) {
		printf("Registered successfully.\n");
		while (!EXIT_LOOP)
			usleep(10); // sleep 10 microsecond
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
