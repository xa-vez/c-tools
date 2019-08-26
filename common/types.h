/**
 * @file types.h
 * @brief Compiler specific definitions
 **/

#ifndef __TYPES_H__
#define __TYPES_H__

//Dependencies
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

/**  */
typedef union
{
	unsigned char byte;
	struct bitfield
	{
		unsigned char bit00 :1;
		unsigned char bit01 :1;
		unsigned char bit02 :1;
		unsigned char bit03 :1;
		unsigned char bit04 :1;
		unsigned char bit05 :1;
		unsigned char bit06 :1;
		unsigned char bit07 :1;
	} bits;
} bitfield8_t;

//Types
typedef unsigned char uchar_t;
typedef char char_t;
typedef unsigned short ushort_t;
typedef short short_t;
typedef signed int int_t;
typedef unsigned int uint_t;

typedef uint32_t systime_t;

#if !defined(R_TYPEDEFS_H) && !defined(USE_CHIBIOS)
typedef int bool_t;
#endif

#if defined(_WIN32)
#define PRIuSIZE "Iu"
#define PRIuTIME "lu"
#elif defined(__XC32)
#define PRIuSIZE "u"
#define PRIuTIME "u"
#elif defined(__CWCC__)
#define PRIu8 "u"
#define PRIu16 "u"
#define PRIu32 "u"
#define PRIx8 "x"
#define PRIx16 "x"
#define PRIx32 "x"
#define PRIX8 "X"
#define PRIX16 "X"
#define PRIX32 "X"
#define PRIuSIZE "u"
#define PRIuTIME "u"
#else
#define PRIuSIZE "u"
#define PRIuTIME "lu"
#endif

#if defined(__CC_ARM)
#undef PRIu8
#define PRIu8 "u"
#undef PRIu16
#define PRIu16 "u"
#endif

//CodeWarrior compiler?
#if defined(__CWCC__)
typedef uint32_t time_t;
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strtok_r(char *s, const char *delim, char **last);
//TI ARM C compiler?
#elif defined(__TI_ARM__)
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strtok_r(char *s, const char *delim, char **last);
#endif

//Microchip XC32 compiler?
#if defined(__XC32)
#define sprintf _sprintf
int sprintf(char * str, const char * format, ...);
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strtok_r(char *s, const char *delim, char **last);
#endif

//GCC compiler?
#if defined(__GNUC__)
#undef __start_packed
#define __start_packed
#undef __end_packed
#define __end_packed __attribute__((__packed__))
//Keil MDK-ARM compiler?
#elif defined(__CC_ARM)
#pragma anon_unions
#undef __start_packed
#define __start_packed __packed
#undef __end_packed
#define __end_packed
//IAR C compiler?
#elif defined(__IAR_SYSTEMS_ICC__)
#undef __start_packed
#define __start_packed __packed
#undef __end_packed
#define __end_packed
//CodeWarrior compiler?
#elif defined(__CWCC__)
#undef __start_packed
#define __start_packed
#undef __end_packed
#define __end_packed
//TI ARM C compiler?
#elif defined(__TI_ARM__)
#undef __start_packed
#define __start_packed
#undef __end_packed
#define __end_packed __attribute__((__packed__))
//Win32 compiler?
#elif defined(_WIN32)
#undef interface
#undef __start_packed
#define __start_packed
#undef __end_packed
#define __end_packed
#endif


//Compilation flags used to enable/disable features
#define ENABLED  1
#define DISABLED 0

#define PTR_OFFSET(addr, offset) ((void *) ((uint8_t *) (addr) + (offset)))

#define timeCompare(t1, t2) ((int32_t) ((t1) - (t2)))

//Miscellaneous macros
#ifndef FALSE
   #define FALSE 0
#endif

#ifndef TRUE
   #define TRUE 1
#endif

#ifndef LSB
   #define LSB(x) ((x) & 0xFF)
#endif

#ifndef MSB
   #define MSB(x) (((x) >> 8) & 0xFF)
#endif

#ifndef MIN
   #define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
   #define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef arraysize
   #define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif

#endif
