#include "../../inc/main_dependecy.h"
#define EXIT(s)                   \
    {                             \
        fprintf(stderr, "%s", s); \
        exit(0);                  \
    }
static char *launce_sub_command(char *args);
static char *exechange_sub_command_dolar(char *line);
static char *exechange_sub_command_scobka(char *line);

command *command_parser(char *line, args *master, int status)
{
    //printf("line:%s\n", line);
    line = mx_validate_questmark_with_dollar(line, status);
    //printf("line:%s\n", line);
    line = exechange_sub_command_dolar(line);
   // printf("line2:%s\n", line);
    line = exechange_sub_command_scobka(line);
    //printf("line3:%s\n", line);
    ////////////////////////////////
    char **argv = prime_split(line);
    int length = mx_char_array_length(argv);

    for (int i = 0; i < length; i++)
    {
        if (argv[i][0] == '~')
        {
            mx_tilde_check(&argv[i]);
        }
        char **temp = mx_strsplit(argv[i], '\"');
        if (temp[0][0] == '$')
        {
            argv[i] = mx_strdup(temp[0]);
            mx_dollar_check(mx_strlen(argv[i]), &argv[i]);
        }
        mx_del_strarr(&temp);
    }
    //mx_print_strarr(argv,"\n");
    command *cum = NULL;
    if (length == 0)
    {
        cum = create_command(mx_strdup(""), argv, length, master);
    }
    else
    {
        cum = create_command(mx_strdup(argv[0]), argv, length, master);
    }

    for (int i = 0; i < length; i++)
    {
        free(argv[i]);
    }
    free(argv);
    argv = NULL;
    cum->list_pid = NULL;
    return cum;
}

static char *exechange_sub_command_scobka(char *line)
{
    bool scobka = false;
    char **sub_commands = (char **)malloc(sizeof(char *) * 15);
    int index1 = 0;
    int index2 = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {
        if (scobka)
        {
            if (line[i] == '`')
            {
                sub_commands[index1][index2] = '\0';
                scobka = false;
                index1++;
                index2 = 0;
                continue;
            }
            else
            {
                sub_commands[index1][index2] = line[i];
                index2++;
            }
        }
        if (!scobka && line[i] == '`')
        {
            scobka = true;
            sub_commands[index1] = mx_strnew(1024);
        }
    }
    sub_commands[index1] = NULL;

    for (int i = 0; sub_commands[i] != NULL; i++)
    {
        char *result = launce_sub_command(sub_commands[i]);

        free(sub_commands[i]);
        sub_commands[i] = mx_strdup(result);

        free(result);
        result = NULL;
    }

    char *res_str = mx_strnew(1024);
    res_str[0] = ' ';
    scobka = false;

    int i = 0;
    while (mx_get_char_index(line, '`') >= 0)
    {
        int index = mx_get_char_index(line, '`');

        int k = mx_strlen(res_str) - 1;
        for (int j = 0; j < index; j++, k++)
            res_str[k] = line[j];
        line += (index + 1);

        index = mx_get_char_index(line, '`');
        line += (index + 1);

        res_str = mx_strjoin(res_str, " ");
        res_str = mx_strjoin(res_str, sub_commands[i]);
        res_str = mx_strjoin(res_str, "\0");

        index = mx_get_char_index(line, '`');

        if (index < 0)
            break;

        i++;
        res_str += mx_strlen(res_str) - 1;

    }

    if (mx_strlen(line) > 0)
        res_str = mx_strjoin(res_str, line);

    for (int i = 0; res_str[i] != '\0'; i++)
        if (res_str[i] == '\n')
            res_str[i] = ' ';

    return res_str;
}

static char *exechange_sub_command_dolar(char *line)
{
    bool dolar = false;
    char **sub_commands = (char **)malloc(sizeof(char *) * 15);
    int index1 = 0;
    int index2 = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {

        if (dolar)
        {
            if (line[i] == ')')
            {
                sub_commands[index1][index2] = '\0';
                dolar = false;
                index1++;
                index2 = 0;
                continue;
            }
            else
            {
                sub_commands[index1][index2] = line[i];
                index2++;
            }
        }
        if (!dolar && line[i] == '$' && line[i + 1] != '\0' && line[i + 1] == '(')
        {
            dolar = true;
            sub_commands[index1] = mx_strnew(1024);
            i++;
        }
    }
    sub_commands[index1] = NULL;
    if(index1 == 0)
        return line;


    for (int i = 0; sub_commands[i] != NULL; i++)
    {


        char *result = launce_sub_command(sub_commands[i]);

        free(sub_commands[i]);
        sub_commands[i] = mx_strdup(result);

        free(result);
        result = NULL;
    }

    char *res_str = mx_strnew(1024);
    res_str[0] = ' ';
    dolar = false;

    int i = 0;
    while (i < index1)
    {
        int index = mx_get_char_index(line, '$');

        if (line[index + 1] != '\0' && line[index + 1] == '(')
        {
            int k = mx_strlen(res_str) - 1;
            for (int j = 0; j < index; j++, k++)
                res_str[k] = line[j];

            index = mx_get_char_index(line, ')');
            if (index < 0 || index + 1 == '\0')
                break;

            line += (index + 1);

            res_str = mx_strjoin(res_str, " ");
            res_str = mx_strjoin(res_str, sub_commands[i]);
            res_str = mx_strjoin(res_str, "\0");
            i++;
            res_str += mx_strlen(res_str - 1);
        }
        else
        {
            int k = mx_strlen(res_str) - 1;

            for (int j = 0; j < index + 3; j++, k++)
                res_str[k] = line[j];
            
            index++;

            line += (index + 1);    
        }
    }

    if (mx_strlen(line) > 0)
    {
        res_str = mx_strjoin(res_str, line);
    }

    for (int i = 0; res_str[i] != '\0'; i++)
        if (res_str[i] == '\n')
            res_str[i] = ' ';

    return res_str;
}

static char *launce_sub_command(char *args)
{
    FILE *fp;
    int status;
    char buff[1024];
    char *res = NULL;

    fp = popen(args, "r");
    if (fp == NULL)
        EXIT("Ошибка открытия файла.........\n");

    while (fgets(buff, 1024, fp) != NULL)
    {
        res = mx_strjoin(res, buff);
    }

    status = pclose(fp);
    return res;
}
