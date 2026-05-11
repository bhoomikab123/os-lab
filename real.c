#include <stdio.h>
#include <math.h>

#define MAX 10

int main() {
    int n, sim_time;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int C[MAX], T[MAX];
    int remaining[MAX], next_arrival[MAX];

    // Input
    for (int i = 0; i < n; i++) {
        printf("Task %d (Ci Ti): ", i + 1);
        scanf("%d %d", &C[i], &T[i]);
    }

    // Step 1: CPU Utilization
    float U = 0;
    for (int i = 0; i < n; i++) {
        U += (float)C[i] / T[i];
    }

    // Step 2: RMS Bound
    float bound = n * (pow(2, 1.0 / n) - 1);

    printf("\nCPU Utilization = %.3f", U);
    printf("\nRMS Bound = %.3f\n", bound);

    // Step 3: Schedulability Check
    if (U <= bound) {
        printf("Schedulable using RMS\n");
    } else {
        printf("Not guaranteed schedulable (need further analysis)\n");
    }

    // Step 4: Sort tasks by period (ascending)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (T[i] > T[j]) {
                // swap T
                int temp = T[i];
                T[i] = T[j];
                T[j] = temp;

                // swap C accordingly
                temp = C[i];
                C[i] = C[j];
                C[j] = temp;
            }
        }
    }

    printf("\nPriority Order (Shortest Period = Highest Priority):\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d → C=%d, T=%d\n", i + 1, C[i], T[i]);
    }

    // Initialize scheduling variables
    for (int i = 0; i < n; i++) {
        remaining[i] = 0;
        next_arrival[i] = 0;
    }

    printf("\nEnter simulation time: ");
    scanf("%d", &sim_time);

    printf("\n--- Scheduling Start ---\n");

    // Step 5: Scheduling Loop
    for (int time = 0; time < sim_time; time++) {

        // Release tasks
        for (int i = 0; i < n; i++) {
            if (time == next_arrival[i]) {
                remaining[i] += C[i];
                next_arrival[i] += T[i];
            }
        }

        // Select highest priority READY task
        int selected = -1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                selected = i; // first available = highest priority (already sorted)
                break;
            }
        }

        // Execute
        if (selected == -1) {
            printf("Time %d: CPU Idle\n", time);
        } else {
            printf("Time %d: Running Task T%d\n", time, selected + 1);
            remaining[selected]--;
        }
    }

    printf("--- Scheduling End ---\n");

    return 0;
}
