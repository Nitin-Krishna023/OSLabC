#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// An empty room with 5 chopsticks and places for four philosophers.

// Counting Semaphore - For Multiple Instances
// Binary Semaphore - For Single Instance

// Data type of semaphore - sem_t
sem_t room;         // Counting Semaphore - 4 instances of resource chair
sem_t chopstick[5]; // 5 chopsticks on the table

void *philosopher(void *num);
void eat(int);

int main()
{
  int i, a[5];
  pthread_t tid[5];

  sem_init(&room, 0, 4); // intializing counting semaphore

  for (i = 0; i < 5; i++) // intializing five binary semaphores
    sem_init(&chopstick[i], 0, 1);

  for (i = 0; i < 5; i++)
  {
    a[i] = i; // philospher id
    pthread_create(&tid[i], NULL, philosopher, (void *)&a[i]);
  }
  for (i = 0; i < 5; i++)
    pthread_join(tid[i], NULL);
}

void *philosopher(void *num)
{
  int phil_num = *(int *)num; // converting void to integer

  sem_wait(&room); // check if resource is available and if it is, allocate to semaphore
  printf("\nPhilosopher %d has entered room", phil_num);
  sem_wait(&chopstick[phil_num]);
  sem_wait(&chopstick[(phil_num + 1) % 5]); // Blocking Chopsticks to the left and right of a philosopher - Philosopher eats with both chopsticks and after eating releases them

  printf("\nPhilosopher %d is eating", phil_num);
  sleep(2);
  printf("\nPhilosopher %d has finished eating", phil_num);

  sem_post(&chopstick[(phil_num + 1) % 5]);
  sem_post(&chopstick[phil_num]);
  sem_post(&room);
}
