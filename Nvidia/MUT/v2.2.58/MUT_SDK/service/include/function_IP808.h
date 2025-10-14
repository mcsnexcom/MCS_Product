#ifndef FUNCTION_IP808_H
#define FUNCTION_IP808_H
/**
 * IP808 Function Header.
 *
 * Team: MCS,MR12
 * Date: 9/6 2023
 */

/**
 * IP808 Function
 */

#ifdef __cplusplus
extern "C" {
#endif


//Add by Hewei 08/28/2023 start
int FUNC_808_PSE_FW_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_808_PSE_TEMPERATURE(int cmdIndex, char *pFunctionName);
int FUNC_808_TOTAL_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_808_PORT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_808_PORT_POWER_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_808_ALL_PORT_LINK_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_808_PORT_POWER_CONTROL(int cmdIndex, char *pFunctionName);
//Add by Hewei 08/28/2023 end

#endif // FUNCTION_IP808_H

#ifdef __cplusplus
}
#endif
