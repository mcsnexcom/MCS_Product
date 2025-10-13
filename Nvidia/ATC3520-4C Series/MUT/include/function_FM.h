/**
 * FM Function Header.
 *
 * Team: MCS,MR12
 * Date: 10/08 2018
 * Add load-modult loopback in /etc/pulse/default.pa
 */

/**
 * FM Radio Function
 */

#ifdef __cplusplus
extern "C" {
#endif

int FUNC_FM_POWER_ON_OFF(int cmdIndex, char *pFunctionName);
int FUNC_GET_BREAK(int cmdIndex, char *pFunctionName);
int FUNC_FM_CONFIG(int cmdIndex, char *pFunctionName);
int FUNC_FM_SET_VOLUME(int cmdIndex, char *pFunctionName);
int FUNC_FM_SET_MUTE(int cmdIndex, char *pFunctionName);
int FUNC_FM_SET_FREQ(int cmdIndex, char *pFunctionName);
int FUNC_FM_AUTO_SCAN(int cmdIndex, char *pFunctionName);
int FUNC_FM_RDS_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_FM_GET_PID(int cmdIndex, char *pFunctionName);
int FUNC_FM_GET_PS(int cmdIndex, char *pFunctionName);
int FUNC_FM_GET_RDS(int cmdIndex, char *pFunctionName);
int FUNC_FM_SEEK_UP(int cmdIndex, char *pFunctionName);
int FUNC_FM_SEEK_DOWN(int cmdIndex, char *pFunctionName);
int FUNC_FM_AUDIO_SWITCH(int cmdIndex, char *pFunctionName);
int FUNC_FM_GET_VOICE(int cmdIndex, char *pFunctionName);
int FUNC_FM_GET_FM_ZONE(int cmdIndex, char *pFunctionName);
int FUNC_FM_SET_FLASH(int cmdIndex, char *pFunctionName);
int FUNC_FM_LOAD_DEFAULT(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
