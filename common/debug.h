/**
 * @file trace_debug.h
 * @brief trace_debug header file
 * $Id: $
 **/
#ifndef _DEBUG_H_
#define _DEBUG_H_

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#include <stdio.h>
#include "date-time.h"

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

//Default trace level
#ifndef TRACE_LEVEL
#define TRACE_LEVEL TRACE_LEVEL_DEBUG
#warning "TRACE_LEVEL Missing for this module"
#endif

#ifndef TRACE_COLOR
#define TRACE_COLOR TRACE_NORMAL
#warning "TRACE_COLOR Missing for this module"
#endif

//Trace output redirection
#ifndef TRACE_PRINTF
#define TRACE_PRINTF(...) \
          do { \
            fprintf(stderr, "%s", TRACE_COLOR ); \
            fprintf(stderr, "[%s] ", covertCurrentUnixTimeToString( getCurrentUnixTime(),NULL) ); \
            fprintf(stderr, "[%s] ", __FILE__ ); \
            fprintf(stderr, __VA_ARGS__); \
            fprintf(stderr, "%s", TRACE_NORMAL ); \
          } while(0)

#endif

#ifndef TRACE_ARRAY
#define TRACE_ARRAY(p, a, n) \
          do { \
            fprintf(stderr, "%s", TRACE_COLOR ); \
            fprintf(stderr, "[%s] Display Array: \n", __FILE__ ); \
            DEBUG_DisplayBuffer(stderr, p, a, n); \
            fprintf(stderr, "%s", TRACE_NORMAL ); \
          } while(0)
#endif

//Debugging macros
#if (TRACE_LEVEL >= TRACE_LEVEL_FATAL)
#define TRACE_FATAL(...) TRACE_PRINTF(__VA_ARGS__)
#define TRACE_FATAL_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
#else
#define TRACE_FATAL(...)
#define TRACE_FATAL_ARRAY(p, a, n)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
#define TRACE_ERROR(...) TRACE_PRINTF(__VA_ARGS__)
#define TRACE_ERROR_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
#else
#define TRACE_ERROR(...)
#define TRACE_ERROR_ARRAY(p, a, n)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_WARNING)
#define TRACE_WARNING(...) TRACE_PRINTF(__VA_ARGS__)
#define TRACE_WARNING_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
#else
#define TRACE_WARNING(...)
#define TRACE_WARNING_ARRAY(p, a, n)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_INFO)
#define TRACE_INFO(...) TRACE_PRINTF(__VA_ARGS__)
#define TRACE_INFO_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
#else
#define TRACE_INFO(...)
#define TRACE_INFO_ARRAY(p, a, n)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
#define TRACE_DEBUG(...) TRACE_PRINTF(__VA_ARGS__)
#define TRACE_DEBUG_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
#else
#define TRACE_DEBUG(...)
#define TRACE_DEBUG_ARRAY(p, a, n)
#endif

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

void DEBUG_DisplayBuffer(FILE * stream, const char * buffer, int length,
		int indent);

void DEBUG_DisplayArray(FILE *stream, const char *prepend, const void *data,
		int length);

void DEBUG_mpiDump(FILE *stream, const char *prepend, const void *data);

void DEBUG_Init(void);

#endif
