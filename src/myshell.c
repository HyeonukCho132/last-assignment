#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ls_command.h"
#include "cat_command.h"

#define MAX_LINE 80
#define MAX_ARGS 10

int main()
{
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while (1)
    { //prompt
        printf("myshell> ");

        //read command
        fgets(input, MAX_LINE, stdin);
       

        //tokenize input
        token = strtok(input, " \n\t");
        int i = 0;
        while(token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL;

        if(argv[0]==NULL){ // empty command
            continue;
        }

        if(strcmp(argv[0], "exit") == 0) {
            printf("Goodbye~\n");
            exit(0);
        } else if (strcmp(argv[0], "cd") == 0){
            chdir(argv[1]);

        } else if (strcmp(argv[0], "pwd") == 0){
            getcwd(input, MAX_LINE);
            printf("%s\n", input);
        } else if (strcmp(argv[0], "ls") == 0){
            my_ls();
        } else if (strcmp(argv[0], "cat") == 0){
            // your command
            my_cat(argv[1]);
        }else {
            if (access(argv[0], X_OK) == 0) {
                pid_t pid = fork();

                if(pid == -1) {
                    //fork 실패
                    perror("fork failed");
                    exit(1);
                }
                else if(pid == 0){
                    //자식 프로세스에서 외부 명령어 실행
                    if(execv(argv[0], argv) == -1) {
                        //execv 실패 시
                        perror("command not found");
                        exit(1);
                    }
                }
                else{
                    wait(NULL);
                }
            }else{
                printf("command not found: %s\n", argv[0]);
            }
        }
    }
    

    return 0;
}