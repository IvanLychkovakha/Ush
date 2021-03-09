#include "../../inc/main_dependecy.h"



static void caretra(){
    
}

static void if_arrow(char ch,char * arrow){
    if(ch == 27  && arrow[0] == '\0'){
        arrow[0] = ch;
    }
    if(ch == 91 && arrow[0] != '\0' && arrow[1] == '\0'){
        arrow[1] = ch;
    }
    if(arrow[0] != '\0' && arrow[1] != '\0' && ch >= 65 && ch <=68){
        arrow[2] = ch;
    }
}




static int if_signal(char ch,bool *c, bool *z, bool *d){
    switch (ch)
    {
    case CONTROL_C:
        *c = true;
        return 1;
        break;
    case CONTROL_D:
        *d = true;
        return 2;
        break;
    case CONTROL_Z:
        *z = true;  
        return 3;
        break;
    default:
        *c = false;
        *d = false;
        *z = false;
        return 0;
        break;
    }
}
static void ch_in_str(char ch,char * buffer, int *position){
    buffer[*position] = ch;
    write(0,&ch,1);
}

char * console_read_line(t_str *readline){
    char ch;
    int iteration_buffer = 1;
    char arrow[3] = {'\0','\0','\0'};

    while(readline->status){
        read(0,&ch,1);
        if((readline->signal = if_signal(ch,&readline->c_c,&readline->c_z,&readline->c_d)) != false){
            if(readline->c_c){
                mx_printstr("\n");
                break;
            }else{
                if(readline->c_d){
                    break;
                }
            }
        }
        else{
            if( (ch == 27) | (ch == 91 && arrow[0] != '\0') | (arrow[1] == 91)){
                if_arrow(ch,arrow);
                if(arrow[0] != '\0' && arrow[1] != '\0' && arrow[2] != '\0'){
                    control_arrow(arrow[2],readline->mouse);
                    arrow[0] = '\0';
                    arrow[1] = '\0';
                    arrow[2] = '\0';
                }
            }else {
                if(ch == DELETE){
                   if(readline->mouse->position > 5){
                       if(readline->position != 0){
                           readline->buffer[readline->position - 1] = ' ';
                           readline->position--;
                       }

                    readline->mouse->position--;
                    MX_BACKSPACE(1);
                    readline->mouse->max--;
                   }
                }else {
                {
                if(ch == NEW_LINE && readline->position == 0){
                    readline->c_c = true;
                    mx_printstr("\n");
                    break;
                }
                if(ch == NEW_LINE){
                    break;
                }
                if(readline->position >= BUFFER_SIZE){
                    iteration_buffer++;
                    readline->buffer = realloc(readline->buffer, BUFFER_SIZE * iteration_buffer);
                }

                readline->mouse->max++;
                readline->mouse->position++;
                ch_in_str(ch,readline->buffer,&(readline->position));
                readline->position++;
                }
                }
            }
        }
    }
    readline->buffer[readline->position] = '\0';
    readline->position = 0;
    readline->mouse->position = 5;
    readline->mouse->begin = 5;
    readline->mouse->max = 5;
    return readline->buffer;
}



