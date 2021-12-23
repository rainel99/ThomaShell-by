#ifndef command_h
#define command_h
typedef struct command
{
    char** arguments;
    int built_in;
    int po;
    int pi;
    char* ld;
    char* gd;
    char* gd_append;
}Command;

typedef Command* CommandPtr;

void init(CommandPtr command);

#endif