/**
 * Header file of MUT client functions
 * 
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	4/9 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "mut_types.h"

/**
 * To set the server FIFO name.
 *
 * @param FIFO_NM 	the pointer of server FIFO name.
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int Set_Server_FIFO(char *FIFO_NM);

#if defined(MCU) | defined(ALL)
/**
 * Register the callback function on MUT service to receive event.
 *
 * @param callback 	the pointer of function.
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int Reg_Event_CF(void (*callback)(int, BYTE, BYTE *));

/**
 * Register the callback function on MUT service to receive specific event type.
 *
 * @param callback 	the pointer of function.
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int Reg_Event_CF_type(void (*callback)(int, BYTE, BYTE *), int);

/**
 * Register the callback function on MUT service to receive heartbeat event type.
 *
 * @param callback 	the pointer of function.
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int Reg_Heartbeat_Monitor(int interval_sec, void (*callback)(void));

/**
 * Unregister the callback function from MUT service.
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int UnReg_Event();

/**
 * Launching a command into MCU service.
 *
 * @param *cmdName 		the command key name
 * @param *dataIn		the array of input data
 * @param dataInLen		the length of input data array
 * @param *dataOut		the array of output data
 * @param *dataOutLen	the length of output data array
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int LAUNCH_MCU_CMD(char *cmdName, BYTE *dataIn, int dataInLen, BYTE *dataOut, int *dataOutLen);
#endif //end of #if defined(MCU) | defined(ALL)

// Add by Singo 2021/03/18 Start...
#if defined(ANDROID)
int LAUNCH_MCU_UPD(char *cmdName, BYTE *dataIn, int dataInLen, BYTE *dataOut, int *dataOutLen);
int LAUNCH_CAN_UPD(char *cmdName, BYTE *dataIn, int dataInLen, BYTE *dataOut, int *dataOutLen);
#endif
// Add by Singo 2021/03/18 End.....

#if defined(CAN) | defined(ALL)
/**
 * Register the callback function on MUT service to receive CAN data.
 *
 * @param callback 	the pointer of function.
 *        The array of BYTE(big endian) is receiveCANDataCount(8 bytes)+receiveErrorCount(4 bytes)+sendCommandSuccessCount(8 bytes)
 *        +sendCommandErrorCount(4 bytes)+sendCommandTimeCount(4 bytes)+fd(2 bytes)+ide(2 bytes)+rtr(2 bytes)+dlc(2 bytes) = 36 bytes
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int Reg_CAN_CF(void (*callback)(int, BYTE[]));

/**
 * Unregister the CAN data callback function from MUT service.
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int UnReg_CAN();

/**
 * Launching a command into CAN service.
 *
 * @param *cmdName 		the command key name
 * @param *dataIn		the array of input data
 * @param dataInLen		the length of input data array
 * @param *dataOut		the array of output data
 * @param *dataOutLen	the length of output data array
 *
 * @return the result of execution (0: Failure/1: Success)
 */
int LAUNCH_CAN_CMD(char *cmdName, BYTE *dataIn, int dataInLen, BYTE *dataOut, int *dataOutLen);
#endif //end of #if defined(CAN) | defined(ALL)

#ifdef __cplusplus
}
#endif
