#include "../../inc/main_dependecy.h"

t_terminal *terminal_begin(){
    t_terminal  * termi = (t_terminal *)malloc(sizeof(t_terminal));
    tcgetattr(0, &(termi->seve_atribut_terminal));
    memcpy(&termi->terminal, &termi->seve_atribut_terminal, sizeof(termi->terminal));
    termi->terminal.c_lflag &= ~(ICANON|ECHO|ISIG);
    termi->terminal.c_cc[VMIN] = 1;
    termi->terminal.c_cc[VTIME] = 1;
    

    return termi;
}
