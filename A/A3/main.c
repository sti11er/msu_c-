#include <stdio.h>
#include <stdlib.h>
#include "read_numbers.h"
#include "shrink_numbers.h"
#include "print_numbers.h"

int *nums = 0, c = 0, s = 0;
int
main(void)
{
    read_numbers(20); // 20
    shrink_numbers();
    read_numbers(200); //200
    print_numbers();
}
