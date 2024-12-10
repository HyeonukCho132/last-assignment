#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>

#include "ls_command.h"

void my_ls(void){
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return;
    } else {
        while ((entry = readdir(dir)) != NULL) {
            if(entry->d_type == DT_DIR){
                printf("%s/\n", entry->d_name);
            }
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);

}