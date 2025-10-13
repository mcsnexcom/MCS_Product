/**
 * TPMS Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/26 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

extern TPMS_DATA TPMS_Data[];
extern int nWheelNumber;

/**
 * Call Back Function.
 */
int FUNC_TPMS_GET_REALTIME_CALLBACK_DATA_FROM_MCU(int cmdIndex, char *pFunctionName);

/**
 * TPMS Function
 */
int FUNC_TPMS_SET_SENSOR_ID(int cmdIndex, char *pFunctionName);
int FUNC_TPMS_DISPLAY_MODE(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
