#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static char * getString(FILE* stream, size_t size)
{
	// Static access modifier to only allow functions in this file to call it.
	// The String that is read will be entirely stored in Heap Memory. The function will
	// stop working if it is out of memory and will return a Null back to function caller.
	/*	Input Parameter:
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
	// Static access modifier to only allow functions in this file to call it.

	char** token_array = (char**) calloc(1, sizeof(char*));
	// Initially one "1D" element, the element will be used to store the array size.
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

char * delimiter[] = {
" ", // Remove "space"
" ,.-", // Remove "space" & "comma" & "dash"
"menu/subMenu2.txt"
};

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
    printf("(Command-Prompt): ");
    // Save string in memory and store the start address to 'input_string'
    char * input_string = getString(stdin, 5); // Read User's input, 'size' is 5 for main prompt
	char** token_array = tokenizer(input_string, delimiter[1]); // Store Tokenized input_string into token_array
	uint8_t num_of_token = token_array[0]; // Read the arraysize stored in element 0 of the array.
	
	printf("\nNumber of tokens from tokenizer: %d\n", num_of_token); // Printing out element 0 of array
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

int main(void)
{
	ApplicationPrompt();

	// Excecute course of action, that is set by applicationPrompt

    printf("\n---End---");
    getchar();
    system("cls");

    return 0;
}