#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

#define MAX 10

int w[MAX][MAX], c[MAX][MAX], r[MAX][MAX];
float p[MAX], q[MAX];
char idnt[MAX][10];
int n;

// Function declarations
int find(int i, int j);
void print(int i, int j);

int main() {
    cout << "Enter the number of identifiers: ";
    cin >> n;

    cout << "\nEnter identifiers:\n";
    for (int i = 1; i <= n; i++) {
        cout << "Identifier " << i << ": ";
        cin >> idnt[i];
    }

    cout << "\nEnter success probabilities p[i] (for each identifier):\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    cout << "\nEnter failure probabilities q[i] (for gaps):\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> q[i];
    }

    // Initialize weight, cost and root matrices
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
        if (i != n) {
            w[i][i + 1] = q[i] + p[i + 1] + q[i + 1];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }
    }

    for (int m = 2; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            int k = find(i, j);
            r[i][j] = k;
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
        }
    }

    cout << "\nRoot of OBST: " << r[0][n] << " (" << idnt[r[0][n]] << ")";
    cout << "\nCost of OBST: " << fixed << setprecision(2) << c[0][n] << "\n";

    cout << "\nPreorder traversal of OBST:\n";
    print(0, n);
    cout << "\n";

    return 0;
}

// Finds optimal root index for subtree (i, j)
int find(int i, int j) {
    int min = INT_MAX;
    int k = i + 1;
    for (int m = i + 1; m <= j; m++) {
        int cost = c[i][m - 1] + c[m][j];
        if (cost < min) {
            min = cost;
            k = m;
        }
    }
    return k;
}

// Preorder traversal (print structure)
void print(int i, int j) {
    if (i >= j) return;
    int root = r[i][j];
    cout << idnt[root] << " ";
    print(i, root - 1);
    print(root, j);
}

