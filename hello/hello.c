/**
 * @file main.c
 * @brief prints the architecture size
 * $Id: $
 **/
#include <stdio.h>

/**
 * @brief main entry point
 * @return true
 **/
int main(void) {

	printf("size of char: %d\n", (int) sizeof(char));
	printf("size of short: %d\n", (int) sizeof(short));
	printf("size of int: %d\n", (int) sizeof(int));
	printf("size of long: %d\n", (int) sizeof(long));
	printf("size of double: %d\n", (int) sizeof(double));

	return 1;
}
