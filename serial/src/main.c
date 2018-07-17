#include <stdio.h>   /* Standard Input Output Library       */
#include <unistd.h>  /* UNIX Standard Definitions           */
#include "serial.h"

/**
 * @brief main entry point
 * @return error status
 */
int main(void) {

#ifdef SERIAL_TEST_INCLUDED
	serial_test();
#endif

	return 0;
}
