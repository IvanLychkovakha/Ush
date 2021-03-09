#include "../../inc/main_dependecy.h"

int (*builtin_func[]) (command *) = {
  &ush_cd,
  &ush_exit,
  &ush_env,
  &ush_export,
  &ush_unset,
  &ush_pwd,
  &ush_which,
  &ush_echo,
  &ush_fg
};

char *builtin_str[] = {
  "/bin/cd",
  "/bin/exit",
  "/bin/env",
  "/bin/export",
  "/bin/unset",
  "/bin/pwd",
  "/bin/which",
  "/bin/echo",
  "/bin/fg"
};

int ush_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}


int ush_execute(command *cum)
{
  int i;
  if (cum->name == NULL) 
    return 1;

  for (i = 0; i < ush_num_builtins(); i++) {
    if (mx_strcmp(cum->name, builtin_str[i]) == 0) {
      return (*builtin_func[i])(cum);
    }
  }
  cum->parameters = create_unix_args(cum->parameters, cum->param_length); // убераю /bin/
  cum->parameters = search_directory(cum->parameters, &(cum->full_command),&(cum->terminal->found_file));
  return ush_launch(cum->parameters,&cum->list_pid,cum->full_command,cum->terminal);
}
