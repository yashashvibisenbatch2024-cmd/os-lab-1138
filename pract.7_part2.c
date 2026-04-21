#include <stdio.h>

int main() {
    int n, i;

    printf("Enter number of processes:\n");
    scanf("%d", &n);

    int at[n], bt[n], rem_bt[n];
    int ct[n], tat[n], wt[n];

    // Input
    for(i = 0; i < n; i++) {
        printf("Enter arrival time of process %d:\n", i + 1);
        scanf("%d", &at[i]);

        printf("Enter burst time of process %d:\n", i + 1);
        scanf("%d", &bt[i]);

        rem_bt[i] = bt[i];
        ct[i] = 0;
        tat[i] = 0;
        wt[i] = 0;
    }

    int tq;
    printf("Enter time quantum:\n");
    scanf("%d", &tq);

    int time = 0;
    int completed = 0;

    while(completed < n) {
        int ready = 0;

        for(i = 0; i < n; i++) {

            // Check if process is ready
            if(at[i] <= time && rem_bt[i] > 0) {
                ready = 1;

                if(rem_bt[i] <= tq) {
                    // Execute completely
                    time += rem_bt[i];
                    rem_bt[i] = 0;

                    ct[i] = time;
                    completed++;
                } else {
                    // Execute for time quantum
                    time += tq;
                    rem_bt[i] -= tq;
                }
            }
        }

        // If no process is ready, increment time
        if(ready == 0) {
            time++;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    // Calculate TAT and WT
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    // Output
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
