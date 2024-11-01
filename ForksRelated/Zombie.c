//? Write a C program to create a Zombie Process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid = fork();
    if (pid == 0){
        printf("Child Process PID : %d", getpid());
        sleep(2);
        printf("Child Process %d terminating", getpid());
        exit(0);
    }
    else if (pid > 0){
        printf("Parent PID : %d", getpid());
        sleep(10);
        printf("Parent PID %d is exiting", getpid());
    }
    return 0;
}

//! In the above code, the child becomes a zombie process because the parent has not called wait()
