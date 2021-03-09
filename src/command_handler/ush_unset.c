#include "../../inc/main_dependecy.h"

static char* parse_param(char* param);

int ush_unset(command* cum)
{
    for(int i = 1; i < cum->param_length; i++)
    {

        char* param = parse_param(cum->parameters[i]);

        for(int j = 0; param[j] != '\0'; j++)
        {
        
            if(is_bad_symbol(param[j]))
            {
                mx_printerr("unset: ");
                mx_printerr(&param[i]);
                mx_printerr(": invalid parameter name\n");
                return 1;
                break;
            }
        }
        if(mx_strcmp(param, "_") != 0)
            unsetenv(param);

        free(param);
    }
    return 0;
}

static char* parse_param(char* param)
{
    char* res_param = (char *) malloc(sizeof(char) * 1024);
    int str_len = mx_strlen(param);

    if(str_len > 2 && param[0] == '\"' && param[str_len - 1] == '\"')
    {
        for(int i = 1; i < str_len - 1; i++)
            res_param[i - 1] = param[i];
    }
    else
    {
        res_param = mx_strcpy(res_param, param);
    }
    
    return res_param;
}
