#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    int ct[n], tat[n], wt[n], rt[n];
    int remaining_bt[n];
    int completed[n];

    for(int i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i+1);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        printf("Priority (Lower number = Higher priority): ");
        scanf("%d", &pr[i]);

        remaining_bt[i] = bt[i];
        completed[i] = 0;
        rt[i] = -1;   // To calculate response time
    }

    int current_time = 0;
    int completed_count = 0;

    while(completed_count < n) {
        int idx = -1;
        int highest_priority = 9999;

        // Find highest priority process available
        for(int i = 0; i < n; i++) {
            if(at[i] <= current_time && completed[i] == 0) {
                if(pr[i] < highest_priority) {
                    highest_priority = pr[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {

            // First response time calculation
            if(rt[idx] == -1)
                rt[idx] = current_time - at[idx];

            remaining_bt[idx]--;
            current_time++;

            // If process finished
            if(remaining_bt[idx] == 0) {
                ct[idx] = current_time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                completed[idx] = 1;
                completed_count++;
            }
        }
        else {
            current_time++;  // CPU idle
        }
    }

    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pr[i],
               ct[i], tat[i], wt[i], rt[i]);

        avg_wt += wt[i];
        avg_tat += tat[i];
        avg_rt += rt[i];
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Response Time = %.2f\n", avg_rt/n);

    return 0;
}
