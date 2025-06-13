#ifndef SHAREDMEM_H
#define SHAREDMEM_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

int create_shared_memory(unsigned int num);
int* attach_to_shared_memory(int shmid);
void detach_from_shared_memory(int* shared_mem);
void delete_shared_memory(int shmid);

#endif  