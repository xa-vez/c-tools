/**
 * @file main
 * @brief main source file
 * $Id: $
 **/
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TRACE_LEVEL TRACE_LEVEL_MAIN
#define TRACE_COLOR TRACE_COLOR_MAIN
#include "debug.h"
#include "serial.h"

#ifdef SERIAL_TEST_INCLUDED
/**
 * @brief serial test function
 * @return error status
 */
int serial_test(void)
{
	int fd, error;
	char buffer[1500];
	int count;

	do {

		error = serial_open(&fd);
		if (error) {
			TRACE_ERROR("Error opening port\r\n");
			break;
		}

		error = serial_write(&fd, (char *)"AT+CWLAP\r\n");
		if (error) {
			TRACE_ERROR("Error writing port\r\n");
			break;
		}

		sleep(3);

		do{

			memset(buffer, 0, sizeof(buffer));

			count = serial_read(&fd, buffer);

			if (count < 0) {
				error = count;
				TRACE_ERROR("Error reading port\r\n");
				break;
			}

			TRACE_DEBUG( "%s\n", buffer );
			//TRACE_ARRAY( buffer, strlen(buffer), 1);

			if( strstr(buffer, "OK" ) || strstr(buffer, "ERROR" ) )
				break;

		}while(1);

		error = serial_close(&fd);

		if (error) {
			TRACE_ERROR("Error closing port\r\n");
			break;
		}

	}while(0);

	return error;
}
#endif //SERIAL_TEST_INCLUDED

/**
 * @brief main entry point
 * @return true
 **/
int main(void) {
	int error = 0;

	TRACE_DEBUG("================================\n");
	TRACE_DEBUG("======= DEMO APPLICATION =======\n");
	TRACE_DEBUG("================================\n");
	TRACE_DEBUG("Copyright: 2010-2018 \n");
	TRACE_DEBUG("Compiled: %s %s \n", __DATE__, __TIME__);
	TRACE_DEBUG("Target: generic \n");

#ifdef SERIAL_TEST_INCLUDED
	error = serial_test();
#endif

	return error;
}
