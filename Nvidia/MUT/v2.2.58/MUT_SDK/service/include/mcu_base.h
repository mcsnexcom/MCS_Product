/**
 * The header file of MCU base.
 *
 * @Team	MR12/MCS
 * @Author 	Sam, William Ho
 * @Date	04/06 2022
 */
#ifndef MCU_BASE_H_
#define MCU_BASE_H_


#include <string.h>
#include <sys/time.h>

// The version of MCU Base library.
#define MCU_BASE_LIBRARY_VERSION "3.3.1"

/** The list of error code
 * 1 : Success

 * 0 : Failure
 * -1 : Fail to open serial port.
 * -2 : Fail to write data to MCU.
 * -3 : Fail to create thread.
 * -4 : Request Timeout.
 * -5 : MCU Busy.
 * -7 : Data Format Error.
 * -8 : CRC Error.
 * -20 : No Command.
 */

/**
 * Enable/Disable Debug Message Level.
 */
#define DEBUG_LITE		0x01
#define DEBUG_FULL		0x09


/**
 * Device List 
 */
#define DEVICE_SYSTEM		0x00
#define DEVICE_RESERVED1	0x01
#define DEVICE_RESERVED2	0x02
#define DEVICE_IAP		0x03
#define DEVICE_DEBUG		0x04
#define DEVICE_BIOS		0x05
#define DEVICE_CAN1		0x06
#define DEVICE_CAN2		0x07
#define DEVICE_IOT		0x08
#define DEVICE_NVR		0x09
#define DEVICE_BKP		0x0A
#define DEVICE_ODM		0x11
#define DEVICE_ERROR		0xFF

// The definition of command type
#define COMMAND_READ		0x00
#define COMMAND_WRITE		0x01
#define COMMAND_GET		0x02
#define COMMAND_SET		0x03
#define COMMAND_EVENT		0x04
#define COMMAND_OTHER		0x05

// The definition of event type
#define EVENT_TYPE_SYSTEM	0x01
#define EVENT_TYPE_CAN		0x10

// The definition of MCU type
#define MCU_TYPE_NXP		0x00
#define MCU_TYPE_ST		0x01
#define MCU_TYPE_CUSTOMISE	0xC0
#define MCU_TYPE_FM		0x0F

// The definition of st mode
#define ST_MODE_AP		0x01
#define ST_MODE_UPDATE		0x02

// The definition of nxp mode
#define NXP_MODE_AP		0x10
#define NXP_MODE_UPDATE		0x20

// The definition of command format
#define ST_START_CODE_F1	0xF1
#define ST_END_CODE_F2		0xF2
#define NXP_START_CODE_C1	0xC1
#define NXP_END_CODE_C2		0xC2
#define NXP_START_CODE_F1	0xF1
#define NXP_END_CODE_F2		0xF2

// The definition of data encode/decode
#define EXTENSION_CODE_F0	0xF0
#define EXTENSION_CODE_F1	0xF1
#define EXTENSION_CODE_F2	0xF2
#define EXTENSION_CODE_F3	0xF3
#define EXTENSION_CODE_C0	0xC0
#define EXTENSION_CODE_C1	0xC1
#define EXTENSION_CODE_C2	0xC2
#define EXTENSION_CODE_C3	0xC3

// The definition of read time of UART
#define READ_TIME_OUT		50	// (unit: 1 ms)
#define READ_TIME_OUT_UPDATE	20000	// (unit: 1 ms)

#if 0
#define READ_SIZE		4096
#define READ_MAX_SIZE		8192
#define WRITE_MAX_SIZE		4096
#else
#define READ_SIZE		1024
#define READ_MAX_SIZE		2048
#define WRITE_MAX_SIZE		1024
#endif

//#define ENUM_TO_STRING(name) # name

typedef int  BOOL;
typedef unsigned  char  BYTE;
typedef unsigned short  WORD;
typedef unsigned  long DWORD;

#define MCU_DEVICE_MAX 10
#define CAN_DEVICE_MAX 10

/**
 * The struct of MCU/CAN device information
 */
typedef struct mcu_device {
	char chEnable;
	char szDeviceName[64];
	char szBaudRate[16];
	char szMCUType[8];
} MCU_DEVICE, CAN_DEVICE;

/**
 * The struct of MCU/CAN update information
 */
typedef struct mcu_update_info {
	unsigned int MCU_startAddr;
	unsigned int FW_Info_Addr;
	unsigned int ProgramROM_Addr;
	char NVRAM_Enable;
	unsigned int NVRAM_Addr;
	char Verify_Enable;
	char CheckCode_Enable;
	unsigned int writeSize;
	unsigned int verifySize;
	char szFilePath[128];
	unsigned char szFWInfo[16];
	unsigned char updatePercentageLevel;
} MCU_UPDATE_INFO, CAN_UPDATE_INFO;

/**
 * The struct of MCU information.
 */
