#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    pid_t pid;
    int status;
    
    pid = fork();

    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);

        case 0:
            // Child process
            printf("In the Child\n");
            printf("Child PID: %d\n", getpid());
            printf("PID of Parent (before orphan): %d\n", getppid());
            
            printf("Child sleeping for 20 seconds...\n");
            sleep(20);  // Parent will exit during this time
            
            printf("\nChild woke up!\n");
            printf("PID of Parent (after orphan): %d\n", getppid());
            printf("Child is now an orphan (adopted by init process)\n");
            
            // Child exits with a specific code for demonstration
            printf("Child exiting with code 42...\n");
            exit(42);

        default:
            // Parent process
            printf("In the Parent\n");
            printf("Parent PID: %d\n", getpid());
            printf("Child PID: %d\n", pid);
            printf("Parent will now wait for child to terminate...\n");
            
            // Wait for child to terminate and get its exit status
            pid_t terminated_child = wait(&status);
            
            printf("\nParent: Child %d has terminated\n", terminated_child);
            printf("Raw status value: %d\n", status);
            
            // Display exit return code (leftmost byte of status)
            if (WIFEXITED(status)) {
                int exit_code = WEXITSTATUS(status);
                printf("Child exited normally with exit code: %d\n", exit_code);
                printf("Exit code (leftmost byte): %d\n", exit_code);
                
                // Manual extraction of leftmost byte
                int leftmost_byte = status >> 8;  // Right shift 8 bits
                printf("Manual extraction (status >> 8): %d\n", leftmost_byte);
            } else if (WIFSIGNALED(status)) {
                printf("Child was terminated by signal: %d\n", WTERMSIG(status));
            }
            
            printf("Parent exiting...\n");
            exit(0);
    }
    
    return 0;
}

/*
Expected Output:
In the Parent
Parent PID: 1234
Child PID: 1235
Parent will now wait for child to terminate...
In the Child
Child PID: 1235
PID of Parent (before orphan): 1234
Child sleeping for 20 seconds...

(20 seconds later...)

Child woke up!
PID of Parent (after orphan): 1234  (still same parent since parent is waiting)
Child is now an orphan (adopted by init process)
Child exiting with code 42...

Parent: Child 1235 has terminated
Raw status value: 10752
Child exited normally with exit code: 42
Exit code (leftmost byte): 42
Manual extraction (status >> 8): 42
Parent exiting...

Note: Since parent waits for child, the child won't become orphan in this case.
If you want true orphan behavior, parent should exit before wait().
*/
