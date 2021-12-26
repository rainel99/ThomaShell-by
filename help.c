#include <stdio.h>
#include <string.h>
int help(char* arg)
{
    if(strcmp(arg,"") == 0)
    {
        printf(
            "Segundo Proyecto de Sistemas Operativos, Shell\n"
            "Integrantes:\n"
            "Lazaro Alejandro Castro Arango C213\n"
            "Rainel Fernández Abreu C212\n"
            "Lista de funcionalidades:\n"
            ">basic (3 puntos)\n"
            ">multipipes (1 punto)\n"
            ">space (0.5 puntos)\n"
            ">history (1 punto)\n"
            ">chain (0.5 puntos)\n"
            ">help (1 punto)\n"
            "Total 7 puntos\n"
            "Comandos built-in\n"
            ">cd\n"
            ">exit\n"
            ">help\n"
            ">history\n"
            ">again\n"
            ">true\n"
            ">false\n"
            "Explicación de la implementación del Shell:\n"
            "En shell.c se maneja el ciclo infinito que se encarga de leer y ejecutar procesos hasta que se llame a la función\n"
            "exit. En el ciclo infinito que corre dentro de shell.c primero se imprime (ThomaShell-By $ ), nombre de nuestro\n"
            "proyecto. Luego de esto se llama a función get_line para tomar la línea de consola, después se escribe dicha línea\n"
            "en el archivo history.txt donde se guardan los 10 últimos comandos ejecutados. Hecho esto se invoca la función Split\n"
            "donde se quitan los espacios innecesarios entre comandos y argumentos y este devuelve una lista con las palabras \n"
            "de dicha línea, para con esta hacer el llamado al método Parse que conformará una lista de comandos para ejecutar,\n"
            "esta lista de comandos es una lista de struct que fue creada por nosotros para facilitar el trabajo con los procesos\n"
            "y encapsular todo lo que necesitamos en una estructura. Dichos comandos tienen una lista con los argumentos de cada uno\n"
            "de estos, donde el primero de los argumentos es el nombre del mismo, tiene variables para saber si hay que redireccionar\n"
            "la salida o si tiene pipes delante o después de este.\n"
            "Culminado este paso se llama a la función Execute que se encuentra en el archivo execute.c, donde con la lista de los\n"
            "comandos listos para ejecutar primero; contamos la cantidad de pipes que tenemos en lista dada asi como la cantidad de\n"
            "comandos de esta, luego verificamos que el comando a ejecutar sea cd o exit, para ejecutarlos antes de hacer fork. Luego\n"
            "recorremos la lista de los comandos y comprobamos si el que tenemos actualmente sea built?in o no, después hacemos fork\n"
            "para crear un nuevo proceso donde correrá el proceso hijo, se comprueba si hay > , < , >> , ; 0 | para en caso afirmativo\n"
            "redireccionar la salida o entrada de estos procesos; se ejecuta el proceso y en el padre se espera o no por este. Este método\n"
            "devuelve un int que será la condicional de ejecución del shell.\n"

        );
    }
    return 1;
}