#ifndef GLOBAL_FLAGS_H
#define GLOBAL_FLAGS_H


#ifndef TRUE
#define TRUE 1 // Or should I define it as ! FALSE?
#endif

#ifndef FALSE
#define FALSE 0
#endif
// https://stackoverflow.com/questions/1921539/using-boolean-values-in-c
// Use enum method from abv site for Boolean




// Action Macros for GLOBAL_FLAGS_METHODS
#define CLEAR_BIT 0
#define SET_BIT 1
#define TOGGLE_BIT 2
#define READ_BIT 3
// End of Action Macros for GLOBAL_FLAGS_METHODS


#define IN_AUTH
#define IN_GENERAL


// SETTING_FLAGS Bits Defns:
// #define 




#include <stdint.h> // Used for standard fixed width Data Types definition e.g. uint8_t is 8bit
uint8_t GLOBAL_FLAGS_METHODS(uint8_t FLAG_id, uint8_t action);

// GLOBAL_FLAG Bits Defns:
#define ALL_FLAGS 0XFF // Use this FLAG to set/reset/toggle all Flags in GLOBAL_FLAGS at once.
#define EXIT_PROGRAM 0x01 // Bit 0: Exit/Quit Program Flag <1: Quit, 0: Not Quit>
#define ERROR 0x02 // Bit 1: Error Flag <1: Error detected from previous operation, 0: No Error>
#define AUTHENTICATION 0x04 // Bit 2: <1: Successful, 0: Unsuccessful>
#define STACK_LOCATION 0x08 // Bit 3: Program_Flow_Stack Bit <1: Stack, 0: Don't Stack>
#define KEYWORD 0x16 // Bit 4: Keyword precesence flag <1: Present, 0: NOT Present>
// Bit 5: Change Location Bit, controlled by input parser
// Bit 6: Next Location Bit
// Bit 7: Control Bit for Lock bit for file access protection
// End of GLOBAL_FLAG Bits Defns.


#endif // End of file