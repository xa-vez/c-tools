/**
 * @file main
 * @brief  test
 * $Id: $
 **/
#include <stdio.h>
#include "logger.h"
#include "serial.h"


/**
 * @brief main entry point
 * @return true
 **/
int main(void) {

	printf("Hello World\n");

#ifdef LOG_TEST_INCLUDED
	log_debug("hello world\n");
	log_info("hello world\n");
	log_warning("hello world\n");
	log_error("hello world\n");
    log_color(log_cyan, "hello world\n");
#endif

#ifdef SERIAL_TEST_INCLUDED
	serial_test();
#endif

	return 0;
}
