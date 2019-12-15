#include <stdint.h> // Used for standard fixed width Data Types definition e.g. uint8_t is 8bit
#include "global_flags.h"

#include <stdio.h>

/*	Try to do better by using structs with BitFields
	https://stackoverflow.com/questions/1725855/uint8-t-vs-unsigned-char
*/

uint8_t GLOBAL_FLAGS_METHODS(uint8_t FLAG_id, uint8_t action)
{
	// This function MUST be called with predefined macros as input.
	/*	Input parameter "action",
		CLEAR_BIT: Clear/Reset Bit to 0.
		SET_BIT: Set/Program Bit to 1.
		TOGGLE_BIT: Toggle Bit.
		READ_BIT: Return value corresponding to FLAG_id.

		Input parameter "FLAG_id",
		If ALL_FLAGS is used as FLAG_id, then return value will be GLOBAL_FLAGS.
		Else return value will be the latest value of that Bit.
	*/
	/*	Return value will be the action called for, other then Read,
 		where the value of the Bit will be returned instead.
	*/

	static uint8_t GLOBAL_FLAGS = 0;
	/*	GLOBAL_FLAGS variable is only directly accessible/modifiable by this function in this file.
		As a static variable, it retains its value even after it has gone out of scope.
		Initial Flag is reset for all Flag Bits.
	*/

	// (FLAG_id ^ 0) ? printf("No error with flag  ") : printf("Error with the damn FLAG_id\n");
	// Use above false condition to call internal error handler and stop running the funciton

	switch(action)
	{
		case CLEAR_BIT:
			GLOBAL_FLAGS &= ~FLAG_id; // Bitwise Assignment.
			return (FLAG_id ^ ALL_FLAGS) ? action : GLOBAL_FLAGS;
		case SET_BIT:
			GLOBAL_FLAGS |= FLAG_id; // Bitwise Assignment.
			return (FLAG_id ^ ALL_FLAGS) ? action : GLOBAL_FLAGS;
		case TOGGLE_BIT:
			GLOBAL_FLAGS ^= FLAG_id; // Bitwise Assignment.
			// No break/return to allow fall through to read Bit value.
		case READ_BIT:
			return (FLAG_id ^ ALL_FLAGS) ? ((GLOBAL_FLAGS & FLAG_id) ? TRUE : FALSE) : GLOBAL_FLAGS;
		default:
			// Internal Error Handler
			break;
	}// End of switch(action)
}


#undef EXIT_PROGRAM
#undef ERROR_BIT
#undef AUTHENTICATION

struct{		
	// Access modifier for struct?
	// Place this inside a function?
	// How to add methods into a struct? smth like all_flags, will trigger a function
	// that operates on all flags at the same time
	uint8_t EXIT_PROGRAM : 1;
	uint8_t ERROR_BIT : 1;
	uint8_t AUTHENTICATION : 1;
} global_flags;


struct{
	uint8_t program_location = 0;
	uint8_t program_starttime = 0;
	uint8_t program_runtime = 0;
	uint8_t total_error_encounted = 0; // Increment this everytime ERROR bit is set in global_flags
} PROGRAM_STATE;

void program_runtime_setter()
{
	time_t Current_Time = clock(); // Function used to get current system time.
	PROGRAM_STATE.program_runtime = difftime() // Give it PROGRAM_STATE.program_starttime & Current_Time
}

uint8_t GLOBAL_FLAGS_METHODS(uint8_t FLAG_id, uint8_t action)
{
	switch(action)
	{
		case CLEAR_BIT:
			global_flags.FLAG_id = 0;
			break;
		case SET_BIT:
			global_flags.FLAG_id = 1;
			break;
		case TOGGLE_BIT:
			~global_flags.FLAG_id;
			break;
		case READ_BIT:
			break;

		default:
			// errorHandler
	}
	return global_flags.FLAG_id; // All action will return the value of the flag
}

int main(void)
{

	return 0;
}




#ifdef action_pack
uint8_t ACTION_METHODS(uint8_t ACTION_id, uint8_t action)  // To fix / modify
{
	// This function MUST be called with predefined macros as input.
	/*	Input parameter "action",
		0: RESET_APP
		1: Set/Program Bit to 1.
		2: Return ACTION___ to function caller.

		Input parameter "ACTION_id",
		Allows the program to know what is the next action to be taken.
	*/
	// Return value will be the ACTION___ variable

	static uint8_t ACTION___ = 0;
	/*	ACTION___ variable is only directly accessible/modifiable by this function in this file.
		As a static variable, it retains its value even after it has gone out of scope.
	*/

	// (FLAG_id ^ 0) ? printf("No error with flag  ") : printf("Error with the damn FLAG_id\n");
	// Use above false condition to call internal error handler and stop running the funciton

	switch(action)
	{
		case RESET_APP:
			// ACTION___ = OGGINAL_ACTION?;
			break;
		case SET_ACTION:
			ACTION___ = ACTION_id;
			break;
		case READ_ACTION:
			break;
		default:
			// Internal Error Handler
			return NULL; // either do this or break to whatever to indicate error
			break; // Or maybe we can set error flag high
	}// End of switch(action)
	return ACTION___;
}
#endif


