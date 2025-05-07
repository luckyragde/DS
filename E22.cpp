#include <iostream>
#include <vector>
#include <queue> // For priority_queue
using namespace std;

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    vector<int> marks(n);
    cout << "Enter marks of " << n << " students:\n";
    for (int i = 0; i < n; ++i) {
        cin >> marks[i];
    }

    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;

    for (int i = 0; i < n; ++i) {
        maxHeap.push(marks[i]);
        minHeap.push(marks[i]);
    }

    int maxMark = maxHeap.top();
    int minMark = minHeap.top();

    cout << "Maximum mark = " << maxMark << endl;
    cout << "Minimum mark = " << minMark << endl;

    return 0;
}

