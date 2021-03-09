#include "../../inc/main_dependecy.h"




char ** create_unix_args(char **argv, int param){
    char ** new_argv = (char**) malloc ((param + 1) * sizeof(char*));
    for (int i = 0 ; i < param; i++){
        if (i == 0){
            new_argv[0] = strdup(argv[0] + 5);
        }
        else{
            new_argv[i] = strdup(argv[i]);
        }
    }
    new_argv[param] = NULL;
    
    return new_argv;
}

