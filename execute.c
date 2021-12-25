#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "execute.h"
#include "command.h"
#include <string.h>
#include "history.h"
#include "parse.h"

int counting_commands(CommandPtr* mycommands){
    int commands_count = 0;

    while(mycommands[commands_count] != NULL){
        commands_count++;
    }
    return  commands_count;
}

int counting_pipes(CommandPtr* mycommands){
    int pipes_count = 0;
    int position = 0;

    while(mycommands[position] != NULL)
    {
        if(mycommands[position]->pi > 0)
            pipes_count++;

        position++;
    }

    return pipes_count;
}

int Execute(CommandPtr* mycommands, HistoryPtr history){
    if(mycommands == NULL)
        return 1;

    int commands_count = counting_commands(mycommands);
    int pipes_count = counting_pipes(mycommands);
    
    if(mycommands[0]->built_in == 1)
    {
        if(strcmp(mycommands[0]->arguments[0],"cd") == 0)
        {
            chdir(mycommands[0]->arguments[1]);
            return 1;
        }
        if(strcmp(mycommands[0]->arguments[0],"exit") == 0)
        {
            exit(0);
        }
    }


    int position = 0;
    int ** pipes_array;

    pipes_array=(int**) malloc((pipes_count)*sizeof(int*));
    for(int i=0; i < pipes_count;i++) {
        pipes_array[i] = (int *) malloc(2 * sizeof(int));
        pipe(pipes_array[i]);
    }
    while(mycommands[position] != NULL){
        CommandPtr actual_commands = mycommands[position];
        //zona de built int
        if(strcmp(mycommands[position]->arguments[0],"history") == 0)//se cambiaron los position, si se pone 0 en lugar de position, solo funciona cuando esta al inicio d la linea
        {
            Read_history(history);
            position++;
            continue;
        }
        if(strcmp(mycommands[position]->arguments[0],"again") == 0)
        {

            int line_number = atoi(mycommands[position]->arguments[1]);
            char* line = malloc(sizeof(char));
            Again(line_number,line,history); 
            int read = strlen(line);
            Write_history(line,history);
            char** parsed_line = Split(line, read);//splitea la linea
            CommandPtr* commands = Parse(parsed_line);//convierte la linea en una lista de comandos
            bultin_command(commands);
            Execute(commands,history);
            free(line);
            free(parsed_line);
            free(commands);
            position++;
            continue;
        }
        if(fork() == 0){
            if(pipes_count > 0){
                if(position == 0){
                    close(pipes_array[position][0]);
                    dup2(pipes_array[position][1], 1);

                }
                else if(position == pipes_count){
                    close(pipes_array[position - 1][1]);
                    dup2(pipes_array[position - 1][0], 0);
                    close(pipes_array[position - 1][0]);
                }
                else{
                 close(pipes_array[position][0]);
                   close(pipes_array[position - 1][1]);
                    dup2(pipes_array[position - 1][0], 0);
                    dup2(pipes_array[position][1],1);
                }
            }
            if(actual_commands->ld != NULL)
            {
                int fd_In = open(actual_commands->ld, O_RDONLY);
                if(fd_In == -1)
                    exit(-1);
                dup2(fd_In, STDIN_FILENO);
                close(fd_In);
            }
            if(actual_commands->gd != NULL)
            {
                int fd_Out = creat(actual_commands->gd, 0644);
                if(fd_Out == -1)
                    exit(-1);
                dup2(fd_Out, STDOUT_FILENO);
                close(fd_Out);
                if(actual_commands->arguments[0] == NULL)
                    exit(-1);
            }
            if(actual_commands->gd_append != NULL){
                int fd_Out_End = open(actual_commands->gd_append, O_CREAT | O_WRONLY | O_APPEND,S_IRWXU | S_IRWXG | S_IRWXO);
                    if(fd_Out_End == -1)
                        exit(-1);
                dup2(fd_Out_End, STDOUT_FILENO);
                close(fd_Out_End);
            }
            int ex = execvp(actual_commands->arguments[0], actual_commands->arguments);
            if(ex == -1) 
            {
                printf("error al ejecutar: %s\n", actual_commands->arguments[0]);
            }

            exit(ex);
        }
        else{
            if(position < pipes_count){
                close(pipes_array[position][1]);
            }
            wait(NULL);
            //waitpid()
        }
        position++;
    }
    //aqui
    return  1;
}

