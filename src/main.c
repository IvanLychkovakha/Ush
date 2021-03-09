#include "../inc/main_dependecy.h"

static void readline_status(bool *c, bool *z, bool *d){
    *c = false;
    *z = false;
    *d = false;
}

static void clear_cum(command **cum){

}

int main(int argc, char **argv)
{
    args *master = create_args(argc, argv);

    char *line;
    int status = 0;
    
    char *shlv = getenv("SHLVL");
    char *shlvl = mx_itoa(mx_atoi(shlv) + 1);
    t_str *readline = create_t_str();
    t_terminal  * termi = terminal_begin();
    termi->our_pgrp = getpgrp();
    tcsetattr(0, TCSAFLUSH, &(termi->terminal));
    t_pid_list *some_pid = NULL;
    setenv("SHLVL", shlvl, 1);
    int is_job = 0;
    do
    {
       signal(SIGINT, SIG_IGN);
       signal(SIGTSTP, SIG_IGN);
        tcsetattr(0,TCSANOW,&(termi->terminal));
        mx_printstr("u$h> ");
        line = console_read_line(readline);
        tcsetattr(0,TCSANOW,&(termi->seve_atribut_terminal));
         if (!(readline->c_d)){
             if(readline->c_c){
                readline_status(&readline->c_c,&readline->c_z,&readline->c_d);

                free(line);
                line = NULL;
                readline->buffer = malloc(sizeof(char)*BUFFER_SIZE);
             }else{
                if(check_num_of_quots(line))
                {
                    char **command_arr = validate_semicolon(line);
                    //x_print_strarr(command_arr, "\n");
                    free(line);
                    line = NULL;
                    
                    mx_printstr("\n");
                    for (int i = 0; command_arr[i] != NULL; i++)
                    {
                        if(mx_strlen(mx_del_extra_spaces(command_arr[i])) != 0)
                        {

                            command *cum = command_parser(command_arr[i], master,status);
                            cum->terminal = termi;
                            if(some_pid != NULL)
                                cum->list_pid = some_pid;
                            status = ush_execute(cum);
                            some_pid = cum->list_pid;
                            if(mx_strcmp("/bin/fg",cum->name) == 0)
                                is_job = 0;
                            free(command_arr[i]);
                            clear_cum(&cum);
                        }
                    }


                    readline->buffer = malloc(sizeof(char)*BUFFER_SIZE);
                    free(command_arr);
                    command_arr = NULL;
                }
                else
                {
                    mx_printerr("\nOdd number of quotes.\n");
                }
             }
             
         }else{
             if(some_pid != NULL){
                 is_job++;
                 if(is_job == 2){
                    clear_ush(line,termi,readline);
                    break;
                 }
                fprintf(stdout,HAVE_JOBS);
             }else {
                 while(some_pid != NULL){
                    pop_pid(&some_pid);
                 }
                clear_ush(line,termi,readline);
                break;
             }
         }
        

    } while (true);

    return status;
}
