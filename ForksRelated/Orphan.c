//? Write a C program to create a Orphan Process

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    pid_t pid = fork();
    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }
    else if (pid == 0){
        sleep(5);
        printf("Child Process (orphan)");
        printf("Child Process PID : %d", getpid());
        printf("New Parent PID : %d", getppid());
    }
    else {
        printf("Parent Process");
        printf("Parent Process PID : %d", getpid());
        printf("Child Process PID : %d", pid);
        printf("Parent Terminating...");
        exit(0);
    }
}