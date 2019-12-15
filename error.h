#include <stdint.h>


uint8_t errorHandler(uint8_t errorType, uint8_t error_ID);


// errorType:
#define ER_INTERNAL 1
#define ER_INPUT 2
#define ER_AUTH_FAILURE 3
// error_ID:
#define ER_bad_execution 11
#define ER_malloc_failure 12
#define ER_realloc_failure 13
#define ER_free_failure 14

#define fptr_null




/*	
	https://stackoverflow.com/questions/8627625/is-it-possible-to-make-function-that-will-accept-multiple-data-types-for-given-a
	-Templates
	-function overloading
	-unions

	https://en.wikibooks.org/wiki/C_Programming/Procedures_and_functions
	https://www.cs.bu.edu/teaching/c/file-io/intro/
	https://www.cs.uic.edu/~jbell/CourseNotes/C_Programming/Functions.html
	https://stackoverflow.com/questions/4161656/replacing-with-bitwise-operators


	More advanced stuff:
	https://www.researchgate.net/post/Which_is_the_preferred_nonlinear_optimization_library_for_c_c
	https://research.google.com/archive/mapreduce.html
	
*/