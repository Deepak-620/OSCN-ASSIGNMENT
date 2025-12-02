#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    string pid;
    int at, bt; 
    int ct, tat, wt;
};

// Sorting by Arrival Time
bool compare(Process a, Process b) {
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    // Input
    for(int i = 0; i < n; i++) {
        cout << "\nEnter Process ID: ";
        cin >> p[i].pid;
        cout << "Arrival Time: ";
        cin >> p[i].at;
        cout << "Burst Time: ";
        cin >> p[i].bt;
    }

    // Sort by Arrival Time
    sort(p, p+n, compare);

    int time = 0;
    float totalTAT = 0, totalWT = 0;

    // FCFS Calculation
    for(int i = 0; i < n; i++) {

        if(time < p[i].at) {
            time = p[i].at; // CPU Idle handling
        }

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    // Output Table
    cout << "\n==============================================\n";
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "==============================================\n";

    for(int i = 0; i < n; i++) {
        cout << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;
    }

    // Averages
    float avgTAT = totalTAT / n;
    float avgWT = totalWT / n;

    cout << "==============================================\n";
    cout << "Total Turnaround Time: " << totalTAT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
    cout << "Total Waiting Time: " << totalWT << endl;
    cout << "Average Waiting Time: " << avgWT << endl;

    return 0;
}