typedef struct mcu_info {
	MCU_DEVICE MCUDevice[MCU_DEVICE_MAX];
	CAN_DEVICE CANDevice[CAN_DEVICE_MAX];
	MCU_UPDATE_INFO MCUUpdateInfo;
	CAN_UPDATE_INFO CANUpdateInfo;
} MCU_INFO;

/**
 * The enumeration of baud rate.
 */
typedef enum {
	CAN_BAUD_12500 		= 12500,			//   12.5  kbps
	CAN_BAUD_12800 		= 12800,			//   12.8  kbps
	CAN_BAUD_16000 		= 16000,			//   16    kbps
	CAN_BAUD_20000 		= 20000,			//   20    kbps
	CAN_BAUD_25000 		= 25000,			//   25    kbps
	CAN_BAUD_31250 		= 31250,			//   31.25 kbps
	CAN_BAUD_32000 		= 32000,			//   32    kbps
	CAN_BAUD_40000 		= 40000,			//   40    kbps
	CAN_BAUD_50000 		= 50000,			//   50    kbps
	CAN_BAUD_62500 		= 62500,			//   62.5  kbps
	CAN_BAUD_64000 		= 64000,			//   64    kbps
	CAN_BAUD_80000 		= 80000,			//   80    kbps
	CAN_BAUD_100000 	= 100000,			//  100    kbps
	CAN_BAUD_125000 	= 125000,			//  125    kbps
	CAN_BAUD_160000 	= 160000,			//  160    kbps
	CAN_BAUD_200000 	= 200000,			//  200    kbps
	CAN_BAUD_250000 	= 250000,			//  250    kbps
	CAN_BAUD_400000 	= 400000,			//  400    kbps
	CAN_BAUD_500000 	= 500000,			//  500    kbps
	CAN_BAUD_1000000 	= 1000000,			// 1000    kbps
} can_baud_t;

/**
 * The structure of CAN packet.
 */
#define CAN_MSG_DATA_LEN	(8)				// CAN Msg data length
typedef struct can_msg {
	unsigned short ide;						// Standard/extended msg
	unsigned int id;						// 11 or 29 bit msg id
	unsigned short dlc;						// Size of data
	unsigned char data[CAN_MSG_DATA_LEN];	// Message pay load
	unsigned short rtr;						// RTR message
} can_msg_t;

/**
 * The structure of TPMS information.
 */
#define SENSOR_NUM_MAX		24
#define SENSOR_ID_LENGTH	16
typedef struct tpms_data {
	BYTE SensorID[SENSOR_ID_LENGTH];
	int temp;
	int psi;
	int vol;
	int alarm;
} TPMS_DATA;

/**
 *  The structure of command pool.
 */
#define CMD_SIZE	16		// The array size of command data.
#define CMD_POOL	2000	// The pool size of command structure.
typedef struct {
	int cmd_index;			// The index of command
	char funName[128];		// The name of function //added by William Ho on 2020/04/14
	int cmd_data[CMD_SIZE]; // The array of command
} cmd;

/**
 *  The structure of callback data.
 */
typedef struct callback_data {
	int fd;
	int type;
	WORD szDataLength;
	BYTE szData[128];
	can_msg_t canData;
	unsigned long receiveCANDataCount;
	unsigned int receiveErrorCount;
	unsigned long sendCommandSuccessCount;
	unsigned int sendCommandErrorCount;
	unsigned int sendCommandTimeCount;
} CALLBACK_DATA;

/**
 *  The structure of test data with sending of the CAN.
 */
typedef struct can_send_info {
	unsigned int nID;
	DWORD sendMax;
	DWORD intervalTime;
	int senFlag;
	unsigned int cmdIndex;
	unsigned long sendCommandSuccessCount;
	unsigned int sendCommandErrorCount;
	unsigned int sendCommandTimeCount;
} CAN_SEND_INFO;

/**
 *  The structure of MCU content.
 */
#define CAN_DATA_MAX	1000
typedef struct mcu_device_content {
	char szProductName[64];
	int result;
	int debugLevel;

	pthread_t receive_thread;
	int cancel_receive_thread;
	pthread_t send_thread;
	int cancel_send_thread;

	int fd;

	int mcuType;
	int stMode;
	int nxpMode;

	WORD cmd_count;
	cmd cmd_pool[CMD_POOL];

	BYTE receiveDataBuffer[READ_MAX_SIZE];
	unsigned int receiveDataStartIndex;
	unsigned int F1_Index;
	int catch_F1_Flag;

	BYTE Device;
	BYTE Command;
	BYTE Address;
	BYTE validData[READ_MAX_SIZE];
	WORD validDataLength;
	BYTE lock;
#if 0
	int canLock;
	can_msg_t canDatabuffer[CAN_DATA_MAX];	// Storge CAN data to buffer
	WORD canDatabufferCount;
	can_msg_t canData[CAN_DATA_MAX];		// Get CAN data from AP
	WORD canDataCount;
#else
	can_msg_t canData;		// Get CAN data from AP
#endif

	BYTE CommandResponseData[READ_SIZE];
	WORD CommandResponseDataLength;

	CAN_SEND_INFO canSendInfo;
	unsigned long receiveCANDataCount;
	unsigned int receiveErrorCount;

	MCU_INFO mcuInfo;

} MCU_CONTENT;

