/**
 * The header file of library of UART.
 *
 * @Team	MR12/MCS
 * @Author 	William Ho
 * @Date	9/4 2017
 */
#ifndef UART_LIB_H_
#define UART_LIB_H_

#define FALSE 0
#define TRUE  1

typedef enum {
	BLKING,     //Blocking mode
	NONBLKING   //Non-Blocking mode
} UART_MODE;

typedef enum {
	RS232,
	RS485
} UART_TYPE;

typedef enum {
	ASCII,
	HEX
} UART_FORMAT;

/**
 * Opening the specified port of UART.
 *
 * @param dev		the name of device
 * @param baudrate	baud rate
 * @param mode		UART_MODE.BLKING:blocking mode / UART_MODE.NONBLKING:non-blocking mode
 * @param type		the type of uart (UART_TYPE.RS232:RS232 / UART_TYPE.RS485:RS485)
 * @param tio		the structure of terminal pointer input / output system (default is library provided)
 * @param setGPIO	the function pointer which setted GPIO
 *
 * @return if opening the specified port of UART successfully, return file descriptor or return -1.
 */
int UART_Open(char *dev, int baudrate, UART_MODE mode, UART_TYPE type, struct termios *tio, void (*setGPIO)(UART_MODE));

/**
 * Closing the specified port of UART.
 *
 * @param fd		file descriptor
 *
 * @return if closing the specified port of UART successfully, return 0 or return -1.
 */
int UART_Close(int fd);

/**
 * Sending data to the specified port of UART.
 *
 * @param fd		file descriptor
 * @param msg		data sent
 * @param format	UART_FORMAT.ASCII:ASCII / UART_FORMAT.HEX:HEX (default is UART_FORMAT.ASCII)
 *
 * @return if sending message successfully, return 0 or return -1.
 */
int UART_Send(int fd, char *msg, UART_FORMAT format);

/**
 * Reading data from the specified port of UART.
 *
 * @param fd		file descriptor
 *
 * @return if reading data successfully, return message or return null.
 */
char* UART_Receive(int fd);

#endif /* UART_LIB_H_ */
