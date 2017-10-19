/*************************************************************************
> File Name: m_thread.c
> Author: 
> Mail: 
> Created Time: 2017年10月19日 星期四 16时54分45秒
************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

void *consumer(void *arg);

int time_to_exit = 0;
int num;

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;


    res = pthread_create(&a_thread, NULL, consumer, NULL);
    if(res != 0) {
        perror("Thread creation failed");
        exit(1);

    }


    while(1) {
        if(time_to_exit ==0) {

            num = rand()%1000;

            printf("number + 1 = : %d\n",num+1);
            time_to_exit = 1;

        }
        else {
            sleep(1);

        }

    }

    res = pthread_join(a_thread, &thread_result);
    if( res != 0 ) {
        perror("Thread join failed");
        exit(1);
    }      
    exit(0);
}


void * consumer(void * arg) {

    while(1) {
        if(time_to_exit != 0) {

            printf("number - 1 = : %d\n",num-1);

            time_to_exit = 0;
        }
        else {
            sleep(1);

        }

    }

}
