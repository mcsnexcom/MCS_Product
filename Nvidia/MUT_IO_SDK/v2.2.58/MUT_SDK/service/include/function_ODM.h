/**
 * ODM Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/26 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ODM Get Function
 */
int FUNC_ST_ODM_GET_FACTORY_DEFAULT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_WIFI_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_WIFI_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_WWAN_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_WWAN_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_GPS_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_GPS_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_VINM_FAULT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_SIM_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_DELAY_ON_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_DELAY_OFF_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_WAKEUP_EVENT(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_GSENSOR_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_POWER_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_POWER_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_WWAN_ENABLE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_GET_WWAN_RESET_STATUS(int cmdIndex, char *pFunctionName);

/**
 * ODM Set Function
 */
int FUNC_ST_ODM_SET_FACTORY_DEFAULT_FLAG(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_WIFI_LED_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_WIFI_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_WWAN_LED_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_WWAN_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_GPS_LED_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_GPS_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_VINM_FAULT_OFF_FLAG(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_DELAY_ON_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_DELAY_OFF_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_GSENSOR_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_POWER_LED_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_POWER_LED_FLASH_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_WWAN_ENABLE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_ODM_SET_WWAN_RESET_STATUS(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
