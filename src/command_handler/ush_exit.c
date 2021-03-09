#include "../../inc/main_dependecy.h"

int ush_exit(command* cum)
{
  int return_val = 0;

    if (cum->param_length == 1)
    {
        exit(0);
        return_val = 0;
    }
    else if (mx_atoi(cum->parameters[1]) == -2147483648
            && cum->param_length == 2) {
        fprintf(stderr, "ush: exit: %s: numeric argument required\n", cum->parameters[1]);
        exit(1);
    }
    else if (cum->param_length == 2)
    {
        
        return_val = mx_atoi(cum->parameters[1]);
    }
    else 
    {
        fprintf(stderr, "ush: exit: too many arguments\n");
         exit(1);
    }
    exit(0);
    return 0;
}
