/**
 * IOT Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/26 2020
 */

/**
 * IoT Get Function
 */

#ifdef __cplusplus
extern "C" {
#endif

int FUNC_ST_IOT_GET_APN(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_DNS(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_SERVER_IP(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_SERVER_PORT(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_IMEI(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_MACHINE_NAME(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_PASSWORD(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_PHONE_NUMBER(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_TRACKER_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_TRACKER_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_TRACKER_DELAY_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_TRACKER_RESPONSE_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_TRACKER_THRESHTAP(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_TRACKER_ANGLE(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_SMS_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_SMS_CODING_TYPE(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_SMS_CONTENT(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_GET_SMS_RESPONSE_TIME(int cmdIndex, char *pFunctionName);

/**
 * IoT Get Function
 */
int FUNC_ST_IOT_SET_APN(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_DNS(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_SERVER_IP(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_SERVER_PORT(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_MACHINE_NAME(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_PASSWORD(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_PHONE_NUMBER(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_TRACKER_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_TRACKER_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_TRACKER_DELAY_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_TRACKER_RESPONSE_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_TRACKER_THRESHTAP(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_TRACKER_ANGLE(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_SMS_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_SMS_CODING_TYPE(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_SMS_CONTENT(int cmdIndex, char *pFunctionName);
int FUNC_ST_IOT_SET_SMS_RESPONSE_TIME(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
