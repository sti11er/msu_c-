#include "read_numbers.h"
#include <stdlib.h>
#include <stdio.h>

extern int s, c;
extern int* nums;

void
read_numbers(int max)
{
    int n; int i=0;
    while (i < max && scanf("%d", &n) == 1) {
        // printf(">%d %d %d\n", c, s, n);
        if (c == s) {
            if (c == 0) {
                c = 100;
            } else {
                c = 2 * c;
            }
            nums = realloc(nums, c * sizeof *nums);
        }
        nums[s++] = n;
        i++;
    }
}

