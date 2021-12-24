#ifndef execute_h
#define execute_h
#include "command.h"
#include <unistd.h>
#include <sys/types.h>

int Execute(CommandPtr* parsed_line);
pid_t* GrowChild_pids(pid_t* child_pids, int child_pidtt_count);


#endif 

