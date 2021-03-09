#include "../../inc/main_dependecy.h"

bool is_bad_symbol(int ch)
{
    if(mx_isdigit(ch))
    {
        return false;
    }
    if(ch >= 65 && ch <= 90)
        return false;

    if(ch >= 97 && ch <= 122)
        return false;

    return true;
}