/**
 * Pushing command into pool.
 *
 * @param *mcu_content	the pointer of MCU content
 * @param index			the index of command data position
 * @param device		the device value
 * @param command		the command value
 * @param address		the address value
 */
void pushCommandToPool(MCU_CONTENT *mcu_content, int index, int device, int command, int address);

/**
 * Pushing command into pool customisely.
 *
 * @param *mcu_content	the pointer of MCU content
 * @param index			the index of command data position
 * @param *cmdData		the array of command data
 * @param cmdDataLen	the length of array
 */
void pushCommandToPoolCustomise(MCU_CONTENT *mcu_content, int index, char *cmdData, int cmdDataLen);

/**
 * To initiate the MCU seetings.
 *
 * @param *pszUARTPortName	the pointer of MCU content
 * @param mcuType			the type of MCU
 * @param baudrate			the baud rate of communicating with MCU
 *
 * @return the struct of MCU content
 */
MCU_CONTENT *init_MCU(char *pszUARTPortName, int mcuType, int baudrate);

/**
 * To exit MCU library.
 *
 * @param *mcu_content	the pointer of MCU content
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int exit_LIB(MCU_CONTENT *mcu_content);

/**
 * To write command to MCU.
 *
 * @param *mcu_content	the pointer of MCU content
 * @param index			the index of command data position
 * @param *data			the array of command data
 * @param dataLen	the length of array
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int defaultWrite(MCU_CONTENT *mcu_content, int index, BYTE *data, int dataLen);

/**
 * The function of sending command to MCU.
 * This function is provided as interface to some body invoke.
 *
 * @param *mcu_content	the pointer of MCU content
 * @param index			the index of command data position
 * @param *data			the array of command data
 * @param dataLen		the length of array
 * @param *dataOut		the array of received data
 * @param *dataOutLen	the length of array
 *
 * @return if processing successfully, then return 1; or return 0.
 */
//int launch(MCU_CONTENT *mcu_content, int index, BYTE *data, int dataLen, BYTE *dataOut, int *dataOutLen);
int sendCMD(MCU_CONTENT *mcu_content, int index, BYTE *data, int dataLen, BYTE *dataOut, int *dataOutLen);

/**
 * The function of receiving command from MCU.
 *
 * @param *mcu_content	the pointer of MCU content
 * @param *dataOut		the array of received data
 * @param *dataOutLen	the length of array
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int receive(MCU_CONTENT *mcu_content, BYTE *dataOut, int *dataOutLen);

/**
 * To get the command by index.
 *
 * @param *mcu_content	the pointer of MCU content
 * @param index			the index of command data position
 *
 * @return the pointer of command structure
 */
cmd * getCommandByIndex(MCU_CONTENT *mcu_content, int index);

/**
 * The function of calculating CRC of data.
 *
 * @param *ptr		the array of calculated data
 * @param Length	the length of data
 *
 * @return the CRC data
 */
BYTE Get_CRC8(BYTE *ptr, unsigned int Length);

/**
 * The function of waiting to read MCU data with timeout.
 *
 * @param *mcu_content	the pointer of MCU content
 * @param timeout		the timeout value
 *
 * @return if processing successfully, then return 1; or return 0.
 */
int WaitForRecevData(MCU_CONTENT *mcu_content, unsigned long int timeout);

/**
 * To register callback function from library.
 *
 * @param byByte1	data argument 1 (deprecated)
 * @param byByte2	data argument 2 (deprecated)
 * @param *callback the pointer of function
 */
void Register_MCU_EventCallBack(BYTE byByte1, BYTE byByte2, void (*callback)(CALLBACK_DATA));

/**
 * The function of reading data from MCU.
 *
 * @param *mcu_content	the pointer of MCU content
 */
void ReceiveMessageFromMCU(MCU_CONTENT *mcu_content);

/**
 * The function of decoding from FM MCU data.
 *
 * @param *mcu_content	the pointer of MCU content
 */
int FM_DecodingResponse(MCU_CONTENT *mcu_content);

/**
 * The function of decoding from customised MCU data.
 *
 * @param *mcu_content	the pointer of MCU content
 */
int Customise_DecodingResponse(MCU_CONTENT *mcu_content);

/**
 * The function of decoding from ST MCU data.
 *
 * @param *mcu_content	the pointer of MCU content
 */
int ST_DecodingResponse(MCU_CONTENT *mcu_content);

/**
 * The function of decoding from NXP MCU data.
 *
 * @param *mcu_content	the pointer of MCU content
 */
int NXP_DecodingResponse(MCU_CONTENT *mcu_content);

/**
 * To retrive the version of MCU library.
 *
 * @param **pszVession	the array of assigned data
 */
void MCU_Library_Version(char *pszVession);

#endif /* MCU_BASE_H_ */
