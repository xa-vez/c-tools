/**
 * @file main.c
 * @brief
 * $Id: $
 **/
#include <stdio.h>
#include "filegen.h"

/**
 * @brief main entry point
 * @param[in] argc
 * @param[in] argv
 * @return error status
 */
int main(int argc, char ** argv) {
	int error = 0;

	printf("filegen\n");

	if (argc != 2) {
		printf("Wrong number of arguments.\n");
		printf("Syntax is: %s module\n", argv[0]);
		error = 1;
	}

	printf("%s\n", argv[1]);

	return error;
}

