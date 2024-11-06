//! This is the writer file

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);  // Create shared memory

    char *str = (char *)shmat(shmid, NULL, 0);  // Attach to the shared memory

    printf("Write Data: ");
    fgets(str, SHM_SIZE, stdin);  // Get input from the user

    printf("Data written in memory: %s\n", str);

    shmdt(str);  // Detach from shared memory
    return 0;
}
