#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // Used for standard fixed width Data Types definition e.g. uint8_t is 8bit
#include "global_flags.h"

static void init_Personal_Finance(int argc, char**argv)
{
	// Static access specifier only accessible from this file.
	// Input parameter is the exact same as main function.

	// Startsup by reading current date and time and data associated with the date

	// Parse ProgramArguements
	if(argc > 1)
	{
		for(uint8_t i = 0; i < number_of_users; i++)
			if(strcmp(argv[1], Usernames[i]))
				CURRENT_User = Usernames[i];
	}

	// Initialize all flags, memory and stuff
	GLOBAL_FLAGS_METHODS(ALL_FLAGS, CLEAR_BIT); // GLOBAL_FLAGS will reset at startup.
	Authenticate(LOGIN); // Set Auth bit to 0 before calling this function

	return GLOBAL_FLAGS_METHODS(AUTHENTICATION, READ_BIT) ? SUCCESS : FAILURE; // Using macro LOGIN.
}

int main(int argc, char**argv)
{
	init_Personal_Finance(argc, **argv); // Initialization function of Program.
	do
	{
		menu(PROGRAM_CURRENT_LOCATION);
		Input_Processor();
		execute_request();
	}while(!GLOBAL_FLAGS_METHODS(EXIT_PROGRAM, READ_BIT)); // Checking if EXIT_PROGRAM flag has been Set.


	// Program cleanup / saving data / exit program
	
	// Print a program ended and all cleaned up msg. Call all the strings from files. so the program will be smaller
	// as the program will only contain all the logic and stuff but not the "data".
	exit(EXIT_SUCCESS);
}

void execute_request()
{
	GLOBAL_FLAGS_METHODS( , READ_BIT); // Determines course of action based on input.

	switch(ACTION_ID)
	{
		case View_Log:
		case New_Log:
		case Del_Log:
		case Edit_Log:

		case View_Sum:
	}
}

/*	Change Bit, Location Bit.

	Everytime change Bit is set, all functions who read it pop back all the way to main.
	Main will clear the change bit and read location Bit
	Jump to location and call parser again

*/