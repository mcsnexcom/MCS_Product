/**
 * NXP CAN Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/18 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int receiveCANDataCountOnAP;

/**
 * Call Back Function.
 */
int FUNC_NXP_CAN_GET_REALTIME_CALLBACK_DATA_FROM_MCU(int cmdIndex, char *pFunctionName);

/**
 * NXP CAN AP Function
 */
int FUNC_NXP_CAN_SELECT_DEVICE(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_READ_FW_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_READ_BL_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_SET_SPEED(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_DISABLE_AND_CLEAR_ALL_FILTER(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_SET_FILTER(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_EDIT_MESSAGE_TO_SENDING(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_AUTO_SEND(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_STOP_TRANSMIT(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_GET_ERROR_CODE(int cmdIndex, char *pFunctionName);
int FUNC_NXP_CAN_READ_INPUT_VOLTAGE(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
