#include <stdio.h>
#include <stdlib.h>

// Five Philosophers
int n;
int mutex = 1;  // Mutex semaphore provides mutual exclusion for access to buffer pool
int empty = 10; // Empty Semaphore counts the number of empty buffers
int full = 0;   // Full Semaphore counts the number of full buffers

void producer()
{
  --mutex;
  ++full;  // Increasing full slots by 1
  --empty; // Decreasing empty slots by 1
  n++;
  printf("\nProducer produces - item %d", n);
  ++mutex;
}

void consumer()
{
  --mutex;
  --full;  // Decreasing Full slots by 1
  ++empty; // Increase empty slots by 1
  printf("\nConsumer consumes - item %d", n);
  n--;
  ++mutex;
}

int main()
{
  int choice;
  printf("\n1. Press 1 for Producer"
         "\n2. Press 2 for Consumer"
         "\n3. Press 3 for Exit");

#pragma omp critical // Only one thread enters the critical section at a time
  for (int i = 1; i > 0; i++)
  {
    printf("\nEnter your choice:");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      if ((mutex == 1) && (empty != 0))
      {
        producer();
      }
      else
        printf("Buffer is full!");
      break;
    case 2:
      if ((mutex == 1) && (full != 0))
      {
        consumer();
      }
      else
      {
        printf("Buffer is empty!");
      }
      break;
    case 3:
      exit(0);
      break;
    }
  }
}