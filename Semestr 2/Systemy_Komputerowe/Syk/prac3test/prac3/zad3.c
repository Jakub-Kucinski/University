/*
 * Jakub Kuciński
 * 309881
 * 
 * Zadanie jest rozwiązane częściowo, nie udało mi się napisać obługi sygnału sigint by działała zgodnie z poleceniem, czyli kończyła procesy.
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
#include <unistd.h>
#include <time.h>
#include <fcntl.h> 
#include <semaphore.h>

#define NUMBER_OF_PHILOSOPHERS 5
pid_t parent_pid;
pid_t kids[NUMBER_OF_PHILOSOPHERS];
sem_t *forks[NUMBER_OF_PHILOSOPHERS];
sem_t *can_eat;

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
    sem_wait(can_eat);
    sem_wait((forks[right(i)]));
    sem_wait((forks[left(i)]));
}

void put_forks(int i)
{
    sem_post((forks[right(i)]));
    sem_post((forks[left(i)]));
    sem_post(can_eat);
}

void think()
{
    srand((unsigned int)time(NULL));
    usleep(rand() % 10000 + 10000);
}

void eat()
{
    srand((unsigned int)time(NULL));
    usleep(rand() % 10000 + 10000);
}

void philosopher(int i)
{
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
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        kill(kids[i], SIGTERM);
    }
    if (sem_unlink("/can_eat") == -1)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}

int main()
{
    can_eat = sem_open("/can_eat", O_CREAT, 0644, NUMBER_OF_PHILOSOPHERS - 1);
    if (can_eat == SEM_FAILED) 
    {
        exit(EXIT_FAILURE);
    }
    
    for (int j = 0; j < NUMBER_OF_PHILOSOPHERS; j++)
    {
        char buffer [20];
        int cx = -1;
        cx = snprintf(buffer, 20, "/forks%d", j);
        if (cx == -1)
            exit(EXIT_FAILURE);
        forks[j] = sem_open(buffer, O_CREAT, 0644, 1);
    }
        
    parent_pid = getpid();
    int i = 0;
    for (i; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        pid_t kid = fork();
        switch (kid)
        {
        case -1:
            handler(0);
            break;
        case 0:
            philosopher(i);
            break;
        default:
            kids[i] = kid;
            break;
        }
    }
    
    struct sigaction newhandler;
    newhandler.sa_handler = &handler;
    sigemptyset(&(newhandler.sa_mask));
    newhandler.sa_flags = 0;
    sigaction(SIGINT, &newhandler, NULL);

    return EXIT_SUCCESS;
}

