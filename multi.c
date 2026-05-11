#include <stdio.h>

struct process {
    int pid, at, bt, type;
    int ct, tat, wt, start;
};

int main() {
    int n, i, j, time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n], temp;

    // Input
    for(i = 0; i < n; i++) {
        printf("Enter PID, AT, BT, TYPE (0-System, 1-User): ");
        scanf("%d %d %d %d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].type);
    }

    // Step 1: Separate queues
    struct process sys[n], user[n];
    int s = 0, u = 0;

    for(i = 0; i < n; i++) {
        if(p[i].type == 0)
            sys[s++] = p[i];
        else
            user[u++] = p[i];
    }

    // Step 2: Sort System Queue by AT
    for(i = 0; i < s-1; i++) {
        for(j = i+1; j < s; j++) {
            if(sys[i].at > sys[j].at) {
                temp = sys[i];
                sys[i] = sys[j];
                sys[j] = temp;
            }
        }
    }

    // Sort User Queue by AT
    for(i = 0; i < u-1; i++) {
        for(j = i+1; j < u; j++) {
            if(user[i].at > user[j].at) {
                temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }

    // Step 3: Execute System Queue first
    for(i = 0; i < s; i++) {
        if(time < sys[i].at)
            time = sys[i].at;

        sys[i].start = time;
        time += sys[i].bt;
        sys[i].ct = time;

        sys[i].tat = sys[i].ct - sys[i].at;
        sys[i].wt = sys[i].tat - sys[i].bt;
    }

    // Step 4: Execute User Queue
    for(i = 0; i < u; i++) {
        if(time < user[i].at)
            time = user[i].at;

        user[i].start = time;
        time += user[i].bt;
        user[i].ct = time;

        user[i].tat = user[i].ct - user[i].at;
        user[i].wt = user[i].tat - user[i].bt;
    }

    // Step 5: Display Output
    printf("\nSystem Queue:\n");
    printf("PID AT BT CT TAT WT\n");
    for(i = 0; i < s; i++) {
        printf("%d %d %d %d %d %d\n",
            sys[i].pid, sys[i].at, sys[i].bt,
            sys[i].ct, sys[i].tat, sys[i].wt);
    }

    printf("\nUser Queue:\n");
    printf("PID AT BT CT TAT WT\n");
    for(i = 0; i < u; i++) {
        printf("%d %d %d %d %d %d\n",
            user[i].pid, user[i].at, user[i].bt,
            user[i].ct, user[i].tat, user[i].wt);
    }

    return 0;
}
