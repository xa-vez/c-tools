#include <stdio.h>
#include <unistd.h>  /* UNIX Standard Definitions           */
#include "serial.h"

/**
 *
 */
int main(void) {
	int fd;
	int error;

	error = serial_open(&fd);
	if (error)
		printf("[SERIAL] Error opening port\r\n");

	error = serial_write(&fd);
	if (error)
		printf("[SERIAL] Error writing port\r\n");

	sleep(5);

	error = serial_read(&fd);
	if (error)
		printf("[SERIAL] Error reading port\r\n");

	error = serial_close(&fd);

	if (error)
		printf("[SERIAL] Error closing port\r\n");

	return 0;
}
