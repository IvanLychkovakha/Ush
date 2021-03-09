#include "../../inc/main_dependecy.h"

static int count_spaces(char *str)
{
    bool state = true;
    unsigned wordcount = 0;
    int i = 0;

    if (str == NULL)
        return -1;
    else
    {
        while (str[i])
        {
            if (str[i] == ' ' && i != 0 && str[i - 1] != '\\')
                state = true;
            else if (state == true)
            {
                state = false;
                ++wordcount;
            }
            ++i;
        }
        return wordcount;
    }
}
static char *get_index_ptr(char *str, int index)
{
    while (index != 0)
    {
        str++;
        index--;
    }
    return str;
}
static int get_space_index(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ' && i != 0 && str[i - 1] != '\\')
        {
            return i;
        }
    }
    return -1;
}
static int get_slash_index(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\\' && str[i + 1] == ' ')
        {
            return i;
        }
    }
    return -1;
}
static char *custom_del_extra_spaces(const char *str)
{
    char *memory = NULL;
    char *temp = NULL;
    //bool flag = false;
    int i = 0;
    int j = 0;

    if (!str)
        return NULL;

    memory = mx_strnew(mx_strlen(str));
    while (str[i])
    {

        if (!(mx_isspace(str[i])))
        {
            memory[j] = str[i];
            j++;
        }
        if (str[i] == '\\' && str[i + 1] == ' ')
        {
            memory[j++] = ' ';
            i++;
        }
        if (!(mx_isspace(str[i])) && mx_isspace(str[i + 1]))
        {
            memory[j] = ' ';
            j++;
        }
        i++;
    }
    temp = mx_strtrim(memory);
    mx_strdel(&memory);
    return temp;
}
static char *validate_space(char *line)
{
    //printf("line:%s\n", line);
    int index = get_slash_index(line);
    //printf("index:%d\n", index);
    int flag = 0;
    char *str = NULL;

    if (index != -1)
    {
        str = mx_strnew(index+1);
        str = mx_strncpy(str, line, index);
        //printf("str1:%s\n", str);
        str = mx_strjoin(str," ");
        //printf("str2:%s\n", str);
        line = get_index_ptr(line, index + 2);
        while (true)
        {
            index = get_slash_index(line);
            if (index == -1)
                break;
            char *temp = mx_strnew(index+1);
            temp = mx_strncpy(temp, line, index);
            
            str = mx_strjoin(str, temp);
           // printf("str3:%s\n", str);
            str = mx_strjoin(str, " ");
            //printf("str4:%s\n", str);
            if (line[index + 1] != '\0')
                line = get_index_ptr(line, index + 2);
            else
            {
                flag = 1;
                break;
            }

            mx_strdel(&temp);
        }
        if (flag == 0){
            str = mx_strjoin(str, line);
           // printf("str5:%s\n", str);
        }
        return str;
    }
    return line;
}
 char **custom_split(char *str)
{
    int flag = 0;
    char **argv = NULL;
    int counter = 0;
    //printf("str:%s\n", str);
    char *result = custom_del_extra_spaces(str);
    //printf("Result:%s\n", result);
    int index = get_space_index(result);
    if (index != -1)
    {
        argv = (char **)malloc((count_spaces(result) + 1) * sizeof(char *));
        argv[counter] = mx_strnew(index + 1);
        argv[counter] = mx_strncpy(argv[counter], result, index);
        argv[counter] = validate_space(argv[counter]);
        //printf("argv[counter]1:%s\n", argv[counter]);
        result = get_index_ptr(result, index + 1);
        counter++;
        while (true)
        {
            index = get_space_index(result);
            if (index == -1)
                break;
            argv[counter] = mx_strnew(index + 1);
            argv[counter] = mx_strncpy(argv[counter], result, index);
            argv[counter] = validate_space(argv[counter]);
            //printf("argv[counter]2:%s\n", argv[counter]);
            counter++;
            if (result[index + 1] != '\0')
                result = get_index_ptr(result, index + 1);
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
             //printf("result:%s\n", validate_space(result));
            argv[counter++] = mx_strdup(validate_space(result));
            //printf("argv[counter]3:%s\n", argv[counter - 1]);
            argv[counter] = NULL;
        }
        else
        {
            argv[counter] = NULL;
        }
        return argv;
    }
    argv = (char **)malloc(2 * sizeof(char *));
    argv[counter++] = mx_strdup(result);
    argv[counter] = NULL;
    return argv;
}
