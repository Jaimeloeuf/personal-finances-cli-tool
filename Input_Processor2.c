void extract_32bit_to_4_btes(uint32_t value){// Example value: 0x01020304
    uint8_t byte1 = (value >> 24);           // 0x01020304 >> 24 is 0x01 so no masking is necessary
    uint8_t byte2 = (value >> 16) & 0xff;    // 0x01020304 >> 16 is 0x0102 so we must mask to get 0x02
    uint8_t byte3 = (value >> 8)  & 0xff;    // 0x01020304 >> 8 is 0x010203 so we must mask to get 0x03
    uint8_t byte4 = value & 0xff;            // here we only mask, no shifting is necessary
}

int main()
{
    unsigned int len_max = 128;
    unsigned int current_size = 0;
    
    char *pStr = malloc(len_max);
    current_size = len_max;

    printf("\nEnter a very very very long String value:");

    if(pStr != NULL)
    {
	int c = EOF;
	unsigned int i =0;
        //accept user input until hit enter or end of file
	while (( c = getchar() ) != '\n' && c != EOF)
	{
		pStr[i++]=(char)c;

		//if i reached maximize size then realloc size
		if(i == current_size)
		{
                        current_size = i+len_max;
			pStr = realloc(pStr, current_size);
		}
	}

	pStr[i] = '\0';

        printf("\nLong String value:%s \n\n",pStr);
        //free it 
	free(pStr);
	pStr = NULL;


    }
    return 0;
}

void main(void)
{
	printf("Enter a string: ");
	char string[10];
	fgets()
	fseek(stdin, 0, SEEK_SET);
	scanf("%s", &string);
	printf("The len of the str is %d\n", strlen(string));
}

void safe_realloc(void *ptr, size_t size) // Consider making this a static function as access modifier
{
	/*	Use this function in a similiar way to the normal realloc.
		The only difference from the std realloc is that this function modifies the input
		parameter ptr directly and this function includes a check if reallocation fails.
	*/
	ptr = realloc(ptr, size); // Modifies Users ptr
	if(ptr == NULL)
		fprintf(stderr, "Reallocation of memory failed.\n");
		// Perhaps do more stuff here like call error handler
}
	
char *menus[] = {
"menu/MainMenu.txt",
"menu/subMenu1.txt",
"menu/subMenu2.txt",
"menu/subMenu3.txt",
"menu/subMenu4.txt",
"menu/subMenu5.txt",
"menu/subMenu6.txt"
};

char settings[]="data files/settings.txt";
char dataFile[]="data files/program data.txt";
char names[]="data files/sector names.txt";
char manual[]="data files/manual.txt";
char error_log_file[]="errors/error log.txt";


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

char *OPERAND[] = {
		
	/*	Make this into a 2D string array so instead of refering to the operators
		with comments, every operator has their own array of words. 
		Possibly add the keyword into the 2D array too. so the element 0 will be
		the keyword/ opereator, then the words onwards will be the operands
	*/

	// For operator "view"
	"log", "sum",
	// For operator "edit"
	"log", "settings", "order", "remarks", "timestamp"

	// For operator "sum",
};

char *SYMBOL[] = {
	".", // Stop symbol
	"*", // Wildcard symbol
	"," // Additional input entered
};




/*	https://www.tutorialspoint.com/cprogramming/c_input_output.htm
	https://www.tutorialspoint.com/cprogramming/c_file_io.htm
	
	https://www.tutorialspoint.com/cprogramming/c_preprocessors.htm
	
	https://www.tutorialspoint.com/cprogramming/c_bit_fields.htm
	https://www.tutorialspoint.com/cprogramming/c_typedef.htm
	https://www.tutorialspoint.com/cprogramming/c_structures.htm
	https://www.tutorialspoint.com/cprogramming/c_unions.htm	
*/

The C library function int fseek(FILE *stream, long int offset, int whence)
sets the file position of the stream to the given offset.
This function returns zero if successful, or else it returns a non-zero value.

Declaration of fseek is int fseek(FILE *stream, long int offset, int whence)
stream − The pointer to a FILE object that identifies the stream.
offset − Number of bytes to offset from whence.
whence − The position from where offset is added. It is specified by one of the following constants

Constants:
1. SEEK_SET -->Beginning of file
2. SEEK_CUR --> Current position of the file pointer
3. SEEK_END --> End of file


Sites for string processing:
https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
http://www.cplusplus.com/reference/cstring/strcspn/
http://www.cplusplus.com/reference/cstring/strpbrk/
http://www.cplusplus.com/reference/cstring/memcmp/

#endif