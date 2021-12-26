#include <stdlib.h>
#include "parse.h"
#include <stdio.h>
#include <string.h>
#include "command.h"


int index_buffer;
char** Split(char* line, int read)
{
    int count = 0;
    int word = 1;

    if(line[0] == ' ')
        word = 0;


    for (size_t i = 0; i < read; i++)
    {
        if(line[i] == '#')
        {
            if(i == 0)
                word = 0;
            break;
        }
        if(line[i] == ' ')
        {
            if(word)
                count++;
            
            word = 0;
        }
        else
            word = 1;
    }
    if(word)
        count++;
    word = 1;

    if(line[0] == ' ')
        word = 0;
    char* buffer = calloc(1024, sizeof(char));
    index_buffer = 0;
    char** parsed_line = malloc((count + 1) * sizeof(char*));
    int index_parsed_line = 0;
    for (size_t j = 0; j < read; j++)
    {
        if(line[j] == '\n')
            continue;
        if(line[j] == ' ' || line[j] == '#')
        {
            if(word)
            {
                parsed_line[index_parsed_line] = buffer;
                index_parsed_line++;
                buffer = calloc(1024, sizeof(char));
                index_buffer = 0;
            }
            if(line[j] == '#')
                break;
            word = 0;
        }
        else
        {
            buffer[index_buffer] = line[j];
            index_buffer++;
            word = 1;
        }
    }

    if(word)
        parsed_line[index_parsed_line] = buffer;


    parsed_line[count] = NULL;//para saber donde parar
    return parsed_line;
}
 

