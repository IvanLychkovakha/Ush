#include "../../inc/main_dependecy.h"


static char *  starr_in_str(char ** argv){
    char * par = mx_strdup(argv[0]);
    for(int i = 1; argv[i]; i++){
        par = mx_strjoin(par,argv[i]);
    }

    return par = mx_strjoin(par,"\0");
}


char ** search_directory(char ** argv,char ** full,bool *p){
    DIR *dir;
    struct dirent *entry;
    char* path = getenv("PATH");
    *full = starr_in_str(argv);

    if(path == NULL)
        return argv;

    char** paths = mx_strsplit(path, ':');
    for(int i = 0; paths[i] != NULL; i++){
        dir = opendir(paths[i]);
        if (!dir) {
            perror("l$h");
        }
        while ( (entry = readdir(dir)) != NULL) {
            if(mx_strcmp(entry->d_name,argv[0]) == 0){
                argv[0] = mx_strjoin("/",argv[0]);
                argv[0] = mx_strjoin(paths[i],argv[0]);
                closedir(dir);
                *p = true;
                return argv;
            }
        }
        closedir(dir);
    }
    *p = false;
    return argv;
}


