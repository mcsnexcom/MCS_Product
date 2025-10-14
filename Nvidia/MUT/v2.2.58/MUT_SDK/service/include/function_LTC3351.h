#ifndef FUNCTION_LTC3351_H
#define FUNCTION_LTC3351_H
/**
 * LTC3351 Function Header.
 *
 * Team: MCS,MR12
 * Date: 05/31 2024
 */

/**
 * LTC3351 Function
 */

//Add by LiCheng 2024/05/31 start
int FUNC_LTC3351_GET_INPUT_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_CAPACITOR_STACK_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_OUTPUT_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_TEMPERATURE(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_CHARGE_CURRENT(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_INPUT_CURRENT(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_CAPACITOR_STACK_CAPACITANCE_VALUE(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_VCAP1(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_VCAP2(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_VCAP3(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_VCAP4(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_VCAP_NUM(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_ADV_VOUT(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_SCAP_TEMPSEN(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_ADC_VCAP(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_SLAVE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_VOLT_TYPE(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_CAP_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_VOLT_PERCENT(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_CAP_HEALTH(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_GET_CAP_LED(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_SET_VOLT_TYPE(int cmdIndex, char *pFunctionName);
int FUNC_LTC3351_SET_CAP_LED(int cmdIndex, char *pFunctionName);

#endif // FUNCTION_LTC3351