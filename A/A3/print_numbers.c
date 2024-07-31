#include "print_numbers.h"
#include <stdio.h>

extern int s;
extern int* nums;

void
print_numbers(void)
{
    for (int k = 0; k < s; ++k) {
        printf("%d\n", nums[k]);
    }
}
