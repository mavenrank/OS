#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }
    else if(pid == 0){
        printf("Child Process PID : %d", getpid());
        printf("Parent Process PID : %d", getppid());
    }
    else{
        printf("Parent Process : %d", getpid());
        printf("Child PID : %d", pid);
        wait(NULL);
    }
    return 0;
}