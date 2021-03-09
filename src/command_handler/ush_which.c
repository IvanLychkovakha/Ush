#include "../../inc/main_dependecy.h"
static int is_comm_rw(char *str) {
    char reserved_words[][5] = {"!", "{", "}", "time"};

    for (int i = 0; i < 4; i++) {
        if (strcmp(str, reserved_words[i]) == 0)
            return 1;
    }
    return -1;
}
static int mx_tolower(int c) {
    if (65 <= c && c <= 90)
        return (c + 32);
    else
        return c;
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
static int is_built(char *command) {
    if (strcmp("cd", command) == 0)
        return 1;
    if (strcmp("pwd", command) == 0)
        return 2;
    if (strcmp("echo", command) == 0)
        return 9;
    return 0;
}

static int mx_is_builtin(char *command) {
    int num = 0;
    char builtins[][20] = {"/usr/bin/cd", "/bin/pwd", "/usr/bin/env",
                           "ush", "export", "unset", "exit",
                           "/usr/bin/which", "/bin/echo"};

    for (int i = 0; i < mx_strlen(command); i++)
        command[i] = (char)mx_tolower(command[i]);
    if ((num = is_built(command)) == 0) {
        for (int i = 0; i < 10; i++) {
            if (strcmp(builtins[i], command) == 0) {
                num = i + 1;
            }
        }
    }
    return num;
}

static char *check_in_path(char *command, char **path) {
    char *command_p = NULL;

    for (int i = 0; i < mx_char_array_length(path); i++) {
        command_p = mx_strnew(mx_strlen(command) + mx_strlen(path[i]) + 1);
        mx_strcpy(command_p, path[i]);
        command_p = mx_strcat(command_p, "/");
        command_p = mx_strcat(command_p, command);
        if (mx_file_exist(command_p))
            break;
        mx_strdel(&command_p);
    }
    return command_p;
}
static void mx_free_void_arr(void **arr, int lines) {
    if (arr != NULL) {
        for (int i = 0; i < lines; i++) {
            free(arr[i]);
            arr[i] = NULL;
        }
        free(arr);
        arr = NULL;
    }
}
static char *mx_coomand_in_path(char *comm, char *str_path) {
    char **path = NULL;
    char *command_p = NULL;
    int paths = 0;
    int i = 0;

    if (str_path != NULL) {
        path = mx_strsplit(str_path, ':');
        paths = mx_char_array_length(path);
        if (strstr(str_path, "PATH=") != NULL) {
            for (; i < mx_strlen(path[0]) - 5; i++)
                path[0][i] = path[0][i + 5];
            path[0][i] = '\0';
        }
        if (mx_strcmp(comm, "/") != 0 && mx_get_char_index(comm, '/') == -1)
            command_p = check_in_path(comm, path);
        mx_free_void_arr((void **) path, paths);
    }
    if (command_p == NULL)
        command_p = mx_strdup(comm);
    return command_p;
}

static void check_builtin(char *input, int *ret_flag, int flag) {
    char *tmp = NULL;

    tmp = mx_coomand_in_path(input, getenv("PATH"));
    if (mx_is_builtin(tmp) != 0 && flag != 1) {
        printf("%s: shell built-in command\n", input);
        if (flag == 2 && strcmp(tmp, input) != 0)
            printf("%s\n", tmp);
    }
    else if (strcmp(tmp, input) != 0) {
        if (flag != 1)
            printf("%s\n", tmp);
    }
    else
        *ret_flag = 1;
    mx_strdel(&tmp);
}

static void check_command(char *input, int *ret_flag, int flag) {
    char **path = NULL;

    if (is_comm_rw(input) == 1)
        printf("%s: shell reserved word\n", input);
    else if (mx_get_char_index(input, '/') != -1) {
        path = mx_strsplit(getenv("PATH"), ':');
        for (int y = 0; y < mx_char_array_length(path); y++) {
            if (mx_get_substr_index(input, path[y]) != -1
                && mx_file_exist(input)) {
                if (flag != 1)
                    printf("%s\n", input);
                *ret_flag = 0;
                break;
            }
            *ret_flag = 1;
        }
        mx_free_void_arr((void**)path, mx_char_array_length(path));
    }
    else
        check_builtin(input, ret_flag, flag);
}

static int check_flag(char *input, int *flag) {
    for (int y = 1; y < mx_strlen(input); y++) {
        if (input[y] == 's' && *flag != 2)
            *flag = 1;
        else if (input[y] == 'a')
            *flag = 2;
        else {
            fprintf(stderr, "which: illegal option -- %c\nusage: which [-as] program ...\n", input[y]);
            return 1;
        }
    }
    return 0;
}

int ush_which(command *cum) {
    int flag = 0;
    int ret_flag = 0;

    if (mx_char_array_length(cum->parameters) == 1) {
        fprintf(stderr, "usage: which [-as] program ...\n");
        return 1;
    }
    for (int i = 1; i < mx_char_array_length(cum->parameters); i++) {
        if (strcmp(cum->parameters[i], "--") == 0)
            flag = 3;
        else if (cum->parameters[i][0] == '-' && flag < 3) {
            if ((ret_flag = check_flag(cum->parameters[i], &flag)) == 0)
                continue;
        }
        check_command(cum->parameters[i], &ret_flag, flag);
    }
    return ret_flag;
}
