#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"


void writeToFile(int priority,char * program_name ,char * filename,char * message)
{
    FILE * out;
    out = fopen(filename,"a+");

    time_t timeval;
    (void)time(&timeval);
    fprintf(out,"priority: %d time: %s %s %s ",priority,ctime(&timeval),program_name,message);
    fclose(out);
    
}



