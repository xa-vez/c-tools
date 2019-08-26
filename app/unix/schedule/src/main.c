/**
 * @file main.c
 * @brief This is the source file.
 * $Id: $
 **/


//****************************** DEPENDENCIES ********************************//
//============================================================================//
#define TRACE_LEVEL TRACE_LEVEL_MAIN
#define TRACE_COLOR TRACE_COLOR_MAIN

#include <unistd.h>
#include <stdio.h>
#include "date-time.h"
#include "debug_settings.h"
#include "debug.h"
#include "main.h"
#include "schedule.h"

//******************************** DEFINES ***********************************//
//============================================================================//

//******************************** TYPEDEFS **********************************//
//============================================================================//

//********************************* ENUMS ************************************//
//============================================================================//

//***************************  PRIVATE VARIABLES *****************************//
//============================================================================//

//***************************  PUBLIC VARIABLES ******************************//
//============================================================================//

//***************************  PRIVATE FUNCTIONS *****************************//
//============================================================================//

//***************************  PUBLIC FUNCTIONS ******************************//
//============================================================================//
int_t app_callback_1day(void * param)
{
	struct alarm_t alarm;

	alarm = * (struct alarm_t * ) param;

	TRACE_INFO("[DAY] %02d:%02d:%02d \r\n", alarm.hours, alarm.minutes, alarm.seconds );

	return 0;
}

int_t app_callback_1hour(void * param)
{
	struct alarm_t alarm;

	alarm = * (struct alarm_t * ) param;

	TRACE_INFO("[HRS] %02d:%02d:%02d \r\n", alarm.hours, alarm.minutes, alarm.seconds );

	return 0;
}

int_t app_callback_1min(void * param)
{
	struct alarm_t alarm;

	alarm = * (struct alarm_t * ) param;

	TRACE_INFO("[MIN] %02d:%02d:%02d \r\n", alarm.hours, alarm.minutes, alarm.seconds );

	return 0;
}

int_t app_callback_10sec(void * param)
{
	struct alarm_t alarm;

	alarm = * (struct alarm_t * ) param;

	TRACE_INFO("[SEC] %02d:%02d:%02d \r\n", alarm.hours, alarm.minutes, alarm.seconds );

	return 0;
}


/**
 * @brief main entry point
 **/
int_t main(void)
{
	struct alarm_t  app_clock = {23,59,00} ;
	DateTime date;

	//Start-up message
	TRACE_INFO("\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("****** Application Demo *****\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("Copyright: 2010-2019\r\n");
	TRACE_INFO("Compiled: %s %s\r\n", __DATE__, __TIME__);
	TRACE_INFO("Target: Generic\r\n");
	TRACE_INFO("\r\n");

	getCurrentDate(&date);
	app_clock.hours = date.hours;
	app_clock.minutes = date.minutes;
	app_clock.seconds = date.seconds;
	TRACE_INFO("[INIT] %02d:%02d:%02d \r\n", date.hours, date.minutes, date.seconds );

	time_t time;
	time = getCurrentUnixTime();
	TRACE_INFO("[INIT] %s\r\n", covertCurrentUnixTimeToString(time, NULL));

	sch_set_clock(&app_clock);

	//for (uint_t i = 0; i < 600; i++)
	for(;;)
	{
		sleep(1);
		sch_task();
	}

	return 0;
}
