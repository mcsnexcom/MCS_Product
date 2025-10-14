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

// Add by Singo 2021/03/25 Start...
char szProductName[64] = {0x00};
#ifndef ANDROID
char *pFolder = "configs/";
#else
char *pFolder = "/etc/nexcom/mut/configs/";
#endif

#define TEST_LINE_MAX 256

int test_MCU_system_set(FILE *fConfig) {
        int i = 0;
        char *res;
        char strLine[TEST_LINE_MAX];
        char info_flag = false;

        memset(strLine, 0, sizeof(strLine));
        while (!feof(fConfig)) {
                res = fgets(strLine, TEST_LINE_MAX, fConfig);
                if (strcmp(strLine, "</MENU_SYSTEM_SET>\n") == 0) {
                        info_flag = false;
                        return 1;
                }
                if (info_flag) {
                        char *pStr;
                        char *pStrData[5];
                        pStr = strtok(strLine, ",");
                        i=0;
                        while (pStr != NULL) {
                                pStrData[i] = pStr;
                                pStr = strtok(NULL, ",");
                                i++;

                        }
                        // MCU Command Name
                        char mcuCommandName[strlen(pStrData[3])];
                        snprintf(mcuCommandName, sizeof(mcuCommandName), "%s", pStrData[3]);
                        mcuCommandName[strlen(mcuCommandName)] = '\0';
                        char mcuCN[30];
                        memset(mcuCN, '\0', sizeof(mcuCN));
                        snprintf(mcuCN, sizeof(mcuCN), "%s", mcuCommandName);
                        int j = 0;
                        for(j=strlen(mcuCommandName); j<30; j++){
                                mcuCN[j] = 0x2E;        // 0x2E > "."
                        }
                        // MCU Test
printf("%s  %s\n", mcuCN, pStrData[0]);
/*                        if (atoi(pStrData[2])){
                                BYTE DataIn[128];
                                int DataInLength = 0;
                                BYTE DataOut[128];
                                int DataOutLength = 0;
                                // Get
                                DataIn[0] = 0x00; // No need.
                                DataInLength = 0;
                                if (LAUNCH_MCU_CMD(pStrData[0], DataIn, DataInLength, DataOut, &DataOutLength)) {
                                        printf("%s \t>>> ", mcuCommandName);
                                        for(i = 0; i < DataOutLength; i++)
                                                printf("0x%02X ", DataOut[i]);
                                        printf("\n");
                                } else {
                                        printf("%s \t>>> ERROR... \n", mcuCommandName);
                                }
                        }
*/                }
                if (strcmp(strLine, "<MENU_SYSTEM_SET>\n") == 0) {
                        info_flag = true;
                        printf("\n\n");
                }
        }
        return 0;
}

int test_MCU_system_get(FILE *fConfig) {
        int i = 0;
        char *res;
        char strLine[TEST_LINE_MAX];
        char info_flag = false;

        memset(strLine, 0, sizeof(strLine));
        while (!feof(fConfig)) {
                res = fgets(strLine, TEST_LINE_MAX, fConfig);
                if (strcmp(strLine, "</MENU_SYSTEM_GET>\n") == 0) {
                        info_flag = false;
                        return 1;
                }
                if (info_flag) {
                        char *pStr;
                        char *pStrData[5];
                        pStr = strtok(strLine, ",");
                        i=0;
                        while (pStr != NULL) {
                                pStrData[i] = pStr;
                                pStr = strtok(NULL, ",");
                                i++;

                        }
                        // MCU Command Name
                        char mcuCommandName[strlen(pStrData[3])];
                        snprintf(mcuCommandName, sizeof(mcuCommandName), "%s", pStrData[3]);
                        mcuCommandName[strlen(mcuCommandName)] = '\0';
                        char mcuCN[30];
                        memset(mcuCN, '\0', sizeof(mcuCN));
                        snprintf(mcuCN, sizeof(mcuCN), "%s", mcuCommandName);
                        int j = 0;
                        for(j=strlen(mcuCommandName); j<30; j++){
                                mcuCN[j] = 0x2E;        // 0x2E > "."
                        }
                        // MCU Test
                        if (atoi(pStrData[2])){
                                BYTE DataIn[128];
                                int DataInLength = 0;
                                BYTE DataOut[128];
                                int DataOutLength = 0;
                                // Get
                                DataIn[0] = 0x00; // No need.
                                DataInLength = 0;
                                if (LAUNCH_MCU_CMD(pStrData[0], DataIn, DataInLength, DataOut, &DataOutLength)) {
                                        printf("%s  ", mcuCN);
                                        for(i = 0; i < DataOutLength; i++)
                                                printf("0x%02X ", DataOut[i]);
                                        printf("\n");
                                } else {
                                        printf("%s\t>>>\tERROR... \n", mcuCN);
                                }
                        }
                }
                if (strcmp(strLine, "<MENU_SYSTEM_GET>\n") == 0) {
                        info_flag = true;
                        printf("\n\n");
                }
        }
        return 0;
}

