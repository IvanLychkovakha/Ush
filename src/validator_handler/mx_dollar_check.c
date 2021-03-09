#include "../../inc/main_dependecy.h"


static char *dollar_change(int len, char **input) {
    char *variable = NULL;

    if ((*input)[1] == '{' && (*input)[len - 1] == '}') {
        variable = mx_strnew(len - 1);
        for (int y = 2, x = 0; y < len - 1; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 3] = '=';
        variable[len - 2] = '\0';
    }
    else {
        variable = mx_strnew(len + 1);
        for (int y = 1, x = 0; y < len; y++, x++)
            variable[x] = (*input)[y];
        variable[len - 1] = '=';
        variable[len] = '\0';
    }
    return variable;
}

static void insert_str(char **in, int j, char *var) {
    int x = 0;
    extern char **environ;

    mx_strdel(in);
    (*in) = mx_strnew(mx_strlen(environ[j]) - mx_strlen(var) + 1);
    x = 0;
    for (int y = mx_strlen(var); y <= mx_strlen(environ[j]); y++)
        (*in)[x++] = environ[j][y];
    (*in)[x] = '\0';
}

void mx_dollar_check(int len, char **in) {
    char *var = NULL;
    extern char **environ;
    int flag = 0;

    var = dollar_change(len, in);
    for (int j = 0; environ[j]!= NULL; j++) {
        if (strstr(environ[j], var) != NULL && environ[j][0] == var[0]) {
            flag = 1;
            insert_str(in, j, var);
            break;
        }
    }
    mx_strdel(&var);
    if (flag == 0) {
      
        mx_strdel(in);
        (*in) = mx_strdup(" ");
       
    }
}
