#include "command.h"
#include <stdio.h>
//new .c para inicializar los comandos una vez creados.
void init(CommandPtr command)
{
    command->arguments = NULL;
    command->built_in = 0;
    command->gd = NULL;
    command->gd_append = NULL;
    command->ld = NULL;
    command->pi = 0;
    command->po = 0;
}