#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "parse.h"
#include "execute.h"
#include <string.h>
#include "history.h"

int main(int argc, char const *argv[])
{
    char filename[] = "history.txt";
    char* path_abs = realpath(filename, NULL);//me quedo con el path de la pc actual
    HistoryPtr history = malloc(sizeof(History));
    history->path = path_abs;

    int status = 1;
    while (status)
    {
    
        printf("%s","ThomaShell-By $ ");
        char* line;
        size_t len = 0;
        size_t read = 0;
        read = getline(&line, &len, stdin);//dame la linea
        if (memcmp("again",line,5) !=0 )// si la linea es diferente de again se guarda en history
        {
            Write_history(line,history);
        }
        char** parsed_line = Split(line, read);//splitea la linea
        CommandPtr* commands = Parse(parsed_line);//convierte la linea en una lista de comandos
        bultin_command(commands);
        // printf("%s\n",commands[0]->arguments[0]);
        // printf("%s\n",commands[1]->arguments[0]);
        // if(commands[0]->arguments[1] == NULL)
        //     printf("++\n");
        // printf("%d\n",commands[0]->built_in);
        status = Execute(commands,history);
        free(line);
        free(parsed_line);
        free(commands);
    }    
    return 0;
}




