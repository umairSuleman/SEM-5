#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    pid_t pid;
    pid = fork();

    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);

        case 0:
            //Child process
            printf("In the Child\n");
            printf("Child PID: %d\n", getpid());
            printf("PID of Parent (before orphan): %d\n", getppid());
            
            printf("Child sleeping for 20 seconds...\n");
            sleep(20);  //Parent will exit during this time
            
            printf("\nChild woke up!\n");
            printf("PID of Parent (after orphan): %d\n", getppid());
            printf("Child is now an orphan (adopted by init process)\n");
            exit(0);
            break;  //Good practice even though unreachable

        default:
            //Parent process
            printf("In the Parent\n");
            printf("Parent PID: %d\n", getpid());
            printf("Child PID: %d\n", pid);
            printf("Parent will now exit, making child an orphan...\n");
            
            sleep(2);  //Small delay to ensure child prints first
            printf("Parent exiting...\n");
            exit(0);  //Parent exits while child is still sleeping
    }
    
    return 0; 
}
