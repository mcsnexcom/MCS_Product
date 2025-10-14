/**
 * MCU System Function Header.
 *
 * Team: MCS,MR12
 * Date: 03/18 2020
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Call Back Function.
 */
int FUNC_ST_CAN_GET_REALTIME_CALLBACK_DATA_FROM_MCU(int cmdIndex, char *pFunctionName);

//--------------------------------------------------

/**
 * ST System Get Function.
 */
int FUNC_ST_SYSTEM_GET_MCU_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_HW_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_DTP_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BL_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_EVENT_LOG(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_SYSTEM_PARAMETER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WWAN_FULLCARD_POWEROFF(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_OS_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_IGNITION_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_SUPPLY_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_TEMPERATURE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_LED_OUTPUT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_POWER_TYPE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_DELAY_TIME_OPTION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_STARTUP_SHUTDOWN_OPTION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_POWER_RANGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_ALART_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_PANEL_BRIGHTNESS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WWAN_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WIFI_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_GPS_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_USB_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_LAN_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_RTC_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WATCHDOG_CONFIGURE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_LS_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_FLASH_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_MDO_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_INPUT_FREQUENCY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_MDI_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_INPUT_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_GSENSOR_DATA(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_CAN_SWITCH_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_AUDIO_VOLUME(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_AUDIO_MUTE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_AUDIO_SWITCH_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_MDIO_MODE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_I_BUTTON_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_I_BUTTON_KEY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_RFID_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_RFID_KEY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_CAN_MODULE_POWER_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_HEATER_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_NVR_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_CAN_DO_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_AUTO_BACKLIGHT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_CAN_MODULE_GPI_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_CAN_DI_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_SIM_CARD_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_HEATER_POWER_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BACKUP_BATTERY_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_GPIO_MODE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BACKUP_BATTERY_TEMPERATURE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_GPO_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_POE_POWER_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WAKE_ON_LAN_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_GPI_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_LOW_VOLTAGE_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_EXTERNAL_12V_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_EXTERNAL_5V_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_GPI_ACTIVE_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_GPO_PULLUP_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_SIM_CARD_DETECT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WWAN_CN7_RESET_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_PULSE_COUNT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WWAN_CN14_RESET_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_IO_BOARD_ID(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BACKUP_BATTERY_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_EXPANSION_BOARD_ID(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_VIDEO_CONTROL_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_WAKEUP_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_PROGRAM_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_VIDEO_INPUT_SOURCE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_LCD_PWM_FREQUENCY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_HEALTH_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_MIC_IN_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_CAN_IMP_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_PCIE_SATA_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_FAN_VALUE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_FAN_RPM(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_FAN_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_POWER_BOARD_VERSION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_AST(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_STARTUP_COUNT(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_SP339A_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BOOT_TIME(int cmdIndex, char *pFunctionName);
// Modify by Ted 2022/05/27
int FUNC_ST_SYSTEM_GET_BUZZER_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_TEMP_BEEP_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_KEY_LOCK_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_SLOT_MODE(int cmdIndex, char* pFunctionName);
//Modify by Hewei 2023/08/17
int FUNC_ST_SYSTEM_GET_BOARD_ID(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_POWER_BOARD_STATUS(int cmdIndex, char *pFunctionName);
//Modify by Hewei 2023/09/21
int FUNC_ST_SYSTEM_GET_KEY_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_Wake_on_LAN_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_OS_Control(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_KEY_LED_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_CONVERSE_FREQUENCY_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_ODOMETER_LOCK_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_RTC_BATTERY_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_PROTECT_KEY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_ANALOG_IN_VOLTAGE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BACKLIGHT_VOLUME_KEY_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_BIOS_NUM(int cmdIndex, char *pFunctionName);
//Modify by Tony 2025/06/27
int FUNC_ST_SYSTEM_GET_MODULE_ID(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_MODULE_NAME(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_MACHINE_PARAMETER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_GET_HEARTBEAT_STATUS(int cmdIndex, char *pFunctionName);
//--------------------------------------------------

/**
 * ST System Set Function.
 */
int FUNC_ST_SYSTEM_SET_BOOT_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_EVENT_LOG(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_BACKUP_EVENT_CLEAR(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_SYSTEM_PARAMETER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WWAN_FULLCARD_POWEROFF(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_OS_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_LOAD_DEFAULT(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_RTC_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_LED_OUTPUT_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_POWER_TYPE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_DELAY_TIME_OPTION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_STARTUP_SHUTDOWN_OPTION(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_ALARM_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_PANEL_BRIGHTNESS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WWAN_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WIFI_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_BT_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_GPS_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_USB_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_LAN_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_RTC_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WATCHDOG_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WATCHDOG_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_FLASH_UPDATE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_MDO_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_G_SENSOR_DATA(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_I_BUTTON_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_POWER_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_CAN_SWITCH_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_AUDIO_VOLUME(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_I_BUTTON_KEY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_AUDIO_MUTE_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_AUDIO_SWITCH_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_RFID_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_MDIO_MODE_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_RFID_KEY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_NVR_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_CAN_MODULE_POWER_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_CAN_MODULE_GPO_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_HEATER_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_SIM_CARD_SELECT(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_AUTO_BACKLIGHT_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_POE_POWER_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_CLEAR_LOW_VOLTAGE_FLAG(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_HEATER_POWER_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_GPIO_MODE_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_GPO_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WAKE_ON_LAN_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_EXTERNAL_12V_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_EXTERNAL_5V_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_VIDEO_CONTROL_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WAKEUP_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_PROGRAM_LED_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_VIDEO_INPUT_SOURCE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_LCD_PWM_FREQUENCY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_HEALTH_LED_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_MIC_IN_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_CAN_IMP_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_GPI_ACTIVE_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_GPO_PULLUP_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_SIM_CARD_DETECT_STATUS(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WWAN_CN7_RESET_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WWAN_CN14_RESET_TIME(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_PCIE_SATA_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_FAN_VALUE_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_FAN_MODE_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_AST(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_SP339A_MODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_KEY_LOCK_CONTROL(int cmdIndex, char *pFunctionName);
// Modify by Ted 2022/05/27
int FUNC_ST_SYSTEM_SET_BUZZER_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_TEMP_BEEP_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_GPI_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_POWER_BUTTON_CONTROL(int cmdIndex, char *pFunctionName);
//Modify by Hewei 2023/09/21
int FUNC_ST_SYSTEM_SET_KEY_LED_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_OS_Control(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_LED_OUTPUT_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WIFI_Control(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_WATCHDOG_Control(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_CONVERSE_FREQUENCY_TIMER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_ODOMETER_LOCK_CONTROL(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_PULSE_COUNT_RESET(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_PROTECT_KEY(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_BACKLIGHT_VOLUME_KEY_SELECT(int cmdIndex, char *pFunctionName);
//Modify by Tony 2025/06/27
int FUNC_ST_SYSTEM_SET_MACHINE_PARAMETER(int cmdIndex, char *pFunctionName);
int FUNC_ST_SYSTEM_SET_HEARTBEAT_CONTROL(int cmdIndex, char *pFunctionName);
//--------------------------------------------------

/**
 * ST CAN AP Function
 */
int FUNC_ST_CAN_GET_ERROR_CODE(int cmdIndex, char *pFunctionName);
int FUNC_ST_CAN_SET_SPEED(int cmdIndex, char *pFunctionName);
int FUNC_ST_CAN_DISABLE_AND_CLEAR_ALL_FILTER(int cmdIndex, char *pFunctionName);
int FUNC_ST_CAN_SET_FILTER(int cmdIndex, char *pFunctionName);
int FUNC_ST_CAN_EDIT_MESSAGE_TO_SENDING(int cmdIndex, char *pFunctionName);
int FUNC_ST_CAN_AUTO_SEND(int cmdIndex, char *pFunctionName);
//int FUNC_ST_CAN_AUTO_SEND_WITH_GET_REALTIME_DATA(int cmdIndex, char *pFunctionName);
int FUNC_ST_CAN_STOP_TRANSMIT(int cmdIndex, char *pFunctionName);
int FUNC_ST_CAN_CLEAR_RECEIVE_FIFO(int cmdIndex, char *pFunctionName);

#ifdef __cplusplus
}
#endif

