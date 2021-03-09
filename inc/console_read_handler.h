#include "termios.h"

#define BUFFER_SIZE  512
#define SIG_KILLS 127
/**************SPECIAL_CEYBOARD*************************/
#define RETURN 13
#define DELETE 127
#define SPACE 32
#define TAB 9
#define CONTROL_C 3
#define CONTROL_Z 26
#define CONTROL_D 4
#define NEW_LINE 10
/**************ARROWS*************************/
#define M_RIGHT 67
#define M_LEFT 68
#define ARROW_UP 65
#define ARROW_DOWN 66
/**************BACKSPACE*************************/
#define CLEARE_STR 
#define MX_BACKSPACE(void) mx_printstr("\033[D \b")
/**************DEFAULT_STRING*************************/
#define ERROR_DENIED "u$h: Permission denied:%s\n"
#define ERROR_FOUND "u$h: command not found: %s\n"
#define SUSPENDED "\nu$h: suspended %s\n"
#define FG_JOB "fg: no current job\n"
#define FG_CONTINUE "[%d] + continued %s\n"
#define HAVE_JOBS "\nu$h: you have suspended jobs.\n"

typedef struct s_mouse t_mouse;

struct s_mouse{
    int begin;
    int position;
    int max;
};

typedef struct s_str t_str;

struct s_str{
    t_mouse *mouse;
    bool status;
    char *buffer;
    int position;
    int signal;
    bool c_c;
    bool c_z;
    bool c_d;
};

typedef struct s_terminal t_terminal;
struct s_terminal{
    struct termios terminal;
    struct termios seve_atribut_terminal;
    pid_t our_pgrp;
     bool found_file;
};


typedef struct args args;
struct args
{
    int argc;
    char** argv;
};
args *create_args(int argc, char** argv);
typedef struct s_pid_list t_pid_list;

struct s_pid_list{
    pid_t pid;
    int number;
    t_pid_list *next;
    char * parameters;
};
typedef struct command command;
struct command
{
    args* master;
    t_pid_list *list_pid;
    char* name;
    char** parameters;
    int param_length;
    int status;
    t_terminal *terminal;
    char * full_command;
   
};
command *create_command(char *name, char **parameters, int param_length, args* master);
command *command_parser(char *line, args* master, int status);
char **echo_split(char *line);
char **prime_split(char *line);
char **custom_split(char *str);
char** create_unix_args(char **argv, int param);
t_terminal *terminal_begin();
void reset_input_mode(t_terminal *termi);
char *console_read_line(t_str * readline);
void clear_ush(char *line, t_terminal *termi, t_str *readline);
t_str * create_t_str();
void control_arrow(char ch,t_mouse *mouse);
void ush_create_pid(t_pid_list **head,pid_t pid);
void pop_pid(t_pid_list **head);
