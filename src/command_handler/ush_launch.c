#include "../../inc/main_dependecy.h"


static void reverse_terminal(t_terminal *termi){
        tcsetpgrp(1,termi->our_pgrp);
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);
}


int ush_launch(char **args, t_pid_list **head, char * name,t_terminal *termi)
{
  pid_t pid, wpid;
  int status;
  extern char** environ;
  signal(SIGINT, SIG_DFL);
  signal(SIGTSTP, SIG_DFL);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  if(!(termi->found_file)){
    fprintf(stderr, ERROR_FOUND, args[0]);
    return SIG_KILLS;
  }
  pid = fork();
  if (pid == 0) 
  {
    // Child process            
    setpgid(getpid(), getpid());
    tcsetpgrp(1,getpid());
     status =  execve(args[0], args, environ);
    if(status == -1)
    {
    fprintf(stderr, ERROR_DENIED, args[0]);
    return EXIT_FAILURE; 
    }
  } else if (pid < 0) 
  {
    perror("l$h");
  } else 
  {
    do{
      wpid = waitpid(pid, &status, WUNTRACED);
      if(WIFEXITED(status)){
        reverse_terminal(termi);
        return WEXITSTATUS(status);
      }else{
        if(WIFSIGNALED(status)){
          reverse_terminal(termi);
          return WTERMSIG(status);
        }else{
          if(WIFSTOPPED(status)){
            ush_create_pid(head,pid);
            (*head)->parameters = mx_strjoin("\0",mx_strdup(name));
            fprintf(stdout,SUSPENDED,(*head)->parameters);
            reverse_terminal(termi);
            if(18 == WSTOPSIG(status))
              return 146;
            return WSTOPSIG(status);
          }
        }
      }
      } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  tcsetpgrp(0,termi->our_pgrp);
  return 1;
}
