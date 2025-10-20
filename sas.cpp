#include <iostream>
#include <vector>
using namespace std;

void merge(vector<pair<int,int>>& a, int l, int m, int r, vector<int>& count) {
    int l1 = m - l + 1;
    int r1 = r - m;

    vector<pair<int,int>> L(l1), R(r1); // Temporary vectors for merging

    for (int i = 0; i < l1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < r1; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0;
    int k = l;
    int rightCount = 0;  // number of smaller elements from right half

    while (i < l1 && j < r1) {
        if (L[i].first <= R[j].first) {
            count[L[i].second] += rightCount;
            a[k++] = L[i++];
        } else {
            rightCount++;
            a[k++] = R[j++];
        }
    }

    while (i < l1) {
        count[L[i].second] += rightCount;
        a[k++] = L[i++];
    }

    while (j < r1) {
        a[k++] = R[j++];
    }
}

void mergeSort(vector<pair<int,int>>& a, int l, int r, vector<int>& count) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;
    mergeSort(a, l, m, count);
    mergeSort(a, m + 1, r, count);
    merge(a, l, m, r, count);
}

int main() {
    vector<int> arr = {5, 2, 6, 1};
    int n = arr.size();

    vector<pair<int,int>> a;
    for (int i = 0; i < n; i++)
        a.push_back({arr[i], i});

    vector<int> count(n, 0);
    mergeSort(a, 0, n - 1, count);

    cout << "Output: \n";
    for (int i = 0; i < n; i++)
        cout << count[i] << " ";
    cout << endl;

    return 0;
}
