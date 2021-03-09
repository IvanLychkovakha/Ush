#include "../../inc/main_dependecy.h"

bool check_num_of_quots(char * str)
{
    int counter = 0;
    bool flag1 = false;
    bool flag2 = false;
    
    for(int i = 0; str[i] != '\0'; i++){
         if (str[i] == '\"' && str[i - 1] != '\\' && !flag2)
        {
            flag1 = !flag1;
            counter++;
            continue;
        }
        if (str[i] == '\'' && str[i - 1] != '\\' && !flag1)
        {
            flag2 = !flag2;
            counter++;
            continue;
        }
    }
    if(counter % 2 == 0 ){
        return true;
    }
    return false;
}

