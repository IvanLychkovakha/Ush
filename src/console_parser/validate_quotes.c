#include "../../inc/main_dependecy.h"

static int get_index(char **arr, char ch, int *j);

char *del_quots(char *str)
{
    char *temp = mx_strnew(1024);
    int counter = 0;
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\' && counter != 2)
        {
            counter++;
            continue;
        }
        temp[index] = str[i];
        index++;
    }
    temp[index] = '\0';
    return temp;
}


char **prime_split(char *line)
{
    char *line_cpy = mx_strdup(line);
    //printf("line-cpy:%s\n", line_cpy);
    char **split_by_space = NULL;
    bool flag1 = false;
    bool flag2 = false;
    //char *line_cpy = add_spaces(line);
    //printf("%s\n", line_cpy);
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '\"' && line[i - 1] != '\\' && !flag2)
        {
            flag1 = !flag1;

            continue;
        }
        if (line[i] == '\'' && line[i - 1] != '\\' && !flag1)
        {
            flag2 = !flag2;

            continue;
        }
        if (flag1)
        {
            line_cpy[i] = '\"';
        }
        else if (flag2)
        {
            line_cpy[i] = '\'';
        }
    }
    // char * temp  = custom_del_extra_spaces(line_cpy);
     
    split_by_space = custom_split(line_cpy);
    //mx_print_strarr(split_by_space, "\n");

    flag1 = false;
    flag2 = false;
    int index = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '\"' && line[i - 1] != '\\')
        {
            int j;
            index = get_index(split_by_space, '\"', &j);

            if (index == -1)
                break;
            if (strcmp(split_by_space[0], "echo") != 0)
            {
                split_by_space[index] = del_quots(split_by_space[index]);
                i++;
            }
            else
            {
                split_by_space[index][j++] = line[i++];
            }

            while (true)
            {
                if (line[i] == '\"' && line[i - 1] != '\\')
                {

                    break;
                }

                split_by_space[index][j++] = line[i++];
            }

            continue;
        }
        if (line[i] == '\'' && line[i - 1] != '\\')
        {
            int j;
            index = get_index(split_by_space, '\'', &j);

            if (index == -1)
                break;

            if (strcmp(split_by_space[0], "echo") != 0)
            {
                split_by_space[index] = del_quots(split_by_space[index]);
                i++;
            }
            else
            {
                split_by_space[index][j++] = line[i++];
            }
            while (true)
            {
                if (line[i] == '\'' && line[i - 1] != '\\')
                {
                    break;
                }

                split_by_space[index][j++] = line[i++];
            }

            continue;
        }
    }
    //mx_print_strarr(split_by_space, "\n");

    return split_by_space;
}
static int get_index(char **arr, char ch, int *j)
{
    for (int i = 0; arr[i] != NULL; i++)
    {
        for (*j = 0; arr[i][*j] != '\0'; (*j)++)
        {

            if (arr[i][*j] == ch)
                return i;
        }
    }

    return -1;
}
