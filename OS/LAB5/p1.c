#include <sys/types.h>    //for types like pid_t
#include <sys/wait.h>     //for wait function
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>        //stands for UNIX standard, has all the process control functions

int main(){    //always stick to int main() instead of void
    int pid = fork();
    int status;
    switch(pid){
        case -1 :    //fork failure case
            perror("fork failed");
            exit(1);
        case 0 :    //pid=0 when in child
            printf("Child running\n");
            break;
        default :   //pid is non zero when in parent
            wait(&status);
            printf("Parent running : Child completed with status %d\n", status);
    }
    return 0;
}