#define PUSH 0
#define POP 1
#define RESET_STACK 2

uint8_t PROGRAM_STACK_METHODS(uint8_t action)
{
	uint8_t PROGRAM_FLOW_STACK[3] = {0};
	/*	Stack is reset on startup, Stack is 3 layers deep --> should this be changeable
		Put the stak creation into a program init function
		For location stack, only certain functions / pages will be added. Reason is because say from
		main menu, you want to change a setting, so you need to do authentication.
		Once you do finnish authentication you can edit the settings,
		but after editing you want ot go back to the main menu and not back to the authentication page
		All functions other then main will be labelled as either "To stack", "Not to stack"
	*/

	/* 

	*/

	GLOBAL_FLAGS_METHODS(STACK_LOCATION, READ_BIT);
	// 1 FOR STACK, 0 FOR NO

	switch(action)
	{
		case PUSH:
			// PROGRAM_CURRENT_LOCATION --> stack
			break;
		case POP: // Pop location

		case RESET_STACK:
			// for(uint8_t i; i<STACK_COUNT; i++)
				// PROGRAM_FLOW_STACK[i] = 0; // Or null
			break;
		// default:
			// Internal error handler
	}

}


uint8_t ERROR_TYPE;

uint8_t CURRENT_USER;
/*	Defines who is signed in at the moment for functions
	to know whos logbook to access and edit
	0: Root User, access to all logbooks and settings
	1: User1, access only to User1 logbook and settings

	Call Authenticate() to change access privileges
*/

uint8_t SETTING_FLAGS_METHODS(uint8_t FLAG_id, uint8_t action)
{
	// This function MUST be called with predefined macros as input.
	/*	Input parameter "action",
		0: Clear/Reset Bit to 0.
		1: Set/Program Bit to 1.
		2: Toggle Bit.
		3: Read Bit corresponding to FLAG_id.

		Input parameter "FLAG_id",
		If ALL_FLAGS is used as FLAG_id, then return value will be GLOBAL_FLAGS.
		Else return value will be the latest value of that Bit.
	*/
	/*	Return value will be the action called for, other then Read,
 		where the value of the Bit will be returned instead.
	*/

	static uint8_t SETTING_FLAGS = 0;
	/*	SETTING_FLAGS variable is only accessible/modifiable by this function in this file.
		As a static variable, it retains its value even after it has gone out of scope.
		Initial Flag is reset for all Flag Bits.
	*/

	/*
		SETTINGS_FLAGS Defn:
		Bit 7: 
		Bit 6: 
		Bit 5:
		Bit 4:
		Bit 3:
		Bit 2:
		Bit 1:
		Bit 0:
	*/

	switch(action)
	{
		case CLEAR_BIT:
			SETTING_FLAGS &= ~FLAG_id; // Bitwise Assignment.
			return (FLAG_id ^ ALL_FLAGS) ? action : SETTING_FLAGS;
		case SET_BIT:
			SETTING_FLAGS |= FLAG_id; // Bitwise Assignment.
			return (FLAG_id ^ ALL_FLAGS) ? action : SETTING_FLAGS;
		case TOGGLE_BIT:
			SETTING_FLAGS ^= FLAG_id; // Bitwise Assignment.
			// No break/return for case 2 to allow fall through to case 3 to return Bit value.
		case READ_BIT:
			return (FLAG_id ^ ALL_FLAGS) ? ((SETTING_FLAGS & FLAG_id) ? TRUE : FALSE) : SETTING_FLAGS;
		default:
			// Internal Error Handler
			break;
	}// End of switch(action)
}















uint8_t Number_of_Program_Locations = 10; // Make this a fixed constant
uint8_t PROGRAM_CURRENT_LOCATION = 0; // Represents up to 255 different menu id.
/*	Global reference variable for navigating application.
	Inital value of 0 resets location to Main Menu.
	The first element PROGRAM_STACK[0] is the
	0: Authentication Site.
	1: Main_Menu.
	2: Settings Page.
	3: Help/Man Page.
	4: Error Page.
	5: New Log Entry / New Action Page.
	6: Edit Logs / Action Page.
	7: Log Viewer.
	8: 
	9:
	10:
	11:
	12:
	13:
	14:
	15:
	16:
	17:
	18:
	19:
	20:
*/

// ... Current_Date = ...; // make a function that runs in initialization stage to set this flag
// ... Current_Time = ...; // make a function that runs in initialization stage to set this flag