/**
 * @file atcommands.h
 * @brief This is the header file.
 * $Id: $
 **/

#ifndef __ATCOMMANDS_H__
#define __ATCOMMANDS_H__

//****************************** DEPENDENCIES ********************************//
//============================================================================//
#include "../common/types.h"

//******************************** DEFINES ***********************************//
//============================================================================//
/** buffer */
struct buffer {

	char_t status;
	int_t size;
	char_t data[1500];
};

/** at command */
struct at_command {
	char_t * cmd;
	char_t * response;
	int_t timeout;
	int_t retry;
	int_t (* const handler)(void *);
};

/** List of application states. */
#define FSM_STATES                                      \
    FSM_STATE( "AT1\r\n", "OK",  1000,  1, state_one  ) \
    FSM_STATE( "AT2\r\n", NULL,  2000,  2, state_two  ) \
    FSM_STATE( "AT3\r\n", "OK",  3000,  3, state_three) \
	FSM_STATE( NULL,      NULL,  10000, 1, state_idle ) \

/** For enumeration of application  states. */
#define FSM_STATE(a,b,c,d,e)  FSM_ ## e,
enum fsm_states {
	FSM_STATES FSM_STATE_CNT
};
#undef FSM_STATE

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

#endif // __ATCOMMANDS_H__