#ifndef history_h
#define history_h

typedef struct history
{
    char* path;
}History;

typedef History* HistoryPtr;
void Write_history(char** parsed_line,HistoryPtr history);
void Read_history(HistoryPtr history);
void Again_line(int line_number, char* command, HistoryPtr history);//devuelve la linea correspondiente al again

#endif 