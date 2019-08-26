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
int_t app_callback_day(void * param)
{
	struct alarm_t alarm;

	alarm = * (struct alarm_t * ) param;

	TRACE_INFO("[DAY] %02d:%02d:%02d \r\n", alarm.hours, alarm.minutes, alarm.seconds );

	return 0;
}

int_t app_callback_hour(void * param)
{
	struct alarm_t alarm;

	alarm = * (struct alarm_t * ) param;

	TRACE_INFO("[HRS] %02d:%02d:%02d \r\n", alarm.hours, alarm.minutes, alarm.seconds );

	return 0;
}

int_t app_callback_min(void * param)
{
	struct alarm_t alarm;

	alarm = * (struct alarm_t * ) param;

	TRACE_INFO("[MIN] %02d:%02d:%02d \r\n", alarm.hours, alarm.minutes, alarm.seconds );

	return 0;
}

int_t app_callback_sec(void * param)
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
	struct alarm_t  app_clock = {23,0,0};

	//Start-up message
	TRACE_INFO("\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("****** Application Demo *****\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("Copyright: 2010-2019\r\n");
	TRACE_INFO("Compiled: %s %s\r\n", __DATE__, __TIME__);
	TRACE_INFO("Target: Generic\r\n");
	TRACE_INFO("\r\n");

	//
	time_t time;
	time = getCurrentUnixTime();
	TRACE_INFO("[INIT] %s\r\n", covertCurrentUnixTimeToString(time, NULL));

	{
		DateTime date;
		getCurrentDate(&date);
		app_clock.hours = date.hours;
		app_clock.minutes = date.minutes;
		app_clock.seconds = date.seconds;

		sch_set_clock(&app_clock);
		TRACE_INFO("[INIT] %02d:%02d:%02d \r\n", app_clock.hours, app_clock.minutes, app_clock.seconds );
	}

	//for (uint_t i = 0; i < 600; i++)
	for(;;)
	{
		sch_task();
		sleep(1);
	}

	return 0;
}
