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
#include <unistd.h>
#include <time.h>

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
    sem_wait(&can_eat);
    sem_wait(&(forks[right(i)]));
    sem_wait(&(forks[left(i)]));
}

void put_forks(int i)
{
    sem_post(&(forks[right(i)]));
    sem_post(&(forks[left(i)]));
    sem_post(&can_eat);
}

void think()
{
    srand((unsigned int)time(NULL));
    usleep(rand() % 1000 + 1000);
}

void eat()
{
    srand((unsigned int)time(NULL));
    usleep(rand() % 1000 + 1000);
}

void *philosopher(void *k)
{
    int i = (long)k;
    while (1)
    {
        think();
        take_forks(i);
        eat();
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

    sem_init(&can_eat, NUMBER_OF_PHILOSOPHERS - 1);

    pthread_mutexattr_t mutexattr;
    assert(pthread_mutexattr_init(&mutexattr) == 0);
    assert(pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK) == 0);
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
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