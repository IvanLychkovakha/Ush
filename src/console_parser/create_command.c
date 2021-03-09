#include "../../inc/main_dependecy.h"

command *create_command(char *name, char **parameters, int param_length, args* master)
{
    command *cumm = (command *)malloc(sizeof(command));
    
    cumm->master = master;
    cumm->name = mx_strjoin("/bin/", name);
    cumm->param_length = param_length;
    cumm->parameters = (char **)malloc(sizeof(char *) * (cumm->param_length + 1));

    cumm->parameters[0] = mx_strdup(cumm->name);
    for (int i = 1; i < cumm->param_length; i++)
    {
        
        cumm->parameters[i] = mx_strdup(parameters[i]);
      
    }
    cumm->parameters[param_length] = NULL;
     return cumm;
}
