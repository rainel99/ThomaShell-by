#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "parse.h"
#include "execute.h"
#include <string.h>


int main(int argc, char const *argv[])
{
    int status = 1;
    while (status)
    {
    
        printf("%s","ThomaShell-By $ ");
        char* line;
        size_t len = 0;
        size_t read = 0;
        read = getline(&line, &len, stdin);//dame la linea
        char** parsed_line = Split(line, read);//splitea la linea
        CommandPtr* commands = Parse(parsed_line);//convierte la linea en una lista de comandos
        bultin_command(commands);
        status = Execute(commands);
        free(line);
        free(parsed_line);
        free(commands);
    }    
    return 0;
}




