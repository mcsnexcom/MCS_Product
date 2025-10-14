/**
 * POE Function Header.
 *
 * Team: MCS,MR12
 * Date: 10/18 2018
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * POE Function
 */
int FUNC_PSE_FW_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_PSE_TEMPERATURE(int cmdIndex, char *pFunctionName);
int FUNC_TOTAL_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_POWER_BUDGET(int cmdIndex, char *pFunctionName);
int FUNC_PORT1_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_PORT2_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_POE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_PORT_POWER_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_PORT_1_POWER_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_PORT_2_POWER_CONSUMPTION(int cmdIndex, char *pFunctionName);
int FUNC_ALL_PORT_LINK_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_POE_CARD_DETECT(int cmdIndex, char *pFunctionName);
/* Add by Ted 08/23/2023 Start */
int FUNC_POE_GET_POWER_BUDGET(int cmdIndex, char *pFunctionName);
/* Add by Ted 08/23/2023 End */
/* Add by Ricky 01/20/2020 Start */
int FUNC_PORT_POWER_CONTROL(int cmdIndex, char *pFunctionName);
/* Add by Ricky 01/20/2020 End */
/* Add by Ted 08/23/2023 Start */
int FUNC_POE_SET_POWER_BUDGET(int cmdIndex, char *pFunctionName);
/* Add by Ted 08/23/2023 End */

#ifdef __cplusplus
}
#endif
