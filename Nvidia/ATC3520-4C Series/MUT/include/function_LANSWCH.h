/**
 * LANSWCH Function Header.
 *
 * Team: MCS,MR12
 * Date: 01/20 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * LAN_SWITCH Function
 */

int FUNC_GET_CHIPID(int cmdIndex, char *pFunctionName);
int FUNC_GET_PORT_LINK_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_GET_PORT_LINK_SPEED(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
