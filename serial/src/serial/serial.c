
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
#include <string.h>  /* String                              */
#include "serial.h"  /* The module                          */

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


/* Change /dev/ttyUSB0 to the one corresponding to your system */
//#define SERIAL_PORT "/dev/ttyUSB0"
#define SERIAL_PORT "/dev/ttyS21"

/* define the baudrate */
#define SERIAL_BAUDRATE  B115200

int fd;/*File Descriptor*/

/**
 *
 */
int serial_open(int * fd) {

	int descriptor;

	printf("+----------------------------------+\r\n");
	printf("|        Serial Port Write         |\r\n");
	printf("+----------------------------------+\r\n");

	if (fd == NULL)
		return -1;

	descriptor = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
	/* O_RDWR Read/Write access to serial port           */
	/* O_NOCTTY - No terminal will control the process   */
	/* O_NDELAY -Non Blocking Mode,Does not care about-  */
	/* -the status of DCD line,Open() returns immediatly */

	if (descriptor == -1) { /* Error Checking */
		printf("Error opening %s \r\n", SERIAL_PORT);
	} else {
		printf("%s Opened Successfully\r\n", SERIAL_PORT);
	}

	/*** Setting the Attributes of the serial port using termios structure ****/

	struct termios SerialPortSettings; /* Create the structure                          */

	tcgetattr(descriptor, &SerialPortSettings); /* Get the current attributes of the Serial port */

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
		printf("ERROR in Setting attributes\r\n");
	} else {
		printf("BaudRate (%d) StopBits = 1 Parity   = non\r\n",
		SERIAL_BAUDRATE);
	}

	*fd = descriptor;

	return 0;
}

/**
 *
 */
int serial_close(int * fd) {

	if (fd == NULL) {
		return -1;
	}

	close(*fd); /* Close the Serial port */

	return 0;
}

/**
 *
 */
int serial_write(int *fd) {

	int descriptor;
	/*-------------
	 ------------------ Write data to serial port -----------------------------*/

	char write_buffer[] = "AT+CWLAP\r\n"; /* Buffer containing characters to write into port	     */
	int bytes_written = 0; /* Value for storing the number of bytes written to the port */

	if (fd == NULL)
		return -1;

	descriptor = *fd;

	bytes_written = write(descriptor, write_buffer, sizeof(write_buffer));/* use write() to send data to port                                            */
	/* "fd"                   - file descriptor pointing to the opened serial port */
	/*	"write_buffer"         - address of the buffer containing data	            */
	/* "sizeof(write_buffer)" - No of bytes to write                               */
	printf("+----------------------------------+\r\n");
	printf("%s written to %s\r\n", write_buffer, SERIAL_PORT);
	printf("%d Bytes written to %s\r\n", bytes_written, SERIAL_PORT);
	printf("+----------------------------------+\r\n");

	return 0;
}

/**
 *
 */
int serial_read(int *fd) {
	char buffer[1000];

	if (fd == NULL)
		return -1;

	memset(buffer, 0, sizeof(buffer));

	int n = read(*fd, buffer, sizeof(buffer));
	if (n < 0)
		fputs("read failed!\n", stderr);

	printf(" %s ", buffer);

	return 0;
}

