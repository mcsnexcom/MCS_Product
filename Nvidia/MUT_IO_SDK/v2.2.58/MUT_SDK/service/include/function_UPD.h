/**
 * MCU Update Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/18 2020
 */

#ifdef __cplusplus
extern "C" {
#endif


typedef int			BOOL;
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef unsigned long		DWORD;

/**
 * ST MCU Update
 */
int FUNC_ST_MCU_UPDATE_START(int cmdIndex, char *pFunctionName);
int FUNC_ST_MCU_UPDATE_CANCEL(int cmdIndex, char *pFunctionName);
int FUNC_ST_MCU_GET_MCU_NVRAM(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif

