/**
 * The header file of base function.
 *
 * @Team 	MCS,MR12
 * @Author 	Sam, William Ho
 * @Date 	3/20 2020
 */

#ifdef __cplusplus
extern "C" {
#endif


extern BYTE data[128];
extern BYTE dataOut[128];
extern int dataOutLength;

// MCU/CAN update attributes
extern unsigned int g_dwMCU_Start_Pos;

extern unsigned int g_dwMCU_Program_Offset;
extern unsigned int g_dwMCU_Program_Addr;

extern unsigned int g_dwMCU_Program_Update_MaxSize;
extern unsigned int g_dwMCU_Program_Update_Addr;
extern unsigned int g_dwMCU_Program_Update_CurrectSize;
extern unsigned int g_dwMCU_Program_Update_RemainSize;
extern unsigned int g_dwMCU_Program_Update_Size;

extern unsigned int g_dwMCU_Program_Verify_MaxSize;
extern unsigned int g_dwMCU_Program_Verify_Addr;
extern unsigned int g_dwMCU_Program_Verify_CurrectSize;
extern unsigned int g_dwMCU_Program_Verify_RemainSize;
extern unsigned int g_dwMCU_Program_Verify_Size;

extern unsigned int g_dwFW_Info_Addr;

extern char szBIN_FWInfo[16];

/**
 * The reserved function.
 *
 * @param cmdIndex 			the command index
 * @param *pFunctionName	function(key) name
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int FUNC_RESERVED(int cmdIndex, char *pFunctionName);

/**
 * The function of getting MCU library version.
 *
 * @param cmdIndex 			the command index
 * @param *pFunctionName	function(key) name
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int FUNC_ST_SYSTEM_GET_MCU_LIBRARY_VERSION(int cmdIndex, char *pFunctionName);

/**
 * The function of exit.
 *
 * @param cmdIndex 			the command index
 * @param *pFunctionName	function(key) name
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int FUNC_EXIT(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif
