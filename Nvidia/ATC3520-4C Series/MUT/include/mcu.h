/**
 * Header file of MCU command API
 * 
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	4/9 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "mut_types.h"

#if defined(MCU) | defined(ALL)
/**
 * Let the specified programmed LED light on.
 *
 * @param data 		the dats struct
 */
void LAUNCH_MCU_CMD(MCU_CMD_DATA *data);
#endif //end of #if defined(MCU) | defined(ALL)

#if defined(CAN) | defined(ALL)
/**
 * Let the specified programmed LED light off.
 *
 * @param data 		the dats struct
 */
void LAUNCH_CAN_CMD(MCU_CMD_DATA *data);
#endif //end of #if defined(CAN) | defined(ALL)

// Add by Singo 2021/03/18 Start...
#if defined(ANDROID)
void LAUNCH_MCU_UPD(MCU_CMD_DATA *data);
#endif // end of #if defined(ANDROID)

#if defined(ANDROID)
void LAUNCH_CAN_UPD(MCU_CMD_DATA *data);
#endif // end of #if defined(ANDROID)
// Add by Singo 2021/03/18 End.....

#ifdef __cplusplus
}
#endif
