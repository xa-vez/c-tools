/**
 * @file debug.h
 * @brief Debugging tools
 * $Id $
 **/

#ifndef __DEBUG_H__
#define __DEBUG_H__


//Dependencies
#include <stdio.h>

//Trace level definitions
#define TRACE_LEVEL_OFF      0
#define TRACE_LEVEL_FATAL    1
#define TRACE_LEVEL_ERROR    2
#define TRACE_LEVEL_WARNING  3
#define TRACE_LEVEL_INFO     4
#define TRACE_LEVEL_DEBUG    5

//Default trace level
#ifndef TRACE_LEVEL
#define TRACE_LEVEL           TRACE_LEVEL_DEBUG
#endif

//Trace output redirection
#ifndef TRACE_PRINTF
#define TRACE_PRINTF(...)     fprintf(stderr, __VA_ARGS__)
#endif

#ifndef TRACE_ARRAY
#define TRACE_ARRAY(p, a, n)  DEBUG_DisplayArray(stderr, p, a, n)
#endif

#ifndef TRACE_MPI
#define TRACE_MPI(p, a)       DEBUG_mpiDump(stderr, p, a)
#endif

//Debugging macros
#if (TRACE_LEVEL >= TRACE_LEVEL_FATAL)
#define TRACE_FATAL(...)      TRACE_PRINTF(__VA_ARGS__)
#else
#define TRACE_FATAL(...)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
#define TRACE_ERROR(...)      TRACE_PRINTF(__VA_ARGS__)
#else
#define TRACE_ERROR(...)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_WARNING)
#define TRACE_WARNING(...)    TRACE_PRINTF(__VA_ARGS__)
#else
#define TRACE_WARNING(...)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_INFO)
#define TRACE_INFO(...)           TRACE_PRINTF(__VA_ARGS__)
#define TRACE_INFO_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
#define TRACE_INFO_NET_BUFFER(p, b, o, n)
#define TRACE_INFO_MPI(p, a) TRACE_MPI(p, a)
#else
#define TRACE_INFO(...)
#define TRACE_INFO_ARRAY(p, a, n)
#define TRACE_INFO_NET_BUFFER(p, b, o, n)
#define TRACE_INFO_MPI(p, a)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
#define TRACE_DEBUG(...) TRACE_PRINTF(__VA_ARGS__)
#define TRACE_DEBUG_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
#define TRACE_DEBUG_NET_BUFFER(p, b, o, n)
#define TRACE_DEBUG_MPI(p, a) TRACE_MPI(p, a)
#else
#define TRACE_DEBUG(...)
#define TRACE_DEBUG_ARRAY(p, a, n)
#define TRACE_DEBUG_NET_BUFFER(p, b, o, n)
#define TRACE_DEBUG_MPI(p, a)
#endif

//Debug related functions
void DEBUG_Init(void);

//Deprecated definitions
#define TRACE_LEVEL_NO_TRACE TRACE_LEVEL_OFF

#endif
