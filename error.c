#include <stdio.h>
#include "error.h"

// Static function modifier -> private access in this file only.

void myPrinter(char * toPrint, uint8_t stream)
{
	/* 'char * toPrint' is the string to be printed
		'stream' is the place to be printed to
	
	*/
	switch(stream)
	{
		case TO_STDOUT: // print to stdout.
			fprintf(stdout, "%s", toPrint);
			break;
		case TO_STDERR: // print to stderr.
			fprintf(stderr, "%s", toPrint);
			break;
		case TO_ERR_LOG: // print to the error log file.
			FILE *file;
			file = fopen(ErrorLog_File, "a");
			fprintf(stderr, "%s", toPrint);
			break;
	}
}

char ErrorLog_File[]="errors/error log.txt"
char Program_Data_File[]="errors/Program Data.txt"

static char* getError_As_String(uint8_t value, uint8_t value_type)
{
	switch((value_type) ? errorType:error_ID)
	{
		case ER_INTERNAL:
			return "ER_INTERNAL";
		case ER_bad_execution:
			return "ER_bad_execution";
		case ER_malloc_failure:
			return "ER_malloc_failure";
		case ER_realloc_failure:
			return "ER_realloc_failure";
		case ER_free_failure:
			return "ER_free_failure";



		case ER_INPUT:
		case ER_FILES:
		case ER_AUTH_FAILURE:
		
	}
}

do{
	FILE *file; // Declaring a file pointer variable before assigning a pointer to it
	file = fopen(names, "r"); break;
	error = fileErrorChecker(file);
}while(error);

uint8_t fileErrorChecker(FILE *fileptr)
{
	// Takes in a file pointer and checks if it is null
	if(fileptr == NULL)
		if(errorHandler(2.0)) // File missing error
			return 1;
	return 0; // Return 0 for no errors
}

// Check out perror frm stdlib to print errors out automatically

static void errorlog(uint8_t errorType, uint8_t error_ID)
{
	FILE *file;
	file = fopen(ErrorLog_File, "a"); // Appends to error log. Creates file when unavailble.
	fileErrorChecker()

	// Print timestamp
	time_t TimeStamp = time(NULL);
	fprintf(file, ctime(&TimeStamp));

	// Print out the errorType and error_ID as strings into the log file.
	fprintf(file, "%s %s", getError_As_String(errorType, 1), getError_As_String(error_ID, 0));


	// print additional remarks

	fclose(file); // Close the file.

	// return either success or failure. Or maybe set a success/fail BitField
}

