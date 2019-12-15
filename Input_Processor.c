#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
// #include "global_flags.h"

static char * getString(FILE* stream, size_t size)
{
	// Static access modifier to only allow functions in this file to call it.
	/*	The String that is read will be entirely stored in Heap Memory.
		A Null will be returned to function caller if HEAP is out of memory.

		Input Parameter:
		-'stream' determines where the function will get "string" from. It is usually stdin.
		-'size' is used as the initial arraysize and the realloc process happens in multiples
		  of the value. It must be bigger then 1. The bigger size is, the more ram used
		  but less compute power as lesser realloc and vice versa. 
	*/
	// sizeof(char) is 1, but still included for clarity.
	// The memory returned must be freed by the function caller ONLY!

	if(size < 1){
		// errorHandler for bad function parameter
	}

	char * input_string; // Pointer to input string
    size_t len = 0; // Variable to keep track length of input string
    input_string = realloc(NULL, sizeof(char) * size); // input size is used for initial array size.

    if(!input_string) // When it is null or 0
    {
    	printf("FUCKING MEMORY ALLOCATION ERROR!!!\n");
    	getchar();
    	exit(EXIT_FAILURE);
    	return input_string; // Call errorHandler instead of returning null
    }

    uint8_t character; // Variable to store newly read character.
    while((character = fgetc(stream)) != EOF && character != '\n'){
        input_string[len++] = character;
        if(len > 100)
        {
        	// String is too long. throw an exception.
        	// Leave it alone if it is for the remarks part
        }
        if(len == size){
	        input_string = realloc(input_string, sizeof(char) * (size*=2));
	        // input_string = realloc(input_string, (len+1));  // Increase array size by 1
            if(!input_string) // When it is null or 0
            {
            	printf("FUCKING MEMORY ALLOCATION ERROR!!!\n");
		    	getchar();
		    	exit(EXIT_FAILURE);
            	return input_string; // Call errorHandler instead of returning null
            }
        }
    }
    input_string[len]='\0'; // Terminating the input string
    return realloc(input_string, len);
}


int my_strlen(const char* str)  // Use this or the normal strlen to test for super long strings
{
	int len = 0;
	while(str[len] != '\0')
		len++;
	return len;
}


/*	Breaks down the input string into blocks.
		1. Call the rule book / format table on formating
		2. Extract Keywords
		3. check if the string is formatted correctly
		4. check if the actions requested is valid
		5. If valid, Format and create action/excecution path based on the keyword blocks/order
		5. save the strings/excecution path into seperate blocks of actions into memory
		and create a count variable(number of blocks) for using. Just like argc and argv of the main function
	*/	


static void * tokenizer(char * input_string, char * delimiter)
{
	char** token_array = (char**) calloc(1, sizeof(char*)); // calloc type caster not needed in 'straight C'
	// Initially one "1D" element, the element will be used to store the array size.
	// Is calloc memory static and also non scope bound variables?
	// Can I use calloc when it is only 1 element?

	if(token_array == NULL){ // To integrate with errorHandler
		printf("Token array heap memory allocation failed. Exiting program now.\n");
		exit(EXIT_FAILURE);
	}

	if(sizeof(*input_string) < 1){ // Check if string is empty
		// errorHandler to reExecute prev func.
	}

	uint8_t token_count = 0; // Token count is only incremented after token is saved into array.
	char * token = strtok(input_string, delimiter); // Read first token of string.
	while(token != NULL) // Loop if current token is valid.
	{
		token_array = realloc(token_array, sizeof(char*) * (token_count+1+1)); // Increase size of char pointer array by 1 element.
		// The +1+1 means add 1 for the arraysize element and add 1 for the actual increment of size
		token_array[++token_count] = calloc(sizeof(*token), sizeof(char));
		// Give the 1D element a pointer to store a 2D element and give the 2D element memory base on sizeof(token)
		token_array[token_count] = token; // Save token into token_array
		token = strtok(NULL, delimiter); // Read a new token
	}
	token_array[0] = token_count; // Element 0 of array stores arraysize
	return token_array;
}

// learn about c accesses modifiers / access control

char * delimiter[] = {
" ", // Remove "space"
" ,.-", // Remove "space" & "comma" & "dash"
"menu/subMenu2.txt"
};

