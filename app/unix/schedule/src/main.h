/**
 * @file main.h
 * @brief This is the header file.
 * $Id: $
 **/

#ifndef __MAIN_H__
#define __MAIN_H__

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#include "types.h"

//******************************** DEFINES ***********************************//
//============================================================================//




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
int_t app_callback_sec(void * param);
int_t app_callback_min(void * param);
int_t app_callback_hour(void * param);
int_t app_callback_day(void * param);

#endif // __MAIN_H__
