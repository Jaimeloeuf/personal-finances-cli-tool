#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <time.h> // This one should be included in the header file of the append_TimeStamp global func

void newLog();
void viewLog();
void editLog();

static char* get_file_name(uint8_t month) // Static function accessible only in this file.
{	// Function returns file name of the given month.
	if(month<1 || month>12){ // Check for input error.
		printf("Error\n"); // Call errorHandler.
		return NULL;
	}
	static const char* month_file_name[] = {"01","02","03","04","05","06","07","08","09","10","11","12"};
	// char pointer array is declared as static const to pervent creation n destruction during every scope change.
	static char str[7]; // To retain memory space for data even after leaving scope.
	strcpy(str, ""); // To reset/clear the array before assigning new string to it.
	strcat(str, month_file_name[--month]); // decrement since array starts at element 0.
	strcat(str, ".txt\0"); // File extension needed to open file with fopen().
	return str;
}

void append_TimeStamp(FILE * file) // Make this a globally accesible function
{
	time_t TimeStamp = time(NULL);
	fprintf(file, ctime(&TimeStamp));
}

void newLog()
{
	/*	Function Flow:
		-Go to dir for current year
		-read users input on Val/Amnt
		-read cat for the spending/expenditure or income
		-Open file for month
		-append data into the file
		-ask user if there is any remarks? let them know max only 100 or smth characters
		-append any remarks
		-close the file
	*/

	uint8_t month = 8; // Read current month from system time.
	FILE * file = fopen(get_file_name(month), "a");
	
	/*Append log*/
	append_TimeStamp(file);

}

void main(void)
{
	printf("The file_name passed from function is %s\n", get_file_name(7));
}