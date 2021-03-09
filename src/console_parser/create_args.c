#include "../../inc/main_dependecy.h"

args *create_args(int argc, char** argv)
{
    args* master = (args*) malloc(sizeof(args));

    master->argc = argc;
    master->argv = (char **)malloc(sizeof(char *) * (argc));

    for(int i = 0; i < argc; i++)
        master->argv[i] = mx_strdup(argv[i]);

    master->argv[argc] = NULL;

    return master;
}
