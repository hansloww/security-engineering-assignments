#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sharedmem.h"
#include "Semaphores.h"

#define N_DATA 2000000   //Total number of random integers (data to transfer)
#define N_SHARED 2000    //Shared memory buffer size 

int main() {
    
    //Create shared memory segment for N_SHARED ints and Attach it to parent process
    int shmid = create_shared_memory(N_SHARED);
    int* shared_mem = attach_to_shared_memory(shmid);

    //Create semaphore set with two semaphores: empty and full
    int semid = new_sem(2);

    //Initialize semaphores: empty = 1 (shared memory is initially empty),
    //full = 0 (no data is written initially).
    initialize_sem(semid, 0, 1); //empty semaphore
    initialize_sem(semid, 1, 0); //full semaphore

    srand48(time(NULL));

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        //Child process (P2)
        
        for (int i = 0; i < N_DATA; i += N_SHARED) {
            //Wait for the full semaphore (i.e., ensure that the parent has written data)
            operation_p(semid, 1);
            
            //Read from shared memory
            for (int j = 0; j < N_SHARED; j++) {
                printf("%d ", shared_mem[j]);
                if ((j + 1) % 10 == 0) printf("\n");
            }
            printf("\nShared memory read complete.\n\n");

            //Signal the empty semaphore (data is read, shared memory is empty again)
            operation_v(semid, 0);
        }

        detach_from_shared_memory(shared_mem);  //Detach shared memory
        exit(0);
    }
    else {
        //Parent process (P1)
        
        for (int i = 0; i < N_DATA / N_SHARED; i += N_SHARED) {
            //Wait for the empty semaphore (i.e., ensure that memory is empty)
            operation_p(semid, 0);

            printf("\nParent process writing data to shared memory...\n\n");

            //Write data into shared memory
            for (int j = 0; j < N_SHARED; j++) {
                shared_mem[j] = lrand48();  // Random number generation
            }

            //Signal the full semaphore (data is written, shared memory is full)
            operation_v(semid, 1);
        }

        wait(NULL);  //Wait for the child process to finish

        //Cleanup
        detach_from_shared_memory(shared_mem);  //Detach shared memory
        delete_shared_memory(shmid);  //Delete shared memory segment
        delete_sem(semid);  //Delete semaphore set
    }

    return 0;
}
