/**
 * Header file of MUT types
 * 
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	4/9 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MUT_TYPES_H_
#define MUT_TYPES_H_
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Identification of debug.(deprecated, used syslog)
 */
//#define DEBUG 1

/**
 * The string of MUT service FIFO.
 */
// Modify by Singo 2021/03/18 Start...
#ifndef ANDROID
#define SERVER_FIFO_NM "/tmp/mut_serv_fifo"
#else
#define SERVER_FIFO_NM "/data/fifo/mut_serv_fifo"
#endif

/**
 * The string of standard FIFO.
 */
#ifndef ANDROID
#define STD_FIFO_NM "/tmp/std_fifo_%07d"
#else
#define STD_FIFO_NM "/data/fifo/std_fifo_%07d"
#endif

/**
 * The string of event FIFO.
 */
#ifndef ANDROID
#define EVT_FIFO_NM "/tmp/evt_fifo_%07d"
#else
#define EVT_FIFO_NM "/data/fifo/evt_fifo_%07d"
#endif

/**
 * The string of CAN FIFO.
 */
#ifndef ANDROID
#define CAN_FIFO_NM "/tmp/can_fifo_%07d"
#else
#define CAN_FIFO_NM "/data/fifo/can_fifo_%07d"
#endif

/**
 * The length of FIFO name. /tmp/{std|evt}_fifo_{pid:length(7)}
 */
#ifndef ANDROID
#define NM_SZ 50
#else
#define NM_SZ 50
#endif
// Modify by Singo 2021/03/18 End.....

/**
 * The name of server FIFO.
 */

static char serv_fifo_nm[NM_SZ];


/**
 * The size of data array.
 */
#define DATA_SZ 128

typedef unsigned char		 BYTE;
typedef unsigned short		 WORD;
typedef unsigned long		DWORD;

typedef struct {
	int  pid;           // the process ID
	int  dType;			// 0: normal/1: event(register)/ -1: event(unregister)
	int  res; 			// 0: Failure/1: Success/-1: The watchdog was disabled
	int  dInLen; 		// The length of input data
	int  dOutLen;		// The length of output data
	BYTE dIn[DATA_SZ];	// The array of input data
	BYTE dOut[DATA_SZ];	// The array of output data
	char fifoNm[NM_SZ];	// The FIFO name of client(std/evt)
	char funNm[NM_SZ];	// The function name of MCU
	char cmdNm[DATA_SZ];// The command name of MCU
} MCU_CMD_DATA;

#endif //MUT_TYPES_H_

#ifdef __cplusplus
}
#endif