uint8_t errorHandler(uint8_t errorType, uint8_t error_ID)
{
	/*	Input parameter:

		- errorType:
		ER_INTERNAL -> internal errors like unexpected excecution or invalid function parameters.
		ER_INPUT -> for input errors, where wrong input type / format is being read.
		ER_FILES -> for file errors, anything to do with file I/O

		- error_ID:
		(0) unexpected internal excecution
		(1) passing of wrong values between functions
		(2) unable to allocate memory from heap for whatever reasons
		(3) unable to free memory from heap or dangling pointer detected
		(4) 
		--
		(10) Wrong input / Invalid input (General Error) Let user try again
		(11) Wrong input type
		(12) Wrong input format
		--
		(20) when FILE pointer is of NULL value, missing file, file unable to be read
		(21) File stored in wrong format / edited wrongly
	*/
	int errorHandlerInput, repeatErrorCount = 0;



	/*Write error to error log first*/

	errorlog(errorType, error_ID);
	// if above successful, continue program, else set ER_INTERNAL error and kill program


	switch(errorType)
	{
		case ER_INTERNAL: // Internal errors
			do{

				printf("\tError! Unexpected internal excecution.\n\tInform developer if error persists.\n");
				sectioner(2); getchar(); sectioner(3); // UI layout code.
				switch(error_ID)
				{
					case ER_bad_execution:
						errorLog("ER_INTERNAL -> ER_bad_execution"); // Work on this
						break;
					case ER_malloc_failure:
						// printf("\tError! Internal error encountered -> wrong values passed in program.\n");
						break;
					case ER_realloc_failure:
						printf("\tDetails: Unable to allocate memory to perform operations!\n");
						printf("\tLikely due to limited RAM avail.\n\tClose apps to free up ram and try again.\n");
						break;
					case ER_free_failure:
						printf("\tDetails: Unable to free memory from heap(RAM).\n");
						break;
					default:
						errorHandler();
				} // End of switch(error_ID)




				printf("\tEnter 'retry' to try excecution again\n");
				printf("\tEnter 'home' to go back to the MainMenu\n");
				printf("\tEnter 'exit' to quit and exit program now.\n");


				pInput(); fflush(stdin);
				char * UserInput = getString();
				while(sizeof(*UserInput) > 6){ // Input longer than longest keyword 'retry'
					if(repeatErrorCount > 2)
						exit(EXIT_FAILURE); // Quit program when invalid input entered more than twice.
					printf("Invalid input! Try again!\n");
					++repeatErrorCount; // Increment error count tracker.
					UserInput = getString(); // Read in new input.
				}





				if(errorHandlerInput < 0 || errorHandlerInput > 2){
					repeatErrorCount++;
					printf("\tOption entered is still invalid please try again.\n");
				}
				else
					break;




			}while(!GLOBAL_FLAGS_METHODS(ERROR, READ_BIT)); // Exit when error bit is cleared.








				if((!(repeatErrorCount % 2) && repeatErrorCount) || !repeatErrorCount)
				{
					if(!(repeatErrorCount % 2) && repeatErrorCount)
						clear_screen(1, 3);
					else
						clear_screen(0, 3);
					sectioner(4);
					sectioner(2);
				}
				sectioner(3);

			// return errorHandlerInput;
			break;



		case ER_INPUT: // input errors
			do
			{
				if((!(repeatErrorCount % 2) && repeatErrorCount) || !repeatErrorCount)
				{
					if(!(repeatErrorCount % 2) && repeatErrorCount)
						clear_screen(1, 3);
					else
						clear_screen(0, 3);
					sectioner(4);
					switch(error_ID)
					{
						case 10:
							printf("\tError! Invalid input detected.\n");
							break;
						case 11:
							printf("\tError! Invalid input type detected.\n");
							break;
						case 12:
							printf("\tError! Invalid input format detected.\n");
							break;
					} // End of switch(error_ID)
					sectioner(2);
				}
				sectioner(3);
				printf("\tEnter:\n\t(1) To try again\n");
				printf("\t(2) To go back to MainMenu\n");
				printf("\t(0) To exit program.\n");
				pInput(); fflush(stdin);
				scanf("%d", &errorHandlerInput);
				if(errorHandlerInput < 0 || errorHandlerInput > 2){
					repeatErrorCount++;
					printf("\tOption entered is still invalid please try again.\n");
				}
				else
					break;
			}while(repeatErrorCount);
			return errorHandlerInput;
			break;
		case ER_AUTH_FAILURE:

			break;
		case 2: // All errors regarding file I/O
			do
			{
				if((!(repeatErrorCount % 2) && repeatErrorCount) || !repeatErrorCount)
				{
					if(!(repeatErrorCount % 2) && repeatErrorCount)
						clear_screen(1, 3);
					else
						clear_screen(0, 3);
					sectioner(4);
					switch(error_ID)
					{
						case 20:
							printf("\tError! File specified does not exist in the specified location!\n");
							printf("\tCheck if file has been deleted before accessing file or running app again.\n");
							break;
						case 21:
							printf("\tError! File specified is written in the wrong format, or has been edited wrongly!\n");
							printf("\tCheck file format before accessing file or running app again.\n");
							break;
					} // End of switch(error_ID)
					sectioner(2);
				}
				sectioner(3);
				printf("\tEnter:\n\t(1) Try excecution again. (Check file first)\n");
				printf("\t(0) Exit program.\n");
				pInput(); fflush(stdin);
				scanf("%d", &errorHandlerInput);
				if(errorHandlerInput < 0 || errorHandlerInput > 1){
					repeatErrorCount++;
					printf("\tOption entered is still invalid please try again.\n");
				}
				else
					break;
			}while(repeatErrorCount);
			return errorHandlerInput;
		default:
			break;
	} // End of switch(errorType)
}