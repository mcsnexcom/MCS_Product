/**
 * VMD Function Header.
 *
 * Joey Wang
 * Team: MCS,MR12
 * Date: 06/21 2019
 */

#ifdef __cplusplus
extern "C" {
#endif


/**
 * VMD Function
 */
int FUNC_ST_VMD_GET_DEVICE_TYPE(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_GET_VIDEO_INPUT_SOURCE(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_GET_MUTE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_GET_AUTO_BACKLIGHT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_GET_VIDEO_CONTROL_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_GET_PANEL_MODE(int cmdIndex, char *pFunctionName);

int FUNC_ST_VMD_SET_VIDEO_INPUT_SOURCE(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_SET_MUTE_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_SET_AUTO_BACKLIGHT_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_SET_VIDEO_CONTROL_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_SET_KEY_SIMULATION(int cmdIndex, char *pFunctionName);
int FUNC_ST_VMD_SET_PANEL_CONTROL(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
