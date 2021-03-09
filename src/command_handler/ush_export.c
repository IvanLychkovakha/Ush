#include "../../inc/main_dependecy.h"

static char** parse_params(char* param);
static void print_sorten_env();

int ush_export(command *cum)
{
    if(cum->param_length == 1)
    {
        print_sorten_env();
    }
    else
    {    
        for(int i = 1; i < cum->param_length; i++)
        {
            char** params = parse_params(cum->parameters[i]);

            if(mx_isdigit(params[0][0]) || is_bad_symbol(params[0][0]))
            {
                mx_printerr("export: not an identifier: ");
                mx_printerr(params[0]);
                mx_printerr("\n");
                
                return 1;
            }
            
            for(int i = 0; params[0][i] != '\0'; i++)
            {
                if(is_bad_symbol(params[0][i]))
                {
                    mx_printerr("export: not valid in this context: ");
                    mx_printerr(params[0]);
                    mx_printerr("\n");

                    return 1;
                }
            }
            setenv(params[0], params[1], 1);

            free(params[0]);
            free(params[1]);
            free(params);
            params = NULL;
        }
    }

    return 0;
}

static char** parse_params(char* param)
{
    char** params = (char **) malloc(sizeof(char*) * 2);
    short index = 0;
    int i;

    for(i = 0; param[i] != '\0'; i++)
    {
        if(param[i] == '=')
        {
            params[index] = (char *) malloc(sizeof(char) * 1024);

            if(param[0] == '\"' && param[i - 1] == '\"')
            {
                int j;
                for(j = 1; j < i - 1; j++)
                    params[index][j - 1] = param[j];
                params[index][j - 1] = '\0';
                
            }
            else
            {
                params[index] = strncpy(params[index], param, i);
            }
            index++;
            break;
        }
    }

    if(param[i + 1] == '\"')
        i++;

    params[index] = (char *) malloc(sizeof(char) * 1024);

    int j = 0;
    for( ++i; param[i] != '\0'; i++, j++)
    {
        params[index][j] = param[i];
    }
    
    if(params[index][j - 1] == '\"')
        params[index][j - 1] = '\0';
    else
        params[index][j + 1] = '\0';

    return params;
}

static void print_sorten_env()
{
    extern char** environ;
    int environ_length = mx_char_array_length(environ);
    char** sorted_environ = (char **) malloc(sizeof(char *) *  environ_length);

    for(int i = 0; i < environ_length; i++)
    {
        sorted_environ[i] = (char*) malloc(sizeof(char) * 1024);
        sorted_environ[i] =   mx_strcpy(sorted_environ[i], environ[i]);
    }

    mx_bubble_sort(sorted_environ, environ_length);
    mx_print_strarr(sorted_environ, "\n");

    for(int i = 0; i < environ_length; i++)
        free(sorted_environ[i]);
    free(sorted_environ);
    sorted_environ = NULL;
}

