//? Write a proram which creates a child process, waits for termination of its child and then lists its PID
//? together with the state in which the process was terminated

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int states;
    pid_t pid = fork();
    if (pid < 0){
        perror("Fork Failed");
        return 1;
    }
    else if (pid == 0){
        printf("Child process PID : %d", getpid());
        sleep(2);
        exit(0);
    }
    else{
        printf("Parent Process Waiting for child not Terminate");
        waitpid(pid, &states, 0);
        if (WIFEXITED(states)){
            printf("Child Process PID : %d", pid, WIFEXITED(states));
        }
        else if (WIFSIGNALED(states)){
            printf("Child Process PID : %d terminated by synd = %d", pid, WTERMSIG(states));
        }
        else{
            printf("Child Process PID : %d terminated abnormally", pid);
        }
    }
}