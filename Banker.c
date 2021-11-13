#include <stdio.h>

void increaseAvailable(int available[], int allocated[5][3], int i)
{
  for (int t = 0; t < 3; t++)
  {
    available[t] += allocated[i][t];
  }
}

int main()
{
  int n = 5;
  int m = 3;
  int allocated[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2,1,1},{0, 0, 2}};
  int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
  int available[3] = {3, 3, 2};

  int need[5][3];
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      need[i][j] = max[i][j] - allocated[i][j];
    }
  }

  int finished[5];
  for (int i = 0; i < n; i++)
  {
    finished[i] = 0;
  }

  int safe_sequence[n];
  int idx = 0;

  int k = 0;
  while (k < n)
  {
    for (int i = 0; i < n; i++)
    {
      if (finished[i] == 0)
      {
        int flag = 0;
        for (int j = 0; j < m; j++)
        {
          if (need[i][j] > available[j])
          { // If need greater than available work
            flag = 1;
            break;
          }
        }
        if (flag == 0)
        {
          safe_sequence[idx++] = i;
          increaseAvailable(available, allocated, i);
          finished[i] = 1;
          k++;
        }
      }
    }
  }

  printf("The Safe Sequence is: ");
  for (int i = 0; i < n; i++)
  {
    printf("P%d ", safe_sequence[i]);
  }
}