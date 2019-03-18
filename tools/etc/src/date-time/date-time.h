/**
 * @file date_time.h
 * @brief This is the header file.
 * $Id: $
 **/

#ifndef __DATE_TIME_H__
#define __DATE_TIME_H__

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#include <time.h>
#include "types.h"

//******************************** DEFINES ***********************************//
//============================================================================//

//******************************** TYPEDEFS **********************************//
//============================================================================//

/**
 * @brief Date and time representation
 **/

typedef struct
{
   uint16_t year;
   uint8_t month;
   uint8_t day;
   uint8_t dayOfWeek;
   uint8_t hours;
   uint8_t minutes;
   uint8_t seconds;
   uint16_t milliseconds;
} DateTime;

//********************************* ENUMS ************************************//
//============================================================================//

//**************************** PUBLIC CONSTANTS ******************************//
//============================================================================//

//***************************  PUBLIC VARIABLES ******************************//
//============================================================================//

//***************************  PUBLIC FUNCTIONS ******************************//
//============================================================================//

//Date and time management
const char_t *formatSystemTime(systime_t time, char_t *str);
const char_t *formatDate(const DateTime *date, char_t *str);

void getCurrentDate(DateTime *date);
time_t getCurrentUnixTime(void);
char * covertCurrentUnixTimeToString(time_t t, char * output);

void convertUnixTimeToDate(time_t t, DateTime *date);
time_t convertDateToUnixTime(const DateTime *date);

int_t compareDateTime(const DateTime *date1, const DateTime *date2);

uint8_t computeDayOfWeek(uint16_t y, uint8_t m, uint8_t d);

char * DT_GetTime(void);



#endif // __DATE_TIME_H__
