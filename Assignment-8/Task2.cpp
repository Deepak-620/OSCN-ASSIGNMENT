#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int at, bt;
    int ct, tat, wt;
    bool completed = false;
};

int main() {
    int n = 4;

    // Given processes
    Process p[n] = {
        {"P1", 0, 8},
        {"P2", 1, 4},
        {"P3", 2, 9},
        {"P4", 3, 5}
    };

    int completed = 0, currentTime = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "------ Non-Preemptive Shortest Job First (SJF) Scheduling ------\n";

    while (completed < n) {
        int idx = -1;
        int minBT = 9999;

        // Select process with shortest burst time among arrived processes
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= currentTime && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }

        if (idx != -1) {
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = true;
            completed++;
        } else {
            currentTime++; // No process arrived yet
        }
    }

    // Output Table
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "---------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;

        totalWT += p[i].wt;
        totalTAT += p[i].tat;
    }

    cout << "\nAverage Waiting Time = " << totalWT / n;
    cout << "\nAverage Turnaround Time = " << totalTAT / n << endl;

    // Gantt Chart
    cout << "\nGantt Chart:\n| ";

    sort(p, p + n, [](Process a, Process b) { return a.ct < b.ct; });

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << " | ";
    }

    cout << "\n0";
    for (int i = 0; i < n; i++) {
        cout << setw(5) << p[i].ct;
    }
    cout << endl;

    return 0;
}
