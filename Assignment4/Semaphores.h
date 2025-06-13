#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

#define SEM_A 0200 //Semaphore Alter mode
#define SEM_R 0400 //Semaphore Read mode


int new_sem(int n); /* create new semaphore set with n semaphores, return semid */
void operation_p(int semid, unsigned int semindex); /* enter critical region */
void operation_v(int semid, unsigned int semindex); /* leave critical region */
void initialize_sem(int semid, unsigned int semindex, int value);
int delete_sem(int semid); /* delete semaphore set semid */
int get_sem_value(int semid, unsigned int semindex); /* get the value of semaphore semindex in semaphore set semid */

#endif 