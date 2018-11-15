/**
 * @file logger.c
 * @brief This is the logger source file.
 * $Id: $
 **/

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#include <stdio.h>
#include "logger.h"

//******************************** DEFINES ***********************************//
//============================================================================//
#define KNRM    "\x1B[00m"
#define KRED    "\x1B[31m"
#define KGRN    "\x1B[32m"
#define KYEL    "\x1B[33m"
#define KBLU    "\x1B[34m"
#define KMAG    "\x1B[35m"
#define KCYN    "\x1B[36m"
#define KWHT    "\x1B[37m"

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

void log_debug(char * msg) {
	printf("%s%s%s", KWHT, msg, KNRM);
}

void log_info(char * msg) {
	printf("%s%s%s", KBLU, msg, KNRM);
}

void log_warning(char * msg) {
	printf("%s%s%s", KYEL, msg, KNRM);
}

void log_error(char * msg) {
	printf("%s%s%s", KRED, msg, KNRM);
}

void log_color(enum log_colors color, char * msg) {
	char * selection = NULL;

	switch (color) {
	case log_red:
		selection = KRED;
		break;
	case log_green:
		selection = KGRN;
		break;
	case log_yellow:
		selection = KYEL;
		break;
	case log_blue:
		selection = KBLU;
		break;
	case log_magenta:
		selection = KMAG;
		break;
	case log_cyan:
		selection = KCYN;
		break;
	case log_white:
		selection = KWHT;
		break;
	default:
		selection = KNRM;
		break;
	}

	printf("%s%s%s", selection, msg, KNRM);
}
