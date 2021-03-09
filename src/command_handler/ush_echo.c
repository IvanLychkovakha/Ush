#include "../../inc/main_dependecy.h"
static void escape_chars(int i, char *str, char *parse_str, int index)
{
    if (str[i] == 'a')
        parse_str[index] = '\a';
    else if (str[i] == 'b')
        parse_str[index] = '\b';
    else if (str[i] == 't')
        parse_str[index] = '\t';
    else if (str[i] == 'n')
        parse_str[index] = '\n';
    else if (str[i] == 'v')
        parse_str[index] = '\v';
    else if (str[i] == 'f')
        parse_str[index] = '\f';
    else if (str[i] == 'r')
        parse_str[index] = '\r';
    else
        parse_str[index] = str[i];
}
static int check_echo_flag(char *arg, bool *flag_e, bool *flag_E, bool *flag_n)
{

    for (int i = 1; i < mx_strlen(arg); i++)
    {
        if (arg[i] != 'e' && arg[i] != 'E' && arg[i] != 'n')
        {
            return -1;
        }
        if (arg[i] == 'e' && *flag_e == false)
        {
            *flag_e = true;
        }
        if (arg[i] == 'E' && *flag_E == false)
        {
            *flag_E = true;
        }
        if (arg[i] == 'n' && *flag_n == false)
        {
            *flag_n = true;
        }
    }

    return 1;
}
static char *mx_parse_echo(char *str, bool flag_e, bool flag_E)
{
    char *parse_str = mx_strnew(1000);
    int flag_quot1 = 1;
    int flag_quot2 = 1;
    int index = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\"')
        {
            flag_quot1 *= -1;
            //printf("%d", 1);
        }
        else if (str[i] == '\'' && flag_quot1 != -1)
        {
            flag_quot2 *= -1;
        }
     
        else if ((flag_e == true || (flag_e == false && flag_E == false)) && str[i] == '\\' && (flag_quot1 == -1 || flag_quot2 == -1))
        {
            // printf("%d",2);
            escape_chars(++i, str, parse_str, index++);
        }
        else if ((flag_e == true || (flag_e == false && flag_E == false) ) && str[i] == '\\' && (flag_quot1 == -1 || flag_quot2 == -1))
        {
            // printf("%d",3);
            parse_str[index++] = str[++i];
        }
       
        else if (flag_E == true && flag_e == false && str[i] == '\\' && (flag_quot1 == -1 || flag_quot2 == -1))
        {
            
            parse_str[index++] = str[i];
        } else if( (flag_e == true || (flag_e == false && flag_E == false) || (flag_E == true && flag_e == false)) && str[i] == '\\')
        {
            parse_str[index++] = str[++i];
        }
        else 
        {
            //printf("%d",5);
            parse_str[index++] = str[i];
        }
    }
    parse_str[index] = '\0';

    mx_strdel(&str);
    //printf("%s\n", parse_str);
    return parse_str;
}

static int mx_chech_num_of_quot(char *str)
{
    int counter = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
    
        if((str[i] == '\"' || str[i] == '\'' ) && ((str[i-1] == '\\' && str[i-2] == '\\') || str[i-1] != '\\' )){
            //printf("cur: %c\tprev: %c\tprprev: %c\n", str[i], str[i-1], str[i-2]);
            counter++;
        }
    }
    if (counter % 2 != 0)
        return 0;
    return 1;
}

int ush_echo(command *cum)
{
    bool flag_e = false;
    bool flag_E = false;
    bool flag_n = false;
    int flag = 0;
    char *str = NULL;
    if(mx_char_array_length(cum->parameters) == 1){
        mx_printchar('\n');
        return 0;
    }
    for (int i = 1; i < mx_char_array_length(cum->parameters); i++)
    {
        if (cum->parameters[i][0] == '-' && str == NULL && flag != -1)
        {
            flag = check_echo_flag(cum->parameters[i], &flag_e, &flag_E, &flag_n);
            if (flag == 1)
                continue;
        }
        if (str == NULL && mx_strcmp(cum->parameters[i], "") != 0)
            str = strdup(cum->parameters[i]);
        else if (mx_strcmp(cum->parameters[i], "") != 0)
        {
            str = realloc(str, strlen(str) + strlen(cum->parameters[i]) + 2);
            strcat(str, " ");
            strcat(str, cum->parameters[i]);
        }
    }

    if (mx_chech_num_of_quot(str) == 1 && str != NULL)
    {
        str = mx_parse_echo(str, flag_e, flag_E);
        if (str != NULL){
            mx_printstr(str);
        if (flag_n == false)
            mx_printchar('\n');
        }else 
            mx_printchar('\n');
        
        mx_strdel(&str);
    }
    else
    {
        mx_strdel(&str);
        fprintf(stderr, "Odd number of quotes.\n");
        return 1;
    }

    return 0;
}
