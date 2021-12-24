#ifndef parse_h
#define parse_h
#include "command.h"

char** Split(char* line, int read);
CommandPtr* Parse(char** parsed_line);
void bultin_command(CommandPtr* commands);

#endif 