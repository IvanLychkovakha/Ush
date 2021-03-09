#include "libmx.h"

char* mx_str_slice(char* s, int from, int to)
{
    int j = 0;
    for(int i = from; i <= to; ++i)
        s[j++] = s[i];
    s[j] = 0;
    return s;
}
