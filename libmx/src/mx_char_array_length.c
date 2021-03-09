#include "libmx.h"
#include <stdio.h>

int mx_char_array_length(char **char_array)
{
    int counter = 0;

    for (; char_array[counter] != NULL; counter++){}

    return counter;
}
