#include "../../inc/main_dependecy.h"

static void tilde_replace(char **inp, char *sub, char *rep) {
    char *tmp = mx_strdup(*inp);

    mx_strdel(inp);
    *inp = mx_replace_substr(tmp, sub, rep);
    mx_strdel(&tmp);
}
void mx_tilde_check(char ** str){
    char * home = strdup(getenv("HOME"));
    char* pwd = strdup(getenv("PWD"));
    char * oldpwd = strdup(getenv("OLDPWD"));
    if (mx_isalpha((*str)[1]))
        tilde_replace(str, "~", "/Users/");
    else if ((*str)[1] == '/' || (*str)[1] == '\0')
        tilde_replace(str, "~", home);
    else if ((*str)[1] == '+' && ((*str)[2] == '/' || (*str)[2] == '\0'))
        tilde_replace(str, "~+", pwd);
    else if ((*str)[1] == '-' && ((*str)[2] == '/' || (*str)[2] == '\0')) {
        tilde_replace(str, "~-", oldpwd);
    }
    mx_strdel(&home);
    mx_strdel(&pwd);
    mx_strdel(&oldpwd);
}
