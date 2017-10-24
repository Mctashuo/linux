#include <unistd.h>
/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char **argv)
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;

    char work_area[256];
    fgets(work_area,256,stdin);

    char * temp = strtok(work_area," ");
    char  params[3][128];
    for(int i = 0;temp != NULL;i++) {
        
        strcpy(params[i] , temp);
        temp = strtok(NULL," ");
        printf("%s\n",params[i]);

    }


    
/*  Create a socket for the client.  */ 
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client3");
        exit(1);
    }

/*  We can now read/write via sockfd.  */

    
    int block[1024 * 1024];
    memset(block,0,sizeof(block));
    write(sockfd, params, sizeof(params));
    int out,nread;

    char * file_name="index.html";

    if(file_name == NULL) {
        printf("error");
        exit(1);
    }

    out = open(file_name,O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);

    while((nread = read(sockfd,&block,sizeof(block))) > 0) {
        write(out,block,nread);
    }
        //sleep(1);
        
    close(sockfd);
    
    exit(0);
}
