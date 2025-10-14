/**
 * Update MCU firmware function header of the NXP_CAN.
 *
 * Team: MCS,MR12
 * Date: 03/23 2020
 */

/**
 * NXP MCU Update
 */

#ifdef __cplusplus
extern "C" {
#endif

int FUNC_NXP_MCU_UPDATE_START(int cmdIndex, char *pFunctionName);
int FUNC_NXP_MCU_UPDATE_CANCEL(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
