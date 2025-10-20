#include <iostream>
#include <vector>
using namespace std;

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
    vector<Job> a = {
        {1, 20, 900}, {2, 18, 850}, {3, 17, 800}, {4, 16, 750},
{5, 15, 700}, {6, 14, 650}, {7, 13, 600}, {8, 12, 580},
{9, 11, 550}, {10, 10, 500}, {11, 9, 480}, {12, 8, 450},
{13, 7, 420}, {14, 6, 400}, {15, 5, 370}, {16, 4, 340},
{17, 3, 310}, {18, 2, 290}, {19, 1, 260}, {20, 19, 870}
    };

    jobScheduling(a);
    return 0;
}