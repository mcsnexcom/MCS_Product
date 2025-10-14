/**
 * BKP Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/25 2020
 */

/**
 * Start Bettery Function
 */

#ifdef __cplusplus
extern "C" {
#endif

int FUNC_ST_BKP_GET_BACKUP_BATTERY_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_SMART_BATTERY_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_SMART_BATTERY_TEMPERATURE(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_BACKUP_BATTERY_TEMPERATURE(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_SMART_BATTERY_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_SMART_BATTERY_CAPACITY(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_SMART_BATTERY_CURRENT(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_BACKUP_BATTERY_CURRENT(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_THRESHOLD_SETTING(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_DELAY_TIME_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_DELAY_TIME_NOW(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_GET_POWER_OFF_VALUE(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_SET_DELAY_TIME_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_SET_POWER_OFF_VALUE(int cmdIndex, char *pFunctionName);
int FUNC_ST_BKP_SET_RESET_BAT(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
