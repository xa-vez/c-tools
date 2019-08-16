/**
 * @file fsm.c
 * @brief This is the source file.
 * $Id: $
 */

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#define TRACE_LEVEL TRACE_LEVEL_MAIN
#define TRACE_COLOR TRACE_COLOR_MAIN

#include <stdio.h>
#include "debug_settings.h"
#include "debug.h"
#include "commands.h"
#include "main.h"


#define STR(x)  STR2(x)
#define STR2(x) #x

//******************************** DEFINES ***********************************//
//============================================================================//
#define VERSION     1
#define REVISION    2
#define INDEX       3

//#define VERSION_SOFTxyz(x,y,z)    #x ## "." ## #y ## "." ## #z
#define VERSION_SOFTxyz(x,y)    STR(x) ## STR(y)
#define VERSION_SOFT(x,y)       VERSION_SOFTxyz(x,y)


const struct commands default_commands[] =
{ DEFAULT_COMMANDS };


//#define FSM_STATE(a, b, c)  void fsm_ ## b ## _(void);
//FSM_STATES
//#undef FSM_STATE

int fsm_state_one(void);
int fsm_state_two(void);
int fsm_state_three(void);

/** array of function pointer to actions for eaxh state (construct with a macro) */
//constructor macro
#define FSM_STATE(a, b, c)  {fsm_ ## b, fsm_ ## c, NULL },
static struct fsm_state Tasks[FSM_STATE_CNT] = { FSM_STATES };
#undef FSM_STATE

#define FSM_STATE(a, b, c)  {fsm_ ## b },
int (* manager[])(void) =	{ FSM_STATES };
#undef FSM_STATE


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

int fsm_state_one(void)
{
	TRACE_INFO("state 1\r\n");
	return 1;
}

int fsm_state_two(void)
{
	TRACE_INFO("state 2\r\n");
	return 2;
}

int fsm_state_three(void)
{
	TRACE_INFO("state 3\r\n");
	return 0;
}

/**
 * @brief App Initialization
 **/
int main(void)
{
    char version[] = { "VERSION_SOFT( VERSION,REVISION ) "};
    char version_test[] = { "00.00a" };
    //uchar_t unused;

    int state = 0;


	//Start-up message
	TRACE_INFO("\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("****** Application Demo *****\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("Copyright: 2010-2016\r\n");
	TRACE_INFO("Compiled: %s %s\r\n", __DATE__, __TIME__);
	TRACE_INFO("Target: Generic\r\n");
	TRACE_INFO("\r\n");


	for ( uchar_t i = 0; i < 3; i++)
	{
		TRACE_INFO("%c - %s\r\n", default_commands[i].option, default_commands[i].descriptor);
	}


    for(uchar_t i = 0; i < 9; i++)
    {
    	//Tasks[state].current();
    	state = manager[state]();
    }

    return 0;
}
