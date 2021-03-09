#include "../../inc/main_dependecy.h"
static int count_semicolon(char *line){
    int counter = 2;
    bool flag1 = false;
    bool flag2 = false;
    for(int i = 0; line[i] != '\0'; i++){
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
        if(line[i] == ';' && flag1 == false && flag2 == false){
            counter++;
        }
        
    }
    return counter;
}
static int get_semicolon_index(char *line){
    
    bool flag1 = false;
    bool flag2 = false;
    for(int i = 0; line[i] != '\0'; i++){
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
        if(line[i] == ';' && flag1 == false && flag2 == false){
           return i;
        }
        
    }
    return -1;
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
char** validate_semicolon(char *line){
    int flag = 0;
    char **argv = NULL;
    int counter = 0;
    //printf("str:%s\n", str);
    
    //printf("Result:%s\n", result);
    int index = get_semicolon_index(line);
    if (index != -1)
    {
        argv = (char **)malloc((count_semicolon(line) + 1) * sizeof(char *));
        argv[counter] = mx_strnew(index + 1);
        argv[counter] = mx_strncpy(argv[counter], line, index);
        //printf("argv[counter]1:%s\n", argv[counter]);
        line = get_index_ptr(line , index + 1);
        counter++;
        while (true)
        {
            index = get_semicolon_index(line);
            if (index == -1)
                break;
            argv[counter] = mx_strnew(index + 1);
            argv[counter] = mx_strncpy(argv[counter], line, index);
            //printf("argv[counter]2:%s\n", argv[counter]);
            counter++;
            if (line[index + 1] != '\0')
                line = get_index_ptr(line, index + 1);
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
             //printf("result:%s\n", validate_space(result));
            argv[counter++] = mx_strdup(line);
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
    argv[counter++] = mx_strdup(line);
    argv[counter] = NULL;
    return argv;
}

/*char** validate_semicolon(char* line)
{
   
    int quota1 = 0;
    int quota2 = 0;
    int size = 1;

    for(int i = 0; line[i] != '\0'; i++)
        if(line[i] == ';')
            size++;

    char** commands = (char**) malloc(sizeof(char*) * (size + 1));
    int index = 0;

    for(int i = 0; line[i] != '\0'; i++)
    {
        if(line[i] == '\'')
            quota1++;

        if(line[i] == '\"')
            quota2++;

        if(line[i] == ';' && quota2 % 2 == 0 && quota1 % 2 == 0)
        {

            commands[index] = mx_strnew(1024);

            if(i > 0)
                commands[index] = mx_strncpy(commands[index], line, i);
            else
            {
                commands[index] = "";
            }

            line += (i + 1);
            index++;
            i = 0;    
        }

    }
    if(mx_strlen(line) > 0)
    {
        commands[index] = mx_strnew(mx_strlen(line) + 1);
        commands[index] = mx_strcpy(commands[index], line);
        index++;
    }

    for(; index < size + 1; index++)
    {
        free(commands[index]);
        commands[index] = NULL;
    }

    return commands;
}*/
