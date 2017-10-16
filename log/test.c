#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include"m_log.h"
int main(int argc,char **argv)
{
    writeToFile(LOG_INFO,"log.txt","program end\n");
    FILE *f;
    f = fopen("not here","r");
    if(!f)
    {

        writeToFile(LOG_ERR,"log.txt","oops - No such file or directory!\n");
    }
    if(rmdir("test") != 0)
    {
        writeToFile(LOG_ERR,"log.txt","oops - delete fail\n");
    }
    writeToFile(LOG_INFO,"log.txt","program begin\n");
    return 0;
}
