#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Sharedmem.h"

#define N_DATA 2000000   //Total number of random integers (data to transfer)
#define N_SHARED 2000    //Shared memory buffer size 

int main() {
    
    //Create shared memory segment for N_SHARED ints and Attach it to parent process
    int shmid = create_shared_memory(N_SHARED);
    int* shared_mem = attach_to_shared_memory(shmid);

    //New Seed
    srand48(time(NULL));

    //Creates a child process from the parent process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        //Child process(P2)
        
        sleep(3);  //Ensure parent has time to write data before child reads

            
        //Read from shared memory
        for (int j = 0; j < N_SHARED; j++) {
            printf("%d ", shared_mem[j]);
            if ((j+1) % 10 == 0) printf("\n");
        }
        printf("\nShared memory read complete.\n\n");

        

        detach_from_shared_memory(shared_mem);  //Detach shared memory
        exit(0); 
    }
    else {
        //Parent process (P1)

        printf("\nParent process writing data to shared memory...\n\n");
          
        //Write data into shared memory
        for (int j = 0; j < N_SHARED; j++) {
            shared_mem[j] = lrand48();  //Random number generation
        }
        
        wait(NULL);  //Wait for the child process to finish

        //Cleanup
        detach_from_shared_memory(shared_mem);  //Detach shared memory
        delete_shared_memory(shmid);  //Delete shared memory segment
    }

    return 0;
}
