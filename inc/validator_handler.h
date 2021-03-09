
bool is_bad_symbol(int ch);
void mx_tilde_check(char ** str);
void mx_dollar_check(int len, char **in);
int mx_atoi(const char *str);
int mx_check_symlink(char **arg, int flag, int link);
bool check_num_of_quots(char* str);
char** validate_semicolon(char* line);
char *mx_validate_questmark_with_dollar(char *line, int status);
