#include "../../inc/main_dependecy.h"

int ush_pwd(command *cum)
{

    int is_link = 0;
    if (cum->param_length == 3 && ((mx_strcmp(cum->parameters[1], "-L") == 0 && mx_strcmp(cum->parameters[2], "-P") == 0) || (mx_strcmp(cum->parameters[1], "-P") == 0 && mx_strcmp(cum->parameters[2], "-L") == 0)))
    {
        char *pwd = mx_strdup(getenv("PWD"));
        is_link = mx_check_symlink(&pwd, 2, 2);
        mx_printstr(pwd);
        mx_printchar('\n');
        mx_strdel(&pwd);
    }
    else if (cum->param_length == 2 && mx_strcmp(cum->parameters[1], "-P") == 0)
    {
        char *pwd = mx_strdup(getenv("PWD"));
        is_link = mx_check_symlink(&pwd, 2, 2);
        mx_printstr(pwd);
        mx_printchar('\n');
        mx_strdel(&pwd);
    }
    else if (cum->param_length == 1 || (mx_strcmp(cum->parameters[1], "-L") == 0 && cum->param_length == 2))
    {
        mx_printstr(getenv("PWD"));
        mx_printchar('\n');
    }
    else
    {
        if (cum->parameters[1][0] == '-' && (cum->parameters[1][1] != 'L' && cum->parameters[1][1] != 'P') && (cum->param_length == 2 || cum->param_length == 3))
        {
            fprintf(stderr, "pwd: bad option: %s\n", cum->parameters[1]);
            return 1;
        }
        else if (cum->param_length == 3 && cum->parameters[1][0] == '-' && cum->parameters[2][0] == '-' && (cum->parameters[2][1] != 'L' && cum->parameters[2][1] != 'P'))
        {
            fprintf(stderr, "pwd: bad option: %s\n", cum->parameters[2]);return 1;
        }
        else
        {
            fprintf(stderr, "pwd: too many arguments\n");
            return 1;
        }
    }
    return 0;
}
