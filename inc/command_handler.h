

int ush_execute(command *cum);
int ush_launch(char **args, t_pid_list **head, char * name,t_terminal *termi);
int ush_pwd(command *cum);
int ush_exit(command *cum);
int ush_cd(command *cum);
int ush_env(command *cum);
int ush_export(command *cum);
int ush_unset(command *cum);
int ush_which(command *cum);
int ush_echo(command *cum);
int ush_fg(command *cum);
char ** search_directory(char ** argv,char ** full,bool *p);
