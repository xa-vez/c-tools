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

#define TRACE_LEVEL TRACE_LEVEL_SERIAL
#define TRACE_COLOR TRACE_COLOR_SERIAL
#include "debug.h"   /* debug module                        */
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

	TRACE_DEBUG("+----------------------------------+\r\n");
	TRACE_DEBUG("|       Opening Serial Port        |\r\n");
	TRACE_DEBUG("+----------------------------------+\r\n");

	/* O_RDWR Read/Write access to serial port           */
	/* O_NOCTTY - No terminal will control the process   */
	/* O_NDELAY -Non Blocking Mode,Does not care about-  */
	/* -the status of DCD line,Open() returns immediatly */
	descriptor = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);

	if (descriptor == -1) { /* Error Checking */
		TRACE_DEBUG("Error opening %s \r\n", SERIAL_PORT);
		return -1;
	} else {
		TRACE_DEBUG("%s Opened Successfully\r\n", SERIAL_PORT);
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

	/* setup for non-canonical mode */
	SerialPortSettings.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	SerialPortSettings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	SerialPortSettings.c_oflag &= ~OPOST;

	/* fetch bytes as they become available */
	SerialPortSettings.c_cc[VMIN] = 1;
	SerialPortSettings.c_cc[VTIME] = 1;

	if ((tcsetattr(descriptor, TCSANOW, &SerialPortSettings)) != 0) {/* Set the attributes to the termios structure*/
		TRACE_ERROR("Error in Setting attributes\r\n");
		return -1;
	} else {
		TRACE_DEBUG("(%d) BaudRate (1)StopBits (None)Parity \r\n", SERIAL_BAUDRATE);
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
	int size, bytes_written = 0;

	if (fd == NULL || str == NULL) {
		return -1;
	}

	descriptor = *fd;

	size = strlen(ptr);

	/* use write() to send data to port      */
	bytes_written = write(descriptor, /* "fd" - file descriptor pointing to the opened serial port */
	                             ptr, /* "str"- address of the buffer containing data              */
	                             size /* "size" - the data size                                    */
	);

	TRACE_DEBUG("(%d/%d) bytes written \r\n", size, bytes_written);

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
	int n, descriptor;

	if (fd == NULL) {
		return -1;
	}

	descriptor = *fd;

	memset(buffer, 0, sizeof(buffer));
	n = read(descriptor, buffer, sizeof(buffer)-1);

	if (n < 0) {
		TRACE_ERROR("read failed!\n");
	} else {
		TRACE_DEBUG("%d bytes readed\n",n );
		if (ptr) {
			buffer[n]= 0;
			memcpy(ptr, buffer, n+1);
		}
		TRACE_DEBUG("<<< %s", buffer);
	}

	return n;
}

