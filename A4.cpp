  #include <iostream>
using namespace std;

class Set {
    public:
        static const int MAX = 5;
        int A[MAX], sizeA;
        int B[MAX], sizeB;
        int C[2 * MAX], sizeC;  // For Union
        int D[2 * MAX], sizeD;  // For Intersection
        int R[2 * MAX], sizeR;  // For Difference

        Set() {
            sizeA = sizeB = sizeC = sizeD = sizeR = 0;
            for (int i = 0; i < MAX; i++) {
                A[i] = B[i] = 0;
            }
            for (int i = 0; i < 2 * MAX; i++) {
                C[i] = D[i] = R[i] = 0;
            }
        }

        void Add(int x) {
            if (sizeA >= MAX) return;
            for (int i = 0; i < sizeA; i++) {
                if (A[i] == x) return; // no duplicates
            }
            A[sizeA++] = x;
        }

        void Add1(int x) {
            if (sizeB >= MAX) return;
            for (int i = 0; i < sizeB; i++) {
                if (B[i] == x) return; // no duplicates
            }
            B[sizeB++] = x;
        }

        void remove() {
            char s;
            int el;
            cout << "From which array do you want to delete the element (F/f for first, S/s for second): ";
            cin >> s;
            cout << "Enter the element to delete: ";
            cin >> el;

            if (s == 'F' || s == 'f') {
                for (int i = 0; i < sizeA; i++) {
                    if (A[i] == el) {
                        for (int j = i; j < sizeA - 1; j++) {
                            A[j] = A[j + 1];
                        }
                        sizeA--;
                        return;
                    }
                }
                cout << "Element not found in A.\n";
            } else if (s == 'S' || s == 's') {
                for (int i = 0; i < sizeB; i++) {
                    if (B[i] == el) {
                        for (int j = i; j < sizeB - 1; j++) {
                            B[j] = B[j + 1];
                        }
                        sizeB--;
                        return;
                    }
                }
                cout << "Element not found in B.\n";
            } else {
                cout << "Invalid choice.\n";
            }
        }

        void Union() {
            sizeC = 0;
            for (int i = 0; i < sizeA; i++) {
                C[sizeC++] = A[i];
            }
            for (int i = 0; i < sizeB; i++) {
                bool found = false;
                for (int j = 0; j < sizeA; j++) {
                    if (B[i] == A[j]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    C[sizeC++] = B[i];
                }
            }
        }

        void Intersection() {
            sizeD = 0;
            for (int i = 0; i < sizeB; i++) {
                for (int j = 0; j < sizeA; j++) {
                    if (B[i] == A[j]) {
                        D[sizeD++] = B[i];
                        break;
                    }
                }
            }
        }

        void Difference() {
            int choice;
            cout << "For (A - B) type 1, for (B - A) type 0: ";
            cin >> choice;
            sizeR = 0;

            if (choice == 1) {
                for (int i = 0; i < sizeA; i++) {
                    bool found = false;
                    for (int j = 0; j < sizeB; j++) {
                        if (A[i] == B[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) R[sizeR++] = A[i];
                }
                cout << "Difference A - B is: ";
            } else {
                for (int i = 0; i < sizeB; i++) {
                    bool found = false;
                    for (int j = 0; j < sizeA; j++) {
                        if (B[i] == A[j]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) R[sizeR++] = B[i];
                }
                cout << "Difference B - A is: ";
            }
        }

        void Display(int arr[], int size) {
            for (int i = 0; i < size; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }

        void Iterators() {
            cout << "Size of A: " << sizeA << endl;
            cout << "Size of B: " << sizeB << endl;
        }
};

int main() {
    Set s;
    int ch;

    while (true) {
        cout << "\n1. Add to A\n2. Add to B\n3. Display A\n4. Display B\n5. Union\n6. Intersection\n7. Delete\n8. Iterators\n9. Difference\n10. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        if (ch == 1) {
            int n, x;
            cout << "Enter number of elements to add to A (max 5): ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cin >> x;
                s.Add(x);
            }
        } else if (ch == 2) {
            int m, y;
            cout << "Enter number of elements to add to B (max 5): ";
            cin >> m;
            for (int i = 0; i < m; i++) {
                cin >> y;
                s.Add1(y);
            }
        } else if (ch == 3) {
            cout << "Array A: ";
            s.Display(s.A, s.sizeA);
        } else if (ch == 4) {
            cout << "Array B: ";
            s.Display(s.B, s.sizeB);
        } else if (ch == 5) {
            s.Union();
            cout << "Union of A and B: ";
            s.Display(s.C, s.sizeC);
        } else if (ch == 6) {
            s.Intersection();
            cout << "Intersection of A and B: ";
            s.Display(s.D, s.sizeD);
        } else if (ch == 7) {
            s.remove();
        } else if (ch == 8) {
            s.Iterators();
        } else if (ch == 9) {
            s.Difference();
            s.Display(s.R, s.sizeR);
        } else if (ch == 10) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
 