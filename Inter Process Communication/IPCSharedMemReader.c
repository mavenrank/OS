//? Implement IPC using IPC.h header file.

//! This is the reader file
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    key_t key = ftok("shmfile", 65);  // Generate unique key
    int shmid = shmget(key, SHM_SIZE, 0666);  // Get the shared memory

    char *str = (char *)shmat(shmid, NULL, 0);  // Attach to the shared memory

    printf("Data read from memory: %s\n", str);  // Read the data

    shmdt(str);  // Detach from shared memory
    shmctl(shmid, IPC_RMID, NULL);  // Destroy the shared memory
    return 0;
}
