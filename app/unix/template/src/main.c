/**
 * @file main.c
 * @brief This is the source file.
 * $Id: $
 **/


//****************************** DEPENDENCIES ********************************//
//============================================================================//
#define TRACE_LEVEL TRACE_LEVEL_MAIN
#define TRACE_COLOR TRACE_COLOR_MAIN

#include <stdio.h>
#include "debug_settings.h"
#include "debug.h"
#include "main.h"

//******************************** DEFINES ***********************************//
//============================================================================//

int_t fsm_state_one(void *);
int_t fsm_state_two(void *);
int_t fsm_state_three(void *);
int_t fsm_state_idle(void *);

/** constructor for enumeration of application  states. */
#define FSM_STATE(a,b,c,d,e)  FSM_ ## e,
enum fsm_states {
	FSM_STATES FSM_STATE_CNT
};
#undef FSM_STATE

/** constructor array of function pointer to actions for each state (construct with a macro) */
#define FSM_STATE(a, b, c, d, e)  { a, b, c, d, fsm_ ## e },
static struct at_command manager[FSM_STATE_CNT] = { FSM_STATES };
#undef FSM_STATE

/** constructor array of function pointer to actions for each state (construct with a macro) */
#define FSM_STATE(a, b, c, d, e)  fsm_ ## e,
 int_t ( * fsm[])(void*) =	{ FSM_STATES };
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

int_t fsm_state_one(void * ctx) {
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 1:%s %d(ms)\r\n", param->cmd, param->timeout);
	return 1;
}

int_t fsm_state_two(void * ctx) {
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 2 %s %d(ms)\r\n", param->cmd, param->timeout);
	return 2;
}

int_t fsm_state_three(void * ctx) {
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 3 %s\r\n", param->cmd);
	return 3;
}

int_t fsm_state_idle(void * ctx) {
	//struct at_command * param = (struct at_command *)ctx;

	//TRACE_INFO("state 3 %s\r\n", param->cmd);
	return 0;
}

/**
 * @brief send function
 * @param param
 * @return
 */
int_t send_cmd( struct at_command * param )
{
	if (param->cmd) {
		TRACE_INFO("send: %s \r\n", param->cmd);
	}

	return 0;
}

/**
 * @brief receive function
 * @param param
 * @return
 */
int_t wait_response( struct at_command * param )
{
	int_t wait = param->timeout;
	/*struct buffer rx;*/

	TRACE_INFO("wait %d(ms)\r\n", param->timeout);

	while (--wait);

//	if (rx.status && rx.size > 2 )
//		if( rx.data )


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
	TRACE_INFO("Copyright: 2010-2019\r\n");
	TRACE_INFO("Compiled: %s %s\r\n", __DATE__, __TIME__);
	TRACE_INFO("Target: Generic\r\n");
	TRACE_INFO("\r\n");

	int_t state = 0;
	struct at_command * command;

	for (uchar_t i = 0; i < FSM_STATE_CNT; i++)
	{
		/*****************************************************/

		//state = fsm[state](&manager[state]);
		/*****************************************************/
		command = &manager[state];

		// transmit message
		send_cmd(command);

		// rx queue message
		wait_response(command);

		//compute next state
		state = command->handler(command);

	}

	return 0;
}
