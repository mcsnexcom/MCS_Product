#ifndef FUNCTION_IP8008_H
#define FUNCTION_IP8008_H
/**
 * IP8008 Function Header.
 *
 * Team: MCS,MR12
 * Date: 11/7 2024
 */

/**
 * IP8008 Function
 */

#ifdef __cplusplus
extern "C" {
#endif


//Add by Hewei 08/28/2023 start
int FUNC_IP8008_GET_FW_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_IP8008_GET_TOTAL_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_IP8008_GET_PORT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_IP8008_GET_PORT_POWER_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_IP8008_GET_ALL_PORT_LINK_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_IP8008_SET_PORT_POWER_CONTROL(int cmdIndex, char *pFunctionName);

#endif // FUNCTION_IP8008_H

#ifdef __cplusplus
}
#endif
