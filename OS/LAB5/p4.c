#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();

    switch (pid) {
        case -1:
            perror("fork failed");
            exit(1);

        case 0:
            printf("Child PID : %d\n", getpid());
            printf("Child exiting\n");
            exit(0);      //child terminates, hence waits for parent to re-accpet

        default:
            printf("Parent now running ps to show zombie...\n");    //parent does not wait, hence child turns into a zombie
            execlp("ps", "ps", "-elf", (char *)0);                  //child pid still present in table, hence even though in-active it is half alive/half dead aka ZOMBIE
            exit(1);        //parent terminates hence now child is taken up by init 
    }

    return 0;
}
