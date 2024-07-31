#include <stdlib.h>
#include <stdio.h>
#include "shrink_numbers.h"

extern int s, c;
extern int* nums;

void
shrink_numbers(void)
{
    while (s >= 2 && nums[s - 1] == nums[s - 2]) {
        // printf("-: %d\n", s);
        nums = realloc(nums, (--s) * sizeof *nums);
        c = s;
    }
    printf("\n");
}

