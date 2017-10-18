#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

static volatile sig_atomic_t wait_child = 0;
static volatile sig_atomic_t wait_parent = 1;
static volatile int count = 0;

void parent_handler(int signo) {
    wait_child = 0;
}
void child_handler(int signo) {
    wait_parent = 0;
}
void tell_parent(pid_t ppid) {
    kill(ppid, SIGUSR1);
    wait_parent = 1;
    count++;
}
void tell_child(pid_t pid) {
    kill(pid, SIGUSR2);
    wait_child = 1;
    count++;
}

int main(int argc, char* const argv[]) {
    struct sigaction sigact;
    sigset_t sigset, oldset;

    // 阻塞所有信号
    sigfillset(&sigset);
    sigprocmask(SIG_SETMASK, &sigset, &oldset);
    // 创建父子进程
    pid_t pid;
    if ((pid = fork()) == -1) {
        return 1;
    } else if (pid != 0) {
        sigdelset(&sigset, SIGUSR1);
        bzero(&sigact, sizeof(sigact));
        sigact.sa_handler = parent_handler;
        sigaction(SIGUSR1, &sigact, NULL);
        int i = 0;
        for ( ; i < 5; ++ i) {
            FILE * f = fopen("out.txt","w");
            sleep(1);
            printf("parent add %d\n",count);

            fprintf(f,"%d", ++count);
            fclose(f);
            tell_child(pid);
            while (wait_child) {
                sigsuspend(&sigset);
            }
        }
    } else {
        sigdelset(&sigset, SIGUSR2);
        bzero(&sigact, sizeof(sigact));
        sigact.sa_handler = child_handler;
        sigaction(SIGUSR2, &sigact, NULL);
        pid_t ppid = getppid();
        int i = 0;
        for ( ; i < 5; ++ i) {
            while (wait_parent) {
                sigsuspend(&sigset);
            }
            FILE * f = fopen("out.txt","w");
            count++;
            sleep(1);
            printf("child  add %d\n",count);
            fprintf(f, "%d",count);
            fclose(f);
            tell_parent(ppid);
        }
        return 0;
    }

    return 0;
}
