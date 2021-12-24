#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "history.h"

void Write_history(char* line, HistoryPtr history)
{
    char commands[9][100];// almacena los 10 comandos 
    

    FILE* file; 
    file = fopen(history->path,"r+");
    char bufer[100];// almacena la linea
    if (file == NULL)// saber abrio bien
    {
        printf("Error al abrir el fichero");
    }
    int index = 0;
    while (fgets(bufer,100,file) != NULL)// copia cada linea al array
    {
        strcpy(commands[index],bufer);
        index += 1;
    }
    if (index == 10)
    {
        if(fclose(file) != 0)// saber si cerro bien
        {
            printf("Error al cerrar el fichero");
        }

        file = fopen(history->path,"w");// vuelvo abrir con w para destruir contenido y copiar el contenido como va
        for (size_t i = 1; i <= 9; i++)
        {
            fputs(commands[i],file);
        }
        fputs(line,file);// comando actual
        if(fclose(file) != 0)// saber si cerro bien
        {
            printf("Error al cerrar el fichero");
        }  
    }
    else
    {
        fputs(line,file);
        if(fclose(file) != 0)// saber si cerro bien
        {
            printf("Error al cerrar el fichero");
        }
    }
       

}

void Read_history(HistoryPtr history)
{
    
    FILE* file; 
    file = fopen(history->path,"r+");
    char bufer[100];// almacena la linea
    if (file == NULL)// saber abrio bien
    {
        printf("Error al abrir el fichero");
    }
    int index = 0;
    while (fgets(bufer,100,file) != NULL)// copia cada linea al array
    {
        printf("%d: %s \n",index+1,bufer);
        index +=1;
    }
    if(fclose(file) != 0)// saber si cerro bien
    {
        printf("Error al cerrar el fichero");
    }  
}

void Again(int line_number, char* command, HistoryPtr history)
{
    
    FILE* file; 
    file = fopen(history->path,"r+");
    char bufer[100];// almacena la linea
    if (file == NULL)// saber abrio bien
    {
        printf("Error al abrir el fichero");
    }
    int index = 0;
    while (index < line_number)// copia cada linea al array
    {   
        if (index+1 == line_number)
        {
            fgets(command,100,file);
        }
        
        fgets(bufer,100,file);// avanzar
       
        index +=1;
    }
    if(fclose(file) != 0)// saber si cerro bien
    {
        printf("Error al cerrar el fichero");
    }  
}