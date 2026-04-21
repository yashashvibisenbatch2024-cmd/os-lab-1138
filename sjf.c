void findTimes(int processes[], int n, int bt[],
               int wt[], int tat[], int rt[], int ct[]) {

    int remaining_bt[MAX_PROCESSES];
    int is_started[MAX_PROCESSES] = {0};

    for (int i = 0; i < n; i++) {
        remaining_bt[i] = bt[i];
        wt[i] = 0;
        rt[i] = -1;
    }

    int current_time = 0;
    int completed = 0;

    while (completed != n) {
        int min_bt = 9999;
        int shortest = -1;

        // Find shortest remaining time process
        for (int i = 0; i < n; i++) {
            if (remaining_bt[i] > 0 && remaining_bt[i] < min_bt) {
                min_bt = remaining_bt[i];
                shortest = i;
            }
        }

        // If first time CPU is allocated → Response Time
        if (is_started[shortest] == 0) {
            rt[shortest] = current_time;
            is_started[shortest] = 1;
        }

        // Execute process for 1 unit
        remaining_bt[shortest]--;
        current_time++;

        // If process completes
        if (remaining_bt[shortest] == 0) {
            completed++;
            ct[shortest] = current_time;
            wt[shortest] = ct[shortest] - bt[shortest];
            tat[shortest] = bt[shortest] + wt[shortest];
        }
    }
}

void calculateAverageTimes(int processes[], int n, int bt[]) {

    int wt[MAX_PROCESSES], tat[MAX_PROCESSES];
    int rt[MAX_PROCESSES], ct[MAX_PROCESSES];
    int total_wt = 0, total_tat = 0, total_rt = 0;

    findTimes(processes, n, bt, wt, tat, rt, ct);

    printf("Process\tBT\tWT\tTAT\tRT\tCT\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i], bt[i], wt[i], tat[i], rt[i], ct[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int burst_time[] = {6, 8, 7, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    calculateAverageTimes(processes, n, burst_time);
    return 0;
}
