#include "../../inc/main_dependecy.h"



int ush_fg(command *cum){
    
 if(cum->list_pid == NULL){   
        fprintf(stdout,FG_JOB); 
        return  1;
       }
    pid_t w_s;
    int w_st;
    int status = 1;

    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(1, cum->list_pid->pid);
    fprintf(stdout, FG_CONTINUE, cum->list_pid->number, cum->list_pid->parameters);
    kill(cum->list_pid->pid,SIGCONT);
   w_s = waitpid(cum->list_pid->pid, &w_st, WUNTRACED);
     if(w_st == 0){
        pop_pid(&(cum->list_pid));
        status = WEXITSTATUS(w_st);
      }else {
        fprintf(stdout,SUSPENDED,cum->list_pid->parameters);
        if(WIFSTOPPED(w_st)) {
          if(WSTOPSIG(w_st) == 18)
            status = 146;
          else
            status = WSTOPSIG(w_st);
      }
      }
    tcsetpgrp(1, cum->terminal->our_pgrp);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    return status;
}

