#include "../../inc/main_dependecy.h"
static int get_questmark_index(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '$' && str[i + 1] == '?')
        {
        
            return i ;
        }
    }
    return -1;
}
static char * get_index_ptr(char * str, int index){
    while (index != 0)
    {
        str++;
        index --;
    }
    return str;
    

}
char *mx_validate_questmark_with_dollar(char *line, int status)
{
    int index = get_questmark_index(line);
    int flag = 0;
    char *str = NULL;

    if (index != -1)
    {
        str = mx_strnew(index+1);
        str = mx_strncpy(str, line, index);
        str = mx_strjoin(str, mx_itoa(status));
        line = get_index_ptr(line, index + 2);
        while (true)
        {
            index = get_questmark_index(line);
            if(index == -1 )
                break;
            char * temp = mx_strnew(index+1);
            temp = mx_strncpy(temp, line, index);
            str = mx_strjoin(str, temp);
            str = mx_strjoin(str, mx_itoa(status));
            if(line[index + 2] != '\0')
                line = get_index_ptr(line, index + 2);
            else{
                flag = 1;
                break;
            }
                
            mx_strdel(&temp);
            
        }
         if(flag == 0)
            str = mx_strjoin(str, line);
         
        return str;

    }

    return line;
}
