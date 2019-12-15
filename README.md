# C CLI tool for tracking finances
(Uncomplete) CLI project to track finances to practice learning C

## reference and research
- To pass multiple arguements into a function:
   - https://www.cprogramming.com/tutorial/c/lesson17.html
   - https://stackoverflow.com/questions/24952190/elegant-way-to-pass-multiple-arguments-to-a-function
- ToolChain:
   - https://www.tutorialspoint.com/makefile/index.htm
   - https://www.tutorialspoint.com/gnu_debugger/index.htm
   - https://www.tutorialspoint.com/developers_best_practices/handy_tools_techniques.htm
- Source code to read:
   - https://github.com/postgres/postgres
   - https://github.com/illumos/illumos-gate
   - https://github.com/deeplearning4j
   - https://deeplearning4j.org/
- Algorithms:
   - http://www.cplusplus.com/reference/algorithm/
- Bitwise:
   - https://www.geeksforgeeks.org/interesting-facts-bitwise-operators-c/
   - The bitwise XOR operator is the most useful operator from technical interview perspective.
   - Simple example where “Given a set of numbers where all elements occur even number of times except one number, find the odd occurring number” This problem can be efficiently solved by just doing XOR of all numbers.
      ```c
      // Function to return the only odd occurring element
      int findOdd(int arr[], int n) {
         int res = 0, i;
         for (i = 0; i < n; i++)
         res ^= arr[i];
         return res;
      }
      
      int main(void) {
         int arr[] = {12, 12, 14, 90, 14, 14, 14};
         int n = sizeof(arr)/sizeof(arr[0]);
         printf ("The odd occurring element is %d ", findOdd(arr, n));
         return 0;
      }
      // Output: The odd occurring element is 90
      ```
   - Using bitwise operators
      1. Toggling a bit and leaving all other bits unchanged
         ```c
         x = x ^ mask; // shorthand x ^= mask;
         ```
         - Bits that are set to 1 in the mask will be toggled in x. 
         - Bits that are set to 0 in the mask will be unchanged in x.
      2. Setting a bit to zero and leaving all other bits unchanged
         ```c
         x = x & (~mask); // or x &= (~mask);
         ```
         - Bits that are set to 1 in the mask will be set to zero in x. 
         - Bits that are set to 0 in the mask will be unchanged in x.
      3. Setting a bit to one and leaving all other bits unchanged
         ```c
         x |= mask;
         ```
         - Bits that are set to 1 in the mask will be set to one in x. 
         - Bits that are set to 0 in the mask will be unchanged in x.
- Macros
   - Imagine there are two flags in the program that are independent of each other.
   - We might implement macros to manipulate them as shown in the code sample below. Macros can be placed in a header file.
   ```c
   // the flag definitions
   #define CAR_LOCKED    0x01  // 0000 0001
   #define CAR_PARKED    0x02  // 0000 0010
   #define CAR_RESET     0x00  // 0000 0000

   // macros to manipulate the flags
   #define RESET_CAR(x)     (x = CAR_RESET)

   #define SET_LOCKED(x)    (x |= CAR_LOCKED)
   #define SET_PARKED(x)    (x |= CAR_PARKED)

   #define UNSET_LOCKED(x)  (x &= (~CAR_LOCKED))
   #define UNSET_PARKED(x)  (x &= (~CAR_PARKED))

   #define TOGGLE_LOCKED(x)  (x ^= CAR_LOCKED)
   #define TOGGLE_PARKED(x)  (x ^= CAR_PARKED)

   // these evaluate to non-zero if the flag is set
   #define IS_LOCKED(x)      (x & CAR_LOCKED)
   #define IS_PARKED(x)      (x & CAR_PARKED)

   // Demo program for the above macros
   void main(void)
   {
      unsigned char mercedes, civic;

      RESET_CAR(mercedes);
      RESET_CAR(civic);

      SET_LOCKED(mercedes);

      if( IS_LOCKED(mercedes) != 0 )
         UNSET_PARKED(civic);

      TOGGLE_LOCKED(mercedes);
   }
   ```