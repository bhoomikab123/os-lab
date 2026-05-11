#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int main()
{
    int available[R] = {0,0,0};

    int allocation[P][R] = {
        {0,1,0},
        {2,0,0},
        {3,0,3},
        {2,1,1},
        {0,0,2}
    };

    int request[P][R] = {
        {0,0,0},
        {2,0,2},
        {0,0,0},
        {1,0,0},
        {0,0,2}
    };

    bool finish[P];

    int work[R];

    for(int i = 0; i < R; i++)
        work[i] = available[i];

    // Initialize Finish
    for(int i = 0; i < P; i++)
    {
        bool zero = true;

        for(int j = 0; j < R; j++)
        {
            if(allocation[i][j] != 0)
            {
                zero = false;
                break;
            }
        }

        finish[i] = zero;
    }

    while(1)
    {
        bool found = false;

        for(int i = 0; i < P; i++)
        {
            if(!finish[i])
            {
                int j;

                for(j = 0; j < R; j++)
                {
                    if(request[i][j] > work[j])
                        break;
                }

                if(j == R)
                {
                    for(int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    finish[i] = true;

                    found = true;
                }
            }
        }

        if(!found)
            break;
    }

    bool deadlock = false;

    for(int i = 0; i < P; i++)
    {
        if(!finish[i])
        {
            deadlock = true;
            printf("Process P%d is deadlocked\n", i);
        }
    }

    if(!deadlock)
        printf("No Deadlock detected\n");

    return 0;
}
