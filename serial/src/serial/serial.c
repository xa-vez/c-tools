
/**
 * @file serial.c
 * @brief This is the source file.
 * $Id: $
 **/

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#include <stdio.h>   /* Standard Input Output               */
#include <fcntl.h>   /* File Control Definitions            */
#include <termios.h> /* POSIX Terminal Control Definitions  */
#include <unistd.h>  /* UNIX Standard Definitions           */
#include <errno.h>   /* ERROR Number Definitions            */
#include <stdlib.h>  /* C Standard Library                  */
#include <string.h>  /* C String Library                    */
#include "serial.h"  /* The module API                      */

//******************************** DEFINES ***********************************//
//============================================================================//


//******************************** TYPEDEFS **********************************//
//============================================================================//

//********************************* ENUMS ************************************//
//============================================================================//

//*************************** PRIVATE CONSTANTS ******************************//
//============================================================================//

//**************************** PUBLIC CONSTANTS ******************************//
//============================================================================//

//*************************** PRIVATE VARIABLES ******************************//
//============================================================================//

//***************************  PUBLIC VARIABLES ******************************//
//============================================================================//

//**************************  PRIVATE FUNCTIONS ******************************//
//============================================================================//

//***************************  PUBLIC FUNCTIONS ******************************//
//============================================================================//
#ifdef SERIAL_TEST_INCLUDED
/**
 * @brief serial test function
 * @return error status
 */
int serial_test(void)
{
	int fd, error;

	error = serial_open(&fd);
	if (error)
		printf("[serial] Error opening port\r\n");

	error = serial_write(&fd, "AT+WLAP\r\n");
	if (error)
		printf("[serial] Error writing port\r\n");

	sleep(5);

	error = serial_read(&fd, NULL);
	if (error)
		printf("[serial] Error reading port\r\n");

	error = serial_close(&fd);

	if (error)
		printf("[serial] Error closing port\r\n");

	return 0;
}
#endif //SERIAL_TEST_INCLUDED

/**
 * @brief serial port open (default settings)
 * @param[in] file descriptor pointer
 * @return error starus
 */
int serial_open(int * fd) {
	int descriptor;

	if (fd == NULL) {
		return -1;
	}

	printf("[serial] +----------------------------------+\r\n");
	printf("[serial] |       Opening Serial Port        |\r\n");
	printf("[serial] +----------------------------------+\r\n");

	/* O_RDWR Read/Write access to serial port           */
	/* O_NOCTTY - No terminal will control the process   */
	/* O_NDELAY -Non Blocking Mode,Does not care about-  */
	/* -the status of DCD line,Open() returns immediatly */
	descriptor = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);

	if (descriptor == -1) { /* Error Checking */
		printf("[serial] Error opening %s \r\n", SERIAL_PORT);
	} else {
		printf("[serial] %s Opened Successfully\r\n", SERIAL_PORT);
	}

	/*** Setting the Attributes of the serial port using termios structure ****/
	struct termios SerialPortSettings;
	tcgetattr(*fd, &SerialPortSettings); /* Get the current attributes of the Serial port */

	cfsetispeed(&SerialPortSettings, SERIAL_BAUDRATE); /* Set Read  Speed as SERIAL_BAUDRATE                       */
	cfsetospeed(&SerialPortSettings, SERIAL_BAUDRATE); /* Set Write Speed as SERIAL_BAUDRATE                       */

	SerialPortSettings.c_cflag &= ~PARENB; /* Disables the Parity Enable bit(PARENB),So No Parity   */
	SerialPortSettings.c_cflag &= ~CSTOPB; /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	SerialPortSettings.c_cflag &= ~CSIZE; /* Clears the mask for setting the data size             */
	SerialPortSettings.c_cflag |= CS8; /* Set the data bits = 8                                 */

	SerialPortSettings.c_cflag &= ~CRTSCTS; /* No Hardware flow Control                         */
	SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */

	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY); /* Disable XON/XOFF flow control both i/p and o/p */
	SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); /* Non Cannonical mode                            */

	SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/


	if ((tcsetattr(descriptor, TCSANOW, &SerialPortSettings)) != 0) {/* Set the attributes to the termios structure*/
		printf("[serial] Error in Setting attributes\r\n");
	} else {
		printf("[serial] (%d) BaudRate (1)StopBits (None)Parity \r\n", SERIAL_BAUDRATE);
	}

	*fd = descriptor;

	return 0;
}

/**
 * @brief serial close function
 * @param[in] file descriptor pointer
 * @return error status
 */
int serial_close(int * fd) {

	if (fd == NULL) {
		return -1;
	}

	close(*fd); /* Close the Serial port */

	return 0;
}

/**
 * @brief write data to serial port
 * @param[in]
 * @return error status
 */
int serial_write(int *fd, char * str) {

	int descriptor;
	char *ptr = str;
	int bytes_written = 0;

	if (fd == NULL) {
		return -1;
	}

	descriptor = *fd;

	/* use write() to send data to port      */
	bytes_written = write(descriptor, /* "fd" - file descriptor pointing to the opened serial port */
	                             ptr, /* "str"- address of the buffer containing data              */
	                      sizeof(ptr) /* "size" - the data size                                    */
	);

	printf("[serial] (%d) bytes written \r\n", bytes_written);

	return 0;
}

/**
 * @brief
 * @param[in] pointer to file descriptor
 * @param[in] pointer rx buffer
 * @return error status
 */
int serial_read(int *fd, char * ptr) {
	char buffer[SERIAL_RX_BUFFER_SIZE];

	if (fd == NULL) {
		return -1;
	}

	memset(buffer, 0, sizeof(buffer));

	int n = read(*fd, buffer, sizeof(buffer));

	if (n < 0) {
		fputs("[serial] read failed!\n", stderr);
	} else {
		if (ptr) {
			memcpy(ptr, buffer, strlen(buffer));
		}

		printf(" %s ", buffer);
	}

	return 0;
}