void get_configs_data() {
// Modified by William Ho on 6/23/2021 Start...
#ifndef ANDROID
    char arch[20] = { 0x00 };
    FILE *fp = popen("uname -m", "r");
    fgets(arch, sizeof(arch), fp);
    pclose(fp);
    // For x86 arch
    if (strcmp(arch, "x86_64\n") == 0 || strcmp(arch, "i686\n") == 0) {
        syslog(LOG_INFO, " CPU architecture is %s", arch);
        FILE *cmd = popen("dmidecode -s system-product-name", "r");
        while (fgets(szProductName, sizeof(szProductName), cmd) != NULL);
        pclose(cmd);
        // For ARM arch
    }
    else if (strcmp(arch, "aarch64\n") == 0 || strcmp(arch, "armv7l\n") == 0) {
        syslog(LOG_INFO, " CPU architecture is %s", arch);
        FILE *cmd = popen("cat /sys/firmware/devicetree/base/product", "r");
        while (fgets(szProductName, sizeof(szProductName), cmd) != NULL);
        szProductName[strlen(szProductName)] = '\n';
        pclose(cmd);
    }
    else {
        printf("Can't recognize CPU architecture.\n");
        exit(1);
    }
#else
    FILE *cmd = popen("getprop ro.product.model", "r");
    while (fgets(szProductName, sizeof(szProductName), cmd) != NULL);
    pclose(cmd);
#endif
// Modified by William Ho on 6/23/2021 End.....

    // Getting MCU/CAN information from configuration file
    char filePath[strlen(pFolder) + strlen(szProductName) + strlen("_M")];
    szProductName[strlen(szProductName) - 1] = '\0';
    snprintf(filePath, sizeof(filePath), "%s%s%s", pFolder, szProductName, "_M");
    syslog(LOG_INFO, "configuration file is %s.", filePath);
    FILE *fConfig = fopen(filePath, "r");
    if (fConfig == NULL) {
        printf("Can't find any configuration file, please check configuration file exist or not.\n");
        exit(1);
    }
    test_MCU_system_get(fConfig);
    test_MCU_system_set(fConfig);
    pclose(fConfig);
}
// Add by Singo 2021/03/25 End.....

/**
 * Handling the signal from key event(ctrl+c).
 *
 * @param sign_no The number of signal
 */
void handle_signal_from_keyevent(int sign_no) {
	printf("\nReceiving signal from key event. The signal no is %d.\n", sign_no);
        EXIT_LOOP = true;
        EXIT_AP = true;
}

/**
 * The Callback function will get alarm event data from MCU service.
 *
 * @param type the event type(0x01:Key/0x03:Alarm/0x04:GPI_Notice)
 * @param data the event data
 */
void Receive_Event(BYTE type, BYTE data) {
    printf("Receive_Event");
    switch(type) {
        case 1:
            /*
             0x81:  Sleep Key
             */
// Modify by Singo 2021/04/29 Start...
            printf("\nThe data received from key event is: 0x%02X\n", data);
            //printf(" Sleep Key.\n");
// Modify by Singo 2021/04/29 End.....
            break;
        case 3:
            /*
             bit 0:  over     voltage alarm
             bit 1: lower     voltage alarm
             bit 2:  over temperature alarm
             bit 3: lower temperature alarm
             */
            printf("The data received from alarm event is:\n");
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
             bit 0: GPI 1 changed
             bit 1: GPI 2 changed
             bit 2: GPI 3 changed
             bit 3: GPI 4 changed
             */
            printf("The data received from GPI notice event is:\n");
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
            break;
        default:
            printf("default");
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

    // Set server FIFO name added by William Ho on 3/16/2021
    if(argc == 2) {
        if(Set_Server_FIFO(argv[1]))
            exit(EXIT_FAILURE);
    }
    else
        Set_Server_FIFO(NULL);

    BYTE DataIn[128];
    int DataInLength = 0;
    BYTE DataOut[128];
    int DataOutLength = 0;

    DataIn[0] = 0x00; // No need.
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
