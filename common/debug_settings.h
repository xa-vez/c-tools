/**
 * @file debug_settings.h
 * @brief debug_settings header file
 * $Id: $
 **/
#ifndef _DEBUG_SETTINGS_H_
#define _DEBUG_SETTINGS_H_

//****************************** DEPENDENCIES ********************************//
//============================================================================//

//******************************** DEFINES ***********************************//
//============================================================================//

//Trace color definitions
#define TRACE_NORMAL  "\x1B[00m"
#define TRACE_RED     "\x1B[31m"
#define TRACE_GREEN   "\x1B[32m"
#define TRACE_YELLOW  "\x1B[33m"
#define TRACE_BLUE    "\x1B[34m"
#define TRACE_MAGENTA "\x1B[35m"
#define TRACE_CYAN    "\x1B[36m"
#define TRACE_WHITE   "\x1B[37m"

//Trace level definitions
#define TRACE_LEVEL_OFF      0
#define TRACE_LEVEL_FATAL    1
#define TRACE_LEVEL_ERROR    2
#define TRACE_LEVEL_WARNING  3
#define TRACE_LEVEL_INFO     4
#define TRACE_LEVEL_DEBUG    5


#define TRACE_LEVEL_SERIAL   TRACE_LEVEL_DEBUG
#define TRACE_COLOR_SERIAL   TRACE_BLUE

#define TRACE_LEVEL_MAIN     TRACE_LEVEL_DEBUG
#define TRACE_COLOR_MAIN     TRACE_GREEN

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

#endif
