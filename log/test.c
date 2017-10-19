#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include"m_log.h"
int main(int argc,char **argv)
{
    

    
    writeToFile(LOG_INFO,argv[0], "log.txt","program begin\n");
    FILE *f;
    f = fopen("not here","r");
    if(!f)
    {

        writeToFile(LOG_ERR,argv[0], "log.txt","oops - No such file or directory!\n");
    }
    if(rmdir("test") != 0)
    {
        writeToFile(LOG_ERR,argv[0], "log.txt","oops - delete fail\n");
    }
    writeToFile(LOG_INFO,argv[0], "log.txt","program end\n");
    return 0;
}
