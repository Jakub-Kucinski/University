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
//#include "zad1.h"
#include <unistd.h>
#include <time.h>


typedef struct {
    int value;
    int wakeups;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sem_t;

void sem_init(sem_t *sem, unsigned value)
{
    // sem = malloc(sizeof(sem_t));
    // assert(sem != NULL);
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

#define NUMBER_OF_PHILOSOPHERS 5
pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];
sem_t forks[NUMBER_OF_PHILOSOPHERS];
sem_t can_eat;

int left(int i)
{
    return i;
}

int right(int i)
{
    return (i + 1) % NUMBER_OF_PHILOSOPHERS;
}

void take_forks(int i)
{
    printf("Chce jesc%d \n", i);
    sem_wait(&can_eat);
    printf("Bede jadl%d \n", i);
    sem_wait(&(forks[right(i)]));
    printf("Biore prawy%d \n", i);
    sem_wait(&(forks[left(i)]));
    printf("Biore lewy%d \n", i);
}

void put_forks(int i)
{
    printf("Odkladam prawy%d \n", i);
    sem_post(&(forks[right(i)]));
    printf("Odkladam lewy%d \n", i);
    sem_post(&(forks[left(i)]));
    printf("Najadlem sie%d \n", i);
    sem_post(&can_eat);
}

void think(int i)
{
    srand((unsigned int)time(NULL));
    printf("Mysle%d \n", i);
    usleep(rand() % 10000 + 10000);
}

void eat(int i)
{
    srand((unsigned int)time(NULL));
    printf("Jem%d \n", i);
    usleep(rand() % 10000 + 10000);
}

void *philosopher(void *k)
{
    int i = (long)k;
    while (1)
    {
        think(i);
        take_forks(i);
        eat(i);
        put_forks(i);
    }
}

void handler(int sig)
{
    int error = 0;
    for (long i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
	    error = error | pthread_cancel(philosophers[i]);
    }
    if (error)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}

int main()
{
    struct sigaction newhandler;
    newhandler.sa_handler = &handler;
    sigemptyset(&(newhandler.sa_mask));
    newhandler.sa_flags = 0;
    sigaction(SIGINT, &newhandler, NULL);
    printf("NUMBER_OF_PHILOSOPHERS%d ", NUMBER_OF_PHILOSOPHERS);
    sem_init(&can_eat, NUMBER_OF_PHILOSOPHERS - 1);

    //can_eat.value = NUMBER_OF_PHILOSOPHERS - 1;
    printf("Value%d ", can_eat.value);
    
    //can_eat.wakeups = 0;
    printf("Wakeups%d \n", can_eat.wakeups);
    pthread_mutexattr_t mutexattr;
    assert(pthread_mutexattr_init(&mutexattr) == 0);
    assert(pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK) == 0);
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        // assert(pthread_mutex_init(&(forks[i]), &mutexattr) == 0);
        sem_init(&(forks[i]), 1);
    }

    pthread_mutex_t print;
    assert(pthread_mutex_init(&print, &mutexattr) == 0);
    for (long i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        int error = 0;
		error = pthread_create(&(philosophers[i]), NULL, philosopher, (void *) i);
		if (error)
		{
			pthread_mutex_lock(&print);
			printf("BŁĄÐ (przy tworzeniu wątku): %s\n", strerror(error));
			pthread_mutex_unlock(&print);
			exit(EXIT_FAILURE);
        }
    }

    for (long i=0; i < NUMBER_OF_PHILOSOPHERS; i++)
	{
		int error = pthread_join(philosophers[i], NULL);
		if (error)
		{
			pthread_mutex_lock(&print);
			printf("BŁĄD (przy oczekiwaniu na zakończenie wątków): %s\n", strerror(error));
			pthread_mutex_unlock(&print);
			exit(EXIT_FAILURE);
		}
    }


    return EXIT_SUCCESS;
}