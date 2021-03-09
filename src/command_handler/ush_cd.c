#include "../../inc/main_dependecy.h"
static void mx_setpwd(char *arg)
{
    if (mx_strlen(arg) != 1 && arg[mx_strlen(arg) - 1] == '/')
        arg[mx_strlen(arg) - 1] = '\0';
    setenv("PWD", arg, 1);
}
static int mx_find_flag(char *flags, char *arg)
{
    int flag = 0;

    for (int i = 0; i < (int)strlen(flags); i++)
    {
        for (int y = 1; y < (int)strlen(arg); y++)
        {
            if (arg[y] == flags[i])
            {
                if (i + 1 > flag)
                    flag = i + 1;
                break;
            }
        }
    }
    return flag;
}

static char *previous_dir( int flag) {
    char *prev_dir = NULL;

    if (flag != 1)
        prev_dir = mx_strdup(getenv("OLDPWD"));
    else
        prev_dir = mx_strdup(getenv("PWD"));
    for (int i = mx_strlen(prev_dir) - 1; i >= 0; i--) {
        if (prev_dir[i] == '/') {
            prev_dir[i] = '\0';
            break;
        }
        prev_dir[i] = '\0';
    }
    if (mx_strlen(prev_dir) == 0) {
        mx_strdel(&prev_dir);
        prev_dir = mx_strdup("/");
    }
    return prev_dir;
}
static char *absolute_path(char *path) {
    char *tmp = NULL;
    char *value = NULL;

    if (mx_strcmp(getenv("PWD"), "/") != 0) {
        tmp = mx_strjoin(getenv("PWD"), "/");
        value = mx_strjoin(tmp, path);
        mx_strdel(&tmp);
    }
    else
        value = mx_strjoin("/", path);
    return value;
}
static int mx_file_exist(char *path) {
    struct stat *st = (struct stat*) malloc(sizeof (struct stat));
    int flag = 0;

    if ((lstat(path, st) != -1))
        flag = 1;
    if (st != NULL) {
        free(st);
        st = NULL;
    }
    return flag;
}
static int cd_print_error(char *path,  char *value) {
   // mx_setenv_ush(ush->pwd, ush);
    if (mx_file_exist(path) == 0)
        fprintf(stderr, "cd: no such file or directory: %s\n", path);
    else
        fprintf(stderr, "cd: not a directory: %s\n", path);
    mx_strdel(&value);
    return 1;
}
static int create_new_path(char **tokens, char *path,  int flag) {
    char *value = NULL;

    for (int y = 0; tokens[y] != NULL; y++) {
        if (mx_strcmp(tokens[y], "..") == 0)
            value = previous_dir( flag);
        else if (mx_strcmp(tokens[y], ".") == 0) {
            if (flag != 1)
                value = mx_strdup(getenv("OLDPWD"));
            else
                value = mx_strdup(getenv("PWD"));
        }
        else{
            value = absolute_path(tokens[y]);
        }
       // printf("%s\n", value);

        if (chdir(value) != -1){
            mx_setpwd(value);
            //printf("%s\n", value);
        }
        else
            return cd_print_error(path, value);
        mx_strdel(&value);
    }
    return 0;
}

static int mx_make_path(char *path, int flag) {
    char **tokens = mx_strsplit(path, '/');
    char *pwd = mx_strdup(getenv("PWD"));
    //printf("%s\n", pwd);
    int ret = 0;

   //ush->pwd = mx_strdup(ush->pwd_l);
    if (path[0] == '/') {
        chdir("/");
       mx_setpwd("/");
    }
    if (tokens != NULL)
        ret = create_new_path(tokens, path, flag);
   // printf("%s\n", pwd);
    setenv("OLDPWD", pwd, 1);
    mx_del_strarr(&tokens);
    mx_strdel(&pwd);
    return ret;
}
static int build_path(char *path, int flag) {
    int ret = 0;
    char *tmp = mx_strdup(path);
    
    int link = mx_check_symlink(&tmp, flag, 1);

    if (flag == 2 && link == 1) {
        fprintf(stderr, "cd: not a directory: %s\n", path);
       
        ret = 1;
    }
    else if (mx_strcmp(tmp, "-") == 0) {
        if (getenv("OLDPWD") != NULL){
            char *temp = mx_strdup(getenv("PWD"));
            mx_setpwd(getenv("OLDPWD"));
            setenv("OLDPWD", temp, 1);
            mx_strdel(&temp);

        }
        else {
            fprintf(stderr, "ush: cd: OLDPWD not set\n");
            ret = 1;
        }
    }
    else
        ret = mx_make_path(tmp, flag);
    mx_strdel(&tmp);
    return ret;
}
int ush_cd(command *cum)
{
    int stop = 0;
    int flag = 0;
    int len = mx_char_array_length(cum->parameters);
    if (len == 1 || (mx_strcmp(cum->parameters[1], "--") == 0 && len == 2))
    {
        setenv("OLDPWD", getenv("PWD"), 1);
        mx_setpwd(getenv("HOME"));
        chdir(getenv("HOME"));
    }
    else
    {
        for (int i = 1; i < len; i++)
        {
            if (mx_strcmp(cum->parameters[i], "--") == 0)
            {
                stop = 3;
                continue;
            }
            if (stop == 0 && cum->parameters[i][0] == '-')
            {
                if ((flag = mx_find_flag("Ps", cum->parameters[i])) > 0)
                    continue;
            }
            return build_path(cum->parameters[i], flag);
        }
        
    }
    
    return 0;
}
