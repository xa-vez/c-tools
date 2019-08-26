/**
 * @file schedule.c
 * @brief This is the source file.
 * $Id: $
 **/

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#define TRACE_LEVEL TRACE_LEVEL_SCHEDULE
#define TRACE_COLOR TRACE_COLOR_SCHEDULE

#include <unistd.h>
#include <stdio.h>
#include "date-time.h"
#include "debug_settings.h"
#include "debug.h"

#include "schedule.h" 
//******************************** DEFINES ***********************************//
//============================================================================//

int_t sch_second(void * ctx);
int_t sch_minute(void * ctx);
int_t sch_hour(void * ctx);
int_t sch_day(void * ctx);

/** state structure */
struct state
{
	char_t * name;
	int_t period;
	int_t (* const handler)(void *);
	int_t (* const cb)(void *);
};

/** constructor for enumeration of application  states. */
#define SCH_STATE(a,b,c,d)  SCH_ ## c,
enum sch_states
{
	SCH_STATES SCH_STATE_CNT
};
#undef SCH_STATE

/** constructor array of function pointer to actions for each state (construct with a macro) */
#define SCH_STATE(a,b,c,d)  { a, b, sch_ ## c, d },
static struct state manager[SCH_STATE_CNT] =
{ SCH_STATES };
#undef SCH_STATE

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

/** alarm_clock structure */
static struct alarm_t alarm_clock = {
 .hours = 0,
 .minutes = 0,
 .seconds = 0 };

//***************************  PUBLIC VARIABLES ******************************//
//============================================================================//

//**************************  PRIVATE FUNCTIONS ******************************//
//============================================================================//

/**
 *
 */
int_t sch_second(void * param)
{
	struct state * ptr = (struct state *) param;
	static uchar_t counter = 0;

	counter++;
	if (ptr->period && alarm_clock.seconds % ptr->period == 0)
	{
		counter = 0;

		if (ptr->cb)
			ptr->cb((void*) &alarm_clock);
	}

	return 0;
}

/**
 *
 */
int_t sch_minute(void * param)
{
	struct state * ptr = (struct state *) param;
	static uchar_t counter = 0;

	counter++;
	if (ptr->period && alarm_clock.minutes % ptr->period == 0)
	{
		counter = 0;

		if (ptr->cb)
			ptr->cb((void*) &alarm_clock);
	}

	return 0;
}

/**
 *
 */
int_t sch_hour(void * param)
{
	struct state * ptr = (struct state *) param;
	static uchar_t counter = 0;

	counter++;
	if (ptr->period && alarm_clock.hours % ptr->period == 0)
	{
		counter = 0;

		if (ptr->cb)
			ptr->cb((void*) &alarm_clock);
	}

	return 0;
}

/**
 *
 */
int_t sch_day(void * param)
{
	struct state * ptr = (struct state *) param;
	static uchar_t counter = 0;

	counter++;
	if (ptr->period && ptr->period == counter)
	{
		counter = 0;

		if (ptr->cb)
			ptr->cb((void*) &alarm_clock);
	}

	return 0;
}

//***************************  PUBLIC FUNCTIONS ******************************//
//============================================================================//

/**
 * @brief This function sets the clock
 */
void sch_set_clock(struct alarm_t * clk)
{
	struct alarm_t * ptr = &alarm_clock;

	if (clk) {
		ptr->hours = clk->hours;
		ptr->minutes = clk->minutes;
		ptr->seconds = clk->seconds;
	}
}

/**
 * @brief This function gets the clock
 */
void sch_get_clock(struct alarm_t * clk)
{
	struct alarm_t * ptr = &alarm_clock;

	if (clk) {
		clk->hours = ptr->hours;
		clk->minutes = ptr->minutes;
		clk->seconds = ptr->seconds;
	}
}

/**
 * @brief This function needs to be called each second
 */
void sch_task(void)
{
	static struct alarm_t * clk = &alarm_clock;
	struct state * state;

	state = &manager[SCH_second];
	state->handler(state);
	clk->seconds++;

	if (clk->seconds == 60)
	{
		clk->seconds = 0;
		clk->minutes++;
		state = &manager[SCH_minute];
		state->handler(state);

		if (clk->minutes == 60)
		{
			clk->minutes = 0;
			clk->hours++;
			state = &manager[SCH_hour];
			state->handler(state);

			if (clk->hours == 24)
			{
				clk->hours = 0;
				state = &manager[SCH_day];
				state->handler(state);
			}
		}
	}

	//TRACE_INFO("[sch] %02d:%02d:%02d \r\n", clk->hours, clk->minutes, clk->seconds );

}
