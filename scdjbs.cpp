#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

struct Job {
    int id;
    int deadline;
    int profit;
};

// Merge two halves sorted by profit
void merge(vector<Job>& a, int l, int m, int r) {
    int l1 = m - l + 1;
    int r1 = r - m;
    
    vector<Job> L(l1), R(r1);
    for (int i = 0; i < l1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < r1; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    
    // Sort in descending order of profit
    while (i < l1 && j < r1) {
        if (L[i].profit >= R[j].profit) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < l1) {
        a[k] = L[i];
        i++; k++;
    }

    while (j < r1) {
        a[k] = R[j];
        j++; k++;
    }
}

void mergeSort(vector<Job>& a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

// Schedule jobs to maximize profit
void jobScheduling(vector<Job>& a) {
    // Step 1: Sort jobs by profit (descending)
    mergeSort(a, 0, a.size() - 1);

    // Step 2: Find max deadline
    int maxDeadline = 0;
    for (auto &job : a)
        maxDeadline = max(maxDeadline, job.deadline);

    // Step 3: Create time slots
    vector<int> slot(maxDeadline + 1, -1);
    int totalProfit = 0;

    // Step 4: Greedy assignment
    for (auto &job : a) {
        for (int t = job.deadline; t > 0; t--) {
            if (slot[t] == -1) {
                slot[t] = job.id;
                totalProfit += job.profit;
                break;
            }
        }
    }

    // Step 5: Output
    cout << "Scheduled Jobs: ";
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != -1)
            cout << "J" << slot[i] << " ";
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {
    vector<Job> a=
    {
        {1, 6, 250},
        {2, 8, 300},
        {3, 4, 180},
        {4, 10, 450},
        {5, 5, 150},
        {6, 3, 100},
        {7, 2, 90},
        {8, 9, 280},
        {9, 7, 310},
        {10, 1, 70},
        {11, 12, 500},
        {12, 15, 420},
        {13, 11, 350},
        {14, 8, 260},
        {15, 13, 380}
    };

    // Measure execution time of job scheduling
    auto start = high_resolution_clock::now();
    jobScheduling(a);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Execution Time: " << duration.count() << " microseconds" << endl;
    return 0;
}