CommandPtr* Parse(char** parsed_line)
{

    if(parsed_line[0] == NULL)
        return NULL;
    /*Crea una lista con cada uno de los comandos y sus argumentos*/
    int command_numb = 1;
    int i = 0;
    while (parsed_line[i] != NULL)
    {
        if(strcmp(parsed_line[i],"|") == 0 || strcmp(parsed_line[i],";") == 0)
            command_numb ++;
        if(strcmp(parsed_line[i],"&&") == 0 || strcmp(parsed_line[i],"||") == 0)
            command_numb = command_numb + 2;
        i++;    
    }
    CommandPtr* my_commands = calloc((command_numb + 1) , sizeof(CommandPtr));
    my_commands[command_numb - 1] = NULL;
    //contar los argumentos de cada funcion
    int temp = 1;
    int k = 0;//moverme dentro de los comandos -> k
    i = 0;
    my_commands[0] = malloc(sizeof(Command));
    init(my_commands[0]);
    while(parsed_line[i] != NULL)
    {
        if(strcmp(parsed_line[i],"|") == 0 || 
           strcmp(parsed_line[i],">") == 0 || 
           strcmp(parsed_line[i],">>")== 0 || 
           strcmp(parsed_line[i],"<") == 0 || 
           strcmp(parsed_line[i],";") == 0 ||
           strcmp(parsed_line[i],"&&") == 0 ||
           strcmp(parsed_line[i],"||") == 0
           )
        {
            if(strcmp(parsed_line[i],">") == 0)
            {
                my_commands[k]->gd = calloc(1024, sizeof(char));
                my_commands[k]->gd = parsed_line[i + 1];
                i++;
            }
            if(strcmp(parsed_line[i],"<") == 0)
            {
                my_commands[k]->ld= malloc(1024* sizeof(char));
                my_commands[k]->ld = parsed_line[i + 1];
                i++;
            }
            if(strcmp(parsed_line[i],">>") == 0)
            {
                my_commands[k]->gd_append = malloc(1024* sizeof(char));
                
                my_commands[k]->gd_append = parsed_line[i + 1];
                i++;
            }
            temp++;
            if(strcmp(parsed_line[i], "|") == 0)
            {   
                my_commands[k]->po = 1;
                my_commands[k]->arguments = malloc((temp)* sizeof(char*));
                k++;
                my_commands[k] = malloc(sizeof(Command));
                init(my_commands[k]);
                my_commands[k]->pi = 1;
                temp = 1;
                i++;
            }
            if(strcmp(parsed_line[i], ";") == 0)
            {
                my_commands[k]->arguments = malloc((temp)* sizeof(char*));
                k++;
                my_commands[k] = malloc(sizeof(Command));
                init(my_commands[k]);
                temp = 1;
                i++;
            }
            if(strcmp(parsed_line[i],"||") == 0)
            {
                my_commands[k]->arguments = malloc((temp)* sizeof(char*));
                k++;
                my_commands[k] = malloc(sizeof(Command));
                init(my_commands[k]);
                temp = 2;
                my_commands[k]->arguments = malloc((temp)* sizeof(char*));
                my_commands[k]->arguments[0] = parsed_line[i];
                k++;
                my_commands[k] = malloc(sizeof(Command));
                init(my_commands[k]);
                temp = 1;
                i++;
            }
            if(strcmp(parsed_line[i],"&&") == 0)
            {
                my_commands[k]->arguments = malloc((temp)* sizeof(char*));
                k++;
                my_commands[k] = malloc(sizeof(Command));
                temp = 1;
                init(my_commands[k]);
                my_commands[k]->arguments = malloc((temp)* sizeof(char*));
                my_commands[k]->arguments[0] = parsed_line[i];
                k++;
                my_commands[k] = malloc(sizeof(Command));
                init(my_commands[k]);
                temp = 1;
                i++;
            }
        }
        else
        {
            temp++;
            i++;
        }
    }

    my_commands[k]->arguments = malloc((temp)*sizeof(char*));
    k = 0;
    i = 0;
    int j = 0;
    int ang = 0;
    while(parsed_line[i] != NULL)
    {
        if( strcmp(parsed_line[i],"<") == 0 || 
            strcmp(parsed_line[i],">") == 0 || 
            strcmp(parsed_line[i],"|") == 0 || 
            strcmp(parsed_line[i],">>")== 0 ||
            strcmp(parsed_line[i],";") == 0 ||
            strcmp(parsed_line[i],"&&") == 0 ||
            strcmp(parsed_line[i],"||") == 0)
        {
            if(strcmp(parsed_line[i],">") == 0)
            {
                ang = 1; 
                my_commands[k]->arguments[j] = NULL;//agrego null al final de cada lista de argumentos
                j = 0;
            }
            if(strcmp(parsed_line[i],">>") == 0)
            {
                ang = 1;
                my_commands[k]->arguments[j] = NULL;//agrego null al final de cada lista de argumentos
                j = 0;
            }
            if(strcmp(parsed_line[i],"<") == 0)
            {
                ang = 1;
                my_commands[k]->arguments[j] = NULL;//agrego null al final de cada lista de argumentos
                j = 0;
            }
            if(strcmp(parsed_line[i],"|") == 0)
            {
                if(ang == 0)
                {
                    my_commands[k]->arguments[j] = NULL;//agrego null al final de cada lista de argumentos
                }
                ang = 0;
                j = 0;
                k++;
            }
            if(strcmp(parsed_line[i],";") == 0)
            {
                if(ang == 0)
                {
                    my_commands[k]->arguments[j] = NULL;//agrego null al final de cada lista de argumentos
                }
                ang = 0;
                j = 0;
                k++;
            }
            if(strcmp(parsed_line[i],"||") == 0)
            {
                if(ang == 0)
                {
                    my_commands[k]->arguments[j] = NULL;//agrego null al final de cada lista de argumentos
                }
                ang = 0;
                j = 0;
                k++;
                my_commands[k]->arguments[1] = NULL;
                k++;
            }
            if(strcmp(parsed_line[i],"&&") == 0)
            {
                if(ang == 0)
                {
                    my_commands[k]->arguments[j] = NULL;//agrego null al final de cada lista de argumentos
                }
                ang = 0;
                j = 0;
                k+=2;
                my_commands[k]->arguments[1] = NULL;
            }
        }
        else
        {
            if(ang == 0)
            {
                my_commands[k]->arguments[j] = parsed_line[i];
                j++;
            }
        }
        i++;
    }
    if(ang == 0)
        my_commands[k]->arguments[j] = NULL;
    
    return my_commands;
        
}

void bultin_command(CommandPtr* commands)
{
    if(commands == NULL)
        return;
    int i = 0;//moverse por los comandos
    char* cd = "cd";
    while (commands[i] != NULL)
    {
        if(strcmp(commands[i]->arguments[0],"cd") == 0 ||
           strcmp(commands[i]->arguments[0],"exit") == 0 ||
           strcmp(commands[i]->arguments[0],"history") == 0 ||
           strcmp(commands[i]->arguments[0],"again") == 0 ||
           strcmp(commands[i]->arguments[0],"true") == 0 || 
           strcmp(commands[i]->arguments[0],"false") == 0 || 
           strcmp(commands[i]->arguments[0],"||") == 0 ||
           strcmp(commands[i]->arguments[0],"help") == 0 ||
           strcmp(commands[i]->arguments[0],"&&") == 0)
        {
            commands[i]->built_in = 1;
        }
        i++;
    }
    
}

