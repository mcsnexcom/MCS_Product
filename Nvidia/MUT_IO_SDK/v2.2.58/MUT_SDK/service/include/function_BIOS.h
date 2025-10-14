/**
 * MCU System Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/18 2020
 */

#ifdef __cplusplus
extern "C" {
#endif


int FUNC_ST_BIOS_GET_AUTO_REBOOT_FUNCTION(int cmdIndex, char *pFunctionName);
int FUNC_ST_BIOS_SET_AUTO_REBOOT_FUNCTION(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