void keyword_identifier(char** token_array); // Function prototype to be deleted.
uint8_t ApplicationPrompt() // Return type to be determined
{
	/*	Steps:
		1. Read user input.
		2. Call tokenizer function to parse input string into tokens.
		3. Search for keywords in token_array.
		4. Determine course of action matching the combination of keywords found.
		5. Return course of action to be taken back to the function caller
		6. Function caller executes return value's corresponding course of action
	*/
    printf("(sense-PF): "); // sense-PF stands for Sensible Pocket Finance or Sensible Personal Finance
    // Save string in memory, and save start address of string to 'input_string' pointer.
    char * input_string = getString(stdin, 8); // Read User's input, 'size' is 8 for main prompt.
	char** token_array = tokenizer(input_string, delimiter[1]); // Store Tokenized input_string into token_array
	uint8_t num_of_token = token_array[0]; // Read the arraysize stored in element 0 of the array.
	
	keyword_identifier(token_array);



	for(uint8_t i = 0; i < num_of_token; i++){
		printf("Token %d is %s\n", i+1, token_array[i+1]);
		free(token_array[i]);
		token_array[i] = NULL;
		printf("The pointer of element %d is %s.\n", i+1, (token_array[i] == NULL) ? "now NULL" : "not freed");
	}

	free(token_array);
	token_array = NULL;
	printf("The pointer to token_array is %s.\n", (token_array == NULL) ? "now freed." : "not freed.");

	free(input_string);
	input_string = NULL;
	printf("The pointer to input_string is %s.\n", (input_string == NULL) ? "now freed." : "not freed.");






	// global_flags_methods()
	// Set next action flag to COURSE_OF_ACTION_ID	
	// return SUCCESS;
}

// #define NUM_OF_KEYWORDS sizeof(keyword)/sizeof(char*)
char * keyword[] = {
	// Keywords entered must be all lower case --> use the toupper() function to change to lower
	"exit",
	"goto",
	"view", // To display data called by query following command
	"set",
	"select",

	"edit", // To edit object after this
	"del",

	"date", // To specify dates. Date format: "DDMMYY", assuming year = 20XX.
	"sum", // Summary
};

void keyword_identifier(char** token_array)
{
	uint8_t num_of_token = token_array[0]; // Read the arraysize stored in element 0 of the array.
	/*Many methods to extract keyword like using hashtable*/


	/*Method 1 -> Using O(n*m) speed. Works but will probs be slow*/
	uint8_t num_of_keywords = sizeof(keyword)/sizeof(char*);

	uint8_t num_of_keywords_detected = 0;
	for(uint8_t x = 1; x<num_of_token+1; x++)
	{
		for(uint8_t i = 0; i<num_of_keywords; i++)
		{
			if(!strcmp(token_array[x], keyword[i]))
			{
				++num_of_keywords_detected;
				printf("token %d matches keyword num %d --> '%s'\n", x, i, keyword[i]);
				// Keyword_String[num_of_keywords_detected] = i; // Must be after num_of_keywords_detected incrementation
			}
		}
	}
}

/* Always write documentation that explains WHY the code does what it does.
	This documentation should include the context and business rules that drove
	the development of the code in the first place. It is useful to include
	this as comments in the source code so the WHY explanation travels with the WHAT.
*/

int main(void)
{
	ApplicationPrompt();

	// Excecute course of action, that is set by applicationPrompt

    printf("\n---End---");
    getchar();
    system("cls");

    return 0;
}


/*	Input format:
	1: Keyword/Operator/Action word
	2: Objects to act upon / operand
	3: Additional keywords/input
*/


#ifdef non_production
void * keyword_extractor()
static uint8_t Keyword_String[1]; // Static to keep data in memory for function caller to use
printf("%s\n", (num_of_keywords_detected) ? "Total of %d keywords detected.\n" : "No Keywords detected.\n");
Keyword_String[0] = num_of_keywords_detected; // Element 0 of array indicates arraysize
#endif


int specialCharCheck(int specialCharIndex, char character) // Checks for special characters(singular) only
{
	// INPUT:
	// 0 for all of the special char below
	/*For input 0, return value will be same as the 
	specific input values choice index*/
	// 1 for '.'
	// 2 for '\n'
	// 3 for 'exit', 'EXIT'
	// 4 for 'Y', 'y'
	// 5 for 'N', 'n'
	// 6 for '..', 'back', 'BACK'
	// 7 for '0'
	// 8 for 'q', 'Q'

	//  for space

	// Input should be a char array and should be passed to function with a pointer

	switch(specialCharIndex)
	{
		case 0: break;
		case 1:
			if(character == specialCharArray[i])
			if(specialCharIndex != 0)
				break;
		case 2:
			if(specialCharIndex != 0)
				break;
		case 3:
			if(specialCharIndex != 0)
				break;
		case 4:
			if(specialCharIndex != 0)
				break;			
		default:
			// Internal error
			break;
	}

	if(specialCharIndex == 0)
		for(int i = 0; i<sizeof(specialChar); i++)

	/* Implement a loop where it loops over all the characters and the function
	returns a int as ascii index number and use a if else statement to check for
	the special characters, and if true ue escape sequence to execute code base
	on character read in
	*/
}