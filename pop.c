#include <stdio.h>

#define MAX 10
#define TIME_QUANTUM 10

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int burst[MAX], weight[MAX], remaining[MAX];
    int completed[MAX] = {0};

    // Input
    for (int i = 0; i < n; i++) {
        printf("Process %d (Burst Time, Weight): ", i + 1);
        scanf("%d %d", &burst[i], &weight[i]);
        remaining[i] = burst[i];
    }

    // Step 1: total weight
    int total_weight = 0;
    for (int i = 0; i < n; i++) {
        total_weight += weight[i];
    }

    printf("\nExecution:\n");

    // Step 2: scheduling loop
    while (total_weight > 0) {

        for (int i = 0; i < n; i++) {

            if (completed[i] == 1)
                continue;

            // proportional time slice
            float share = (float)weight[i] / total_weight;
            int time_slice = (int)(share * TIME_QUANTUM);

            // ensure at least 1 unit
            if (time_slice < 1)
                time_slice = 1;

            // cap to remaining burst time
            if (time_slice > remaining[i])
                time_slice = remaining[i];

            printf("P%d runs for %d units\n", i + 1, time_slice);

            remaining[i] -= time_slice;

            // check completion
            if (remaining[i] <= 0) {
                completed[i] = 1;
                total_weight -= weight[i];
                printf("P%d completed\n", i + 1);
            }
        }
    }

    printf("\nAll processes completed.\n");

    return 0;
}
