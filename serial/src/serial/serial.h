/**
 * @file serial.h
 * @brief This is the header file.
 * $Id: $
 **/

#ifndef __SERIAL_H__
#define __SERIAL_H__

//****************************** DEPENDENCIES ********************************//
//============================================================================//

//******************************** DEFINES ***********************************//
//============================================================================//

/* Change /dev/ttyUSB0 to the one corresponding to your system */
//#define SERIAL_PORT "/dev/ttyUSB0"
#define SERIAL_PORT "/dev/ttyAMA0"
//#define SERIAL_PORT "/dev/ttyS19"

/* define the baudrate */
#define SERIAL_BAUDRATE  B115200

/* define the rx buffer size */
#define SERIAL_RX_BUFFER_SIZE 1500

/*  define test api */
#define SERIAL_TEST_INCLUDED

//******************************** TYPEDEFS **********************************//
//============================================================================//

//********************************* ENUMS ************************************//
//============================================================================//

//**************************** PUBLIC CONSTANTS ******************************//
//============================================================================//

//***************************  PUBLIC VARIABLES ******************************//
//============================================================================//

//***************************  PUBLIC FUNCTIONS ******************************//
//============================================================================//

#ifdef SERIAL_TEST_INCLUDED
int serial_test(void);
#endif

int serial_open(int *fd);
int serial_close(int *fd);
int serial_write(int *fd, char * str);
int serial_read(int *fd, char * str);

#endif // __SERIAL_H__
