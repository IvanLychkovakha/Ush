#include "../../inc/main_dependecy.h"


static void arrow_left(int *begin, int *position){
    if(*position > *begin){
        mx_printstr("\033[D");
        --(*position);
    }
}

static void arrow_rigt(int *max, int *position){
    if(*position  < *max){
        mx_printstr("\033[C");
        ++(*position);
    }
}


void control_arrow(char ch,t_mouse *mouse){
    switch (ch)
    {
    case M_RIGHT:
      arrow_rigt(&mouse->max,&mouse->position);
        break;
    case M_LEFT:
        arrow_left(&mouse->begin,&mouse->position);
        break;
    case ARROW_UP:
        break;
    case ARROW_DOWN:
        break;
    
    default:
        break;
    }
}

