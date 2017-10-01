/**
 * @file atcommands.c
 * @brief This is the source file.
 * $Id: $
 **/


//****************************** DEPENDENCIES ********************************//
//============================================================================//
#include <stdio.h>
#include "../common/debug.h"
#include "../common/types.h"
#include "atcommands.h"

//******************************** DEFINES ***********************************//
//============================================================================//

int_t fsm_state_one(void *);
int_t fsm_state_two(void *);
int_t fsm_state_three(void *);
int_t fsm_state_idle(void *);
int_t fsm_state_parser(void * ctx);

/** array of function pointer to actions for eaxh state (construct with a macro) */
//constructor macro
#define FSM_STATE(a, b, c, d, e)  {fsm_ ## a, b, c, d, e },
static struct at_command manager[FSM_STATE_CNT] = { FSM_STATES };
#undef FSM_STATE

#define FSM_STATE(a, b, c, d, e)  {fsm_ ## a },
 int ( * fsm[])(void*) =	{ FSM_STATES };
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


int_t fsm_state_one(void * ctx)
{
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 1:%s %d(ms)\r\n", param->cmd, param->timeout);
	return 1;
}

int_t fsm_state_two(void * ctx)
{
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 2 %s %d(ms)\r\n", param->cmd, param->timeout);
	return 2;
}

int_t fsm_state_three(void * ctx)
{
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 3 %s\r\n", param->cmd);
	return 3;
}

int_t fsm_state_idle(void * ctx)
{
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 3 %s\r\n", param->cmd);
	return 0;
}

int_t state_parser(void * ctx)
{

	return 2;
}


int_t send_cmd( struct at_command * param )
{
	TRACE_INFO("send: %s \r\n", param->cmd);
    return 0;
}

int_t wait_response( struct at_command * param )
{
	TRACE_INFO("wait %d(ms)\r\n", param->timeout);
    return 0;
}

/**
 * @brief App Initialization
 **/
int main(void)
{
	//Start-up message
	TRACE_INFO("\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("****** Application Demo *****\r\n");
	TRACE_INFO("*****************************\r\n");
	TRACE_INFO("Copyright: 2010-2016\r\n");
	TRACE_INFO("Compiled: %s %s\r\n", __DATE__, __TIME__);
	TRACE_INFO("Target: Generic\r\n");
	TRACE_INFO("\r\n");

    int_t state = 0;


    for(uchar_t i = 0; i < 6; i++)
    {
    	// transmit message
    	send_cmd( &manager[state]);

    	// queue message ?
    	wait_response( &manager[state]);


    	//

    	// compute next state
//    	if( manager[state].response != NULL )
//          state = fsm[state](&manager[state]);
//    	else
//          state = 0;
    	//state = manager[state].function();
    }

    return 0;
}
