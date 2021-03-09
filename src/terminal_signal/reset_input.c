#include "../../inc/main_dependecy.h"

void reset_input_mode(t_terminal *termi) {
    tcsetattr(0, TCSANOW, &(termi->seve_atribut_terminal)); 
}
