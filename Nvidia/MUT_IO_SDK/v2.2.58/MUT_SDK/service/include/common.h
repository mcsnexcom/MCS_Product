/**
 * Common Variable.
 *
 * Team: MCS,MR12
 * Date: 11/18 2020 
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/stat.h>
#include "mcu_base.h"
#include "function_MAP.h"

#define DEMO_AP_VERSION "2.1.6"

extern MCU_INFO mcuInfo;
extern int nMCUDevice;
extern int nCANDevice;

extern MCU_CONTENT *mcu_content;
extern MCU_CONTENT *can_content[4];
extern int currentCANDevice;
extern int CAN1_fd;
extern int CAN2_fd;

//extern int verifyEnable;
extern int updatePercentageLevel;
extern int debugLevel;

void STOP_READ(int signal); // for CAN
void callback_gotEventData(CALLBACK_DATA callback_data);

// Add by Singo 2021/03/18 Start...
#ifdef ANDROID
int check_result(int fd, int mode, int result, BYTE *dataOut, int dataOutLen, char *function);
void checkSelect(int *get_option, int option_MIN, int option_MAX);
#endif
// Add by Singo 2021/03/18 End.....

#ifdef __cplusplus
}
#endif
