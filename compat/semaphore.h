
#pragma once

typedef void* sem_t;

int sem_init(sem_t* sem, int a, int b) { return 0; }

int sem_destroy(sem_t* sem) { return 0; }

int sem_wait(sem_t* sem) { return 0; }

int sem_post(sem_t* sem) { return 0; }

int sem_trywait(sem_t* sem) { return 0; }

int sem_timedwait(sem_t* sem, struct timespec *ts) { return 0; }

int clock_gettime(int type, struct timespec *ts) { return 0; }