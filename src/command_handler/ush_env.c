#include "../../inc/main_dependecy.h"

static int launce(char **args, char **env);
static void run_flag_i(command *cum);
static void run_standart_env(command *cum);
static void run_flag_u(command *cum);
static void run_flag_P(command *cum);

int ush_env(command *cum)
{
    if (cum->param_length > 1)
    {
        if (mx_strcmp(cum->parameters[1], "-i") == 0)
        {
            run_flag_i(cum);
        }
        else if (mx_strcmp(cum->parameters[1], "-P") == 0)
        {
            run_flag_P(cum);
        }
        else if (mx_strcmp(cum->parameters[1], "-u") == 0)
        {
            run_flag_u(cum);
        }
        else if (cum->parameters[1][0] == '-')
        {
            mx_printerr("env: illegal option -- ");
            write(2, &cum->parameters[1][1], 1);
            mx_printerr("\nusage: env [-iv] [-P utilpath] [-S string] [-u name]\n           [name=value ...] [utility [argument ...]]\n");
            return 1;
        }
        else
        {
            run_standart_env(cum);
        }
    }
    else
    {
        extern char **environ;
        if (cum->param_length < 2)
            mx_print_strarr(environ, "\n");
    }

    return 0;
}

static void run_flag_P(command *cum)
{
    if(cum->param_length == 2)
    {
        mx_printerr("env: option requires an argument -- P\n");
        mx_printerr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
        mx_printerr("           [name=value ...] [utility [argument ...]]\n");
            return;
    }
    if(cum->param_length == 3)
    {
        extern char** environ;

        mx_print_strarr(environ, "\n");
    }
    else
    {
        extern char** environ;

        char *path_var = NULL;
        path_var = mx_strdup(getenv("PATH"));

        if(path_var != NULL)
        {
            setenv("PATH", cum->parameters[2], 1);

            char** args = (char **) malloc(sizeof(char*) * (cum->param_length - 2));

            for(int i = 3; i < cum->param_length; i++)
            {
                args[i - 3] = mx_strdup(cum->parameters[i]);
            }
            args [cum->param_length - 3] = NULL;
            launce(args, environ);

            setenv("PATH", path_var, 1);

            for(int i = 0; i < cum->param_length - 3; i++)
            {
                free(args[i]);
            }
            free(args);
            args = NULL;
        }

        free(path_var);
        path_var = NULL;
    }
}

static void run_flag_u(command *cum)
{
    if (cum->param_length == 2)
    {
        mx_printerr("env: option requires an argument -- u\n");
        mx_printerr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
        mx_printerr("           [name=value ...] [utility [argument ...]]\n");
            return;
    }
    else if (cum->param_length == 3)
    {
        if (mx_get_char_index(cum->parameters[2], '=') < 0)
        {
            char *temp_env_var = NULL;
            if (getenv(cum->parameters[2]) != NULL)
                temp_env_var = mx_strdup(cum->parameters[2]);

            if (mx_strcmp(cum->parameters[2], "_") != 0 || mx_strcmp(cum->parameters[2], "PATH") != 0)
                unsetenv(cum->parameters[2]);

            extern char **environ;
            mx_print_strarr(environ, "\n");

            if (temp_env_var != NULL)
                setenv(cum->parameters[2], temp_env_var, 0);

            free(temp_env_var);
            temp_env_var = NULL;
        }
        else
        {
            mx_printerr("env: unsetenv ");
            mx_printerr(cum->parameters[2]);
            mx_printerr(": Invalid argument\n");
        }
    }
    else
    {
        char *temp_env_var = NULL;

        if (getenv(cum->parameters[2]) != NULL)
        {
            temp_env_var = mx_strdup(getenv(cum->parameters[2]));

            unsetenv(cum->parameters[2]);
        }

        char **args = (char **)malloc(sizeof(char *) * cum->param_length - 2);

        int j = 0;
        for (int i = 3; i < cum->param_length; i++, j++)
        {
            args[j] = mx_strdup(cum->parameters[i]);
        }
        args[j] = NULL;

        extern char **environ;
        mx_print_strarr(environ, "\n");

        launce(args, environ);

        if (temp_env_var != NULL)
            setenv(cum->parameters[2], temp_env_var, 0);

        free(temp_env_var);
        temp_env_var = NULL;

        for (int i = 0; i < cum->param_length - 2; i++)
            free(args[i]);
        free(args);
        args = NULL;
    }
}

static void run_standart_env(command *cum)
{
    extern char **environ;

    int env_length = 0;
    int i;
    for (i = 1; i < cum->param_length; i++)
    {
        env_length++;
        if (mx_get_char_index(cum->parameters[i], '=') < 0)
            break;
    }

    char **env = (char **)malloc(sizeof(char *) * (env_length + mx_char_array_length(environ) + 1));
    for (i = 0; i < mx_char_array_length(environ); i++)
        env[i] = mx_strdup(environ[i]);

    int j;
    for (j = 1; j < cum->param_length; j++, i++)
    {
        if (mx_get_char_index(cum->parameters[j], '=') > 0)
        {
            env[i] = mx_strdup(cum->parameters[j]);
            env[i + 1] = NULL;
        }
        else
            break;
    }

    int args_length = (cum->param_length - j);
    char **args = (char **)malloc(sizeof(char *) * args_length + 1);

    for (int index = 0; index < args_length; index++, j++)
    {
        args[index] = mx_strdup(cum->parameters[j]);
    }
    args[args_length] = NULL;

    if (args_length < 1)
        mx_print_strarr(env, "\n");
    else
        launce(args, env);

    for (int k = 0; k < args_length; k++)
        free(args[k]);
    free(args);
    args = NULL;

    for (int k = 0; k < env_length; k++)
        free(env[k]);
    free(env);
    env = NULL;
}

static void run_flag_i(command *cum)
{
    if(cum->param_length == 2)
        return;

    int env_length = 0;
    int i;
    for (i = 2; i < cum->param_length; i++)
    {
        if (mx_get_char_index(cum->parameters[i], '=') < 0)
            break;
        env_length++;
    }
    char **env = (char **)malloc(sizeof(char *) * (env_length + 1));
    for (i = 2; i < cum->param_length; i++)
    {
        if (mx_get_char_index(cum->parameters[i], '=') > 0)
        {
            env[i - 2] = mx_strdup(cum->parameters[i]);
            env[i - 1] = NULL;
        }
        else
        {
            break;
        }
    }
    env[env_length] = NULL;

    int args_length = cum->param_length - i;
    char **args = (char **)malloc(sizeof(char *) * (args_length + 1));

    for (int index = 0; index < args_length; index++, i++)
        args[index] = mx_strdup(cum->parameters[i]);
    args[args_length] = NULL;

    if (mx_char_array_length(args) < 1)
        mx_print_strarr(env, "\n");
    else
    {
        launce(args, env);
    }

    for (int k = 0; k < args_length; k++)
        free(args[k]);
    free(args);
    args = NULL;

    for (int k = 0; k < env_length; k++)
        free(env[k]);
    free(env);
    env = NULL;
}

static int launce(char **args, char **env)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        // Child process
        if (args[0] != NULL)
            args[0] = mx_strdup(mx_strjoin("/bin/", args[0]));

        mx_print_strarr(args, "\n");

        if (execve(args[0], args, env) == -1)
        {
            perror("l$h");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("l$h");
    }
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
