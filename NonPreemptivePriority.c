#include<stdio.h>
 
int main()
{
    int burstTime[20],process[20],waitingTime[20],turnAround[20],priority[20],i,j,n,total=0;
    int pos,temp,avgWaitingTime,avgTurnAround;
    printf("Enter Total Number of Process:");
    scanf("%d",&n);
 
    printf("\nEnter Burst Time and Priority\n");
    for(i=0;i<n;i++) // for taking burst time and priority of each process
    {
        printf("\nP[%d]\n",i+1);
        printf("Burst Time: ");
        scanf("%d",&burstTime[i]);
        printf("Priority: ");
        scanf("%d",&priority[i]);
        process[i]=i+1;           //contains process number
    }
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(priority[j]<priority[pos])
                pos=j;
        }
 
        temp=priority[i];
        priority[i]=priority[pos];
        priority[pos]=temp;
 
        temp=burstTime[i];
        burstTime[i]=burstTime[pos];
        burstTime[pos]=temp;
 
        temp=process[i];
        process[i]=process[pos];
        process[pos]=temp;
    }
 
    waitingTime[0]=0; //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        waitingTime[i]=0;
        for(j=0;j<i;j++)
            waitingTime[i]+=burstTime[j];
 
        total+=waitingTime[i];
    }
 
    avgWaitingTime=total/n;
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        turnAround[i]=burstTime[i]+waitingTime[i];
        total+=turnAround[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",process[i],burstTime[i],waitingTime[i],turnAround[i]);
    }
 
    avgTurnAround=total/n;
    printf("\n\nAverage Waiting Time=%d",avgWaitingTime);
    printf("\nAverage Turnaround Time=%d\n",avgTurnAround);
 
return 0;
}