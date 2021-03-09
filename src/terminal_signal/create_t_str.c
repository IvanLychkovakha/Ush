#include "../../inc/main_dependecy.h"




t_str * create_t_str(){
    t_str * readline = (t_str*)malloc(sizeof(t_str));
    readline->status = true;
    readline->position = 0;
    readline->buffer = malloc(sizeof(char)*BUFFER_SIZE);
    readline->mouse =  (t_mouse *)malloc(sizeof(t_mouse));
    readline->mouse->begin = 5;
    readline->mouse->position = 5;
    readline->mouse->max = 5;
    return readline;
}

