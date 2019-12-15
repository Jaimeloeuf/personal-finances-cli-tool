#include <stdio.h>
#include <stdint.h>

uint64_t sum(uint64_t num)
{
    if(num)
        return num + sum(num-1); // sum() function calls itself
    else
        return num;
}

int main()
{
   	uint64_t number, result;

    printf("Enter a positive integer: ");
    scanf("%ld", &number);

    result = sum(number);

    printf("sum=%d", result);
}

//43429