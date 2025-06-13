#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Semaphores.h"

/* create new semaphore set with n semaphores, return semid */
int new_sem(int n)
{
return semget(IPC_PRIVATE, n, SEM_A | SEM_R );
}

void operation_p(int semid, unsigned int semindex) /* enter critical region */
{
    struct sembuf P = {semindex, -1, 0};  // wait
    if (semop(semid, &P, 1) < 0) /* 1 operation */
    {
        perror("semop() in operation_p()");
        return;
    }
    return;
}

void operation_v(int semid, unsigned int semindex) /* leave critical region */
{
    struct sembuf V = {semindex, 1, 0};   // signal
    if (semop(semid, &V, 1) < 0) /* 1 operation */
    {
        perror("semop() in operation_v()");
        return;
    }
    return;
}

/* initialize semaphore semindex in semaphore set semid with value */
void initialize_sem(int semid, unsigned int semindex, int value)
{
    if (semctl(semid, semindex, SETVAL, value) < 0)
    {
        perror("semctl() in initialize_sem()");
        return; 
    }
    return; 
}

/* delete semaphore set semid */
int delete_sem(int semid)
{
if (semctl(semid, 0, IPC_RMID) < 0)
{
perror("semctl(sem, 0, IPC_RMID, 0)");
return 0; /* error removing semaphore */
}
return 1; /* success */
}

/* get the value of semaphore semindex in semaphore set semid */
int get_sem_value(int semid, unsigned int semindex) {
    int sem_value = semctl(semid, semindex, GETVAL);
    if (sem_value == -1) {
        perror("semctl(GETVAL) failed");
        return -1;
    }
    return sem_value; 
}