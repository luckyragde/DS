#include <iostream>
using namespace std;

const int MAX = 100;

class Heap {
    int arr[MAX];
    int size;
    bool isMax; // true for max-heap, false for min-heap

public:
    Heap(bool type) {
        size = 0;
        isMax = type;
    }

    void insert(int value) {
        if (size >= MAX) {
            cout << "Heap Overflow!\n";
            return;
        }

        arr[size] = value;
        int i = size;
        size++;

        // Bubble up
        while (i > 0) {
            int parent = (i - 1) / 2;
            if ((isMax && arr[i] > arr[parent]) || (!isMax && arr[i] < arr[parent])) {
                swap(arr[i], arr[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

    int getTop() {
        if (size == 0) {
            cout << "Heap is empty.\n";
            return -1;
        }
        return arr[0];
    }

    void display() {
        cout << (isMax ? "Max" : "Min") << "-Heap: ";
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Heap maxHeap(true);
    Heap minHeap(false);

    for (int i = 0; i < n; i++) {
        int mark;
        cout << "Enter mark of student " << (i + 1) << ": ";
        cin >> mark;
        maxHeap.insert(mark);
        minHeap.insert(mark);
    }

    cout << "\n";
    maxHeap.display();
    minHeap.display();

    cout << "\nMaximum Marks: " << maxHeap.getTop() << "\n";
    cout << "Minimum Marks: " << minHeap.getTop() << "\n";

    return 0;
}