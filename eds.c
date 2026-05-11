#include <stdio.h>

#define MAX 10

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int C[MAX], D[MAX], A[MAX];
    int remaining[MAX], completed[MAX] = {0};

    // Input
    for (int i = 0; i < n; i++) {
        printf("Process %d (Arrival, Execution, Deadline): ", i + 1);
        scanf("%d %d %d", &A[i], &C[i], &D[i]);
        remaining[i] = C[i];
    }

    // Step 1: Utilization
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)C[i] / D[i];
    }

    // Step 2: Feasibility
    if (U > 1)
        printf("\nNot feasible\n");
    else
        printf("\nFeasible\n");

    int t = 0, done = 0;

    printf("\nExecution:\n");

    // Step 3–4: Scheduling loop
    while (done < n) {
        int selected = -1;
        int min_deadline = 999999;

        // Build Ready List + pick earliest deadline
        for (int i = 0; i < n; i++) {
            if (A[i] <= t && completed[i] == 0 && remaining[i] > 0) {
                if (D[i] < min_deadline) {
                    min_deadline = D[i];
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            printf("Time %d: Idle\n", t);
            t++;
            continue;
        }

        printf("Time %d: Running P%d\n", t, selected + 1);

        remaining[selected]--;

        if (remaining[selected] == 0) {
            completed[selected] = 1;
            done++;
        }

        t++;
    }

    return 0;
}
