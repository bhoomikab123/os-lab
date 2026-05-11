#include<stdio.h>

int main()
{
    int n,i,j;
    int bt[10],wt[10],tat[10],priority[10];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("Enter Burst Time and Priority for P%d: ",i+1);
        scanf("%d%d",&bt[i],&priority[i]);
    }

    // Sorting based on priority (smaller number = higher priority)
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(priority[i] > priority[j])
            {
                int temp;

                temp=priority[i];
                priority[i]=priority[j];
                priority[j]=temp;

                temp=bt[i];
                bt[i]=bt[j];
                bt[j]=temp;
            }
        }
    }

    wt[0]=0;

    for(i=1;i<n;i++)
        wt[i]=wt[i-1]+bt[i-1];

    for(i=0;i<n;i++)
    {
        tat[i]=wt[i]+bt[i];
        printf("P%d WT=%d TAT=%d\n",i+1,wt[i],tat[i]);
    }

    return 0;
}
