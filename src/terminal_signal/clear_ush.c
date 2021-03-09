#include "../../inc/main_dependecy.h"



void clear_ush(char *line, t_terminal *termi, t_str *readline){
    free(line);
    reset_input_mode(termi);
    free(termi);
    free(readline);
    
}

