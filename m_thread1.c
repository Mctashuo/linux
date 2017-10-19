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

sem_t bin_sem,con_sem;
int num;

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;

    res = sem_init(&bin_sem,0,0);
    if(res != 0 ) {

        perror("semaphore initialization failed");
        exit(1);
    }
    res = sem_init(&con_sem,0,1);
    if(res != 0 ) {
        perror("semaphore initialization failed");
        exit(1);
    }
    res = pthread_create(&a_thread, NULL, consumer, NULL);
    if(res != 0) {
        perror("Thread creation failed");
        exit(1);

    }


    while(1) {

        sem_wait(&con_sem);
        num = rand()%1000;

        printf("number + 1 = : %d\n",++num);
        sem_post(&bin_sem);

        sleep(1);


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


        sem_wait(&bin_sem);

        printf("number - 1 = : %d\n",--num);
        sem_post(&con_sem);




    }

}
