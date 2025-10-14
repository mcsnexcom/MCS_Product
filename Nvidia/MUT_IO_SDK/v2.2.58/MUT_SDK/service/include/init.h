/**
 * The header file of initiation.
 *
 * @Team	MR12/MCS
 * @Author 	Sam, Singo, William Ho, Ricky
 * @Date	8/6 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#define LINE_MAX 128

// To declare external variables from init.c's variables, Added by William Ho start
extern char *pFolder;
extern char szProductName[64];
// To declare external variables from init.c's variables, Added by William Ho end

#if defined(MCU) | defined(ALL)
/**
 * To retrive the information of MCU from configuration file.
 *
 * @param *fConfig		the pointer of file
 * @param *pnDevice 	the pointer recorded the amount of MCU device
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int Get_MCU_DeviceInfo(FILE *fConfig, int *pnDevice);

/**
 * To launch command with input data to MCU and to retrive the result data.
 *
 * @param *cmdName		the pointer of function(key) name
 * @param *dataIn		the array of input data
 * @param dataInLen		the length of input data
 * @param *dataOut		the array of received data
 * @param *dataOutLen	the length of received data
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int LAUNCH_MCU_COMMAND(char *cmdName, BYTE *dataIn, int dataInLen, BYTE *dataOut, int *dataOutLen);

/**
 * To retrive the information of updating MCU from configuration file.
 *
 * @param *fConfig		the pointer of file
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int Get_MCU_UpdateInfo(FILE *fConfig);

/**
 * To launch command to flash MCU.
 *
 * @param *cmdName		the pointer of function(key) name
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int LAUNCH_MCU_UPDATE(char *cmdName);

/**
 * To launch command to get MCU NVRAM.
 *
 * @param *cmdName		the pointer of function(key) name
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int LAUNCH_MCU_GET_NVARM(char *cmdName);
#endif

#if defined(CAN) | defined(ALL)
/**
 * To swicth the CAN device you want to control if haved multiple CAN devices.
 *
 * @param canIdx	the index of CAN device(1~N)
 *
 * @param if processed successfully, then return 1; or return 0.
 */
int switchCAN(int canIdx);

/**
 * To retrive the information of CAN from configuration file.
 *
 * @param *fConfig		the pointer of file
 * @param *pnDevice 	the pointer recorded the amount of CAN device
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int Get_CAN_DeviceInfo(FILE *fConfig, int *pnDevice);

/**
 * To launch command with input data to CAN and to retrive the result data.
 *
 * @param *cmdName		the pointer of function(key) name
 * @param *dataIn		the array of input data
 * @param dataInLen		the length of input data
 * @param *dataOut		the array of received data
 * @param *dataOutLen	the length of received data
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int LAUNCH_CAN_COMMAND(char *cmdName, BYTE *dataIn, int dataInLen, BYTE *dataOut, int *dataOutLen);

/**
 * To retrive the information of updating CAN from configuration file.
 *
 * @param *fConfig		the pointer of file
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int Get_CAN_UpdateInfo(FILE *fConfig);

/**
 * To launch command to flash CAN.
 *
 * @param *cmdName		the pointer of function(key) name
 *
 * @return if processed successfully, then return 1; or return 0.
 */
int LAUNCH_CAN_UPDATE(char *cmdName);
#endif

/**
 * To find out the index of command with function(key) name.
 *
 * @param *funName	the pointer of function(key) name
 * @param *cmdIdx 	the pointer recorded the index of command
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int findCommandIndex(char *funName, int *cmdIdx);

/**
 * To initiate the command pool within the struct of MCU content.
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int INIT_CMD_POOL();

/**
 * To Initiate the MCU or CAN devices.
 *
 * @param *machineNm	the name of machine(optional, you can assign "NULL" value)
 * @param devType 		0:MCU/1:CAN
 * @param *dev 			the name of uart
 * @param baudR			the baud rate
 * @param canType		0:NXP/1:ST(optional, needed if devType is 1(CAN))
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int LAUNCH_INIT_DEV(char *machineNm, int devType, char *dev, int baudR, int canType);

/**
 * To initiate the MCU or CAN devices with arguments and config file.
 *
 * @param argc 		the count of command line argument
 * @param *argv[]	the pointer of command line data
 *
 * @return if processing successfully, then return the pointer of config file; or return 0.
 */
FILE * LAUNCH_INIT_CONFIG(int argc ,char *argv[]);

/**
 * To exit the program.
 *
 * @param *cmdName	the pointer of function(key) name
 * @param *pfile	the pointer of config file
 * @param uiBase	1:program with menu/0:program without menu
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int LAUNCH_EXIT(char *cmdName, FILE *pfile, int uiBase);


/**
*To Check if the FLASH BIN file exists.
*If it exists, return 1; otherwise, return -1
*/
int FIND_FLASH_BIN_FILE();
int FIND_FunName(char *simple_funName, char *funName) ;

#ifdef __cplusplus
}
#endif
