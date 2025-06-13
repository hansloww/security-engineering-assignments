#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Sharedmem.h"

//THESE FUNCTIONS HANDLE SHARED MEMORY OPERATIONS FOR INTEGER ARRAYS !!!!!

//Function to create memory for integers
int create_shared_memory(unsigned int num) {
    //Create shared memory segment for 'size' integers
    int shmid = shmget(IPC_PRIVATE, num * sizeof(int), 0666 | IPC_CREAT);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }
    return shmid;
}

int* attach_to_shared_memory(int shmid) {
    //Attach shared memory to the parent process
    int* shared_mem = (int *)shmat(shmid, NULL, 0);
    if (shared_mem == (int *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Return the pointer to the attached shared memory
    return shared_mem;
}

//Function to detach from shared memory
void detach_from_shared_memory(int* shared_mem) {
    if (shmdt(shared_mem) < 0) {
        perror("shmdt failed");
        exit(1);
    }
}

//Function to delete shared memory segment
void delete_shared_memory(int shmid) {
    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        perror("shmctl failed");
        exit(1);
    }
}