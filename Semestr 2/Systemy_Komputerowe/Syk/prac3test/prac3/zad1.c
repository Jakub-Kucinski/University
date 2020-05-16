/*
 * Jakub Kuciński
 * 309881
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <assert.h>
#include "zad1.h"

void sem_init(sem_t *sem, unsigned value)
{
    sem->value = (int) value;
    sem->wakeups = 0;
    assert(pthread_cond_init(&(sem->cond), NULL) == 0);
    pthread_mutexattr_t mutexattr;
    assert(pthread_mutexattr_init(&mutexattr) == 0);
    assert(pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK) == 0);
    assert(pthread_mutex_init(&(sem->mutex), &mutexattr) == 0);
}

void sem_wait(sem_t *sem)
{
    assert(pthread_mutex_lock(&(sem->mutex)) == 0);
    sem->value--;
    if(sem->value < 0)
    {
        do
        {
            pthread_cond_wait(&(sem->cond), &(sem->mutex));
        } while (sem->wakeups <= 0);
        sem->wakeups--;
    }
    assert(pthread_mutex_unlock(&(sem->mutex)) == 0);
}

void sem_post(sem_t *sem)
{
    assert(pthread_mutex_lock(&(sem->mutex)) == 0);
    sem->value++;
    if(sem->value <= 0)
    {
        sem->wakeups++;
        pthread_cond_signal(&(sem->cond));
    }
    assert(pthread_mutex_unlock(&(sem->mutex)) == 0);
}

void sem_getvalue(sem_t *sem, int *sval)
{
    assert(pthread_mutex_lock(&(sem->mutex)) == 0);
    (*sval) = sem->value;
    assert(pthread_mutex_unlock(&(sem->mutex)) == 0);
}

