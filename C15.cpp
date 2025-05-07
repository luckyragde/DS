#include <iostream>
using namespace std;

class graph {
    int a[10][10], b[10][10];
    int n;

public:
    graph(int x) {
        n = x;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                a[i][j] = b[i][j] = 0; 
    }
    void prims() {
        int visited[n], from[n], dist[n];
        int sum = 0;
        for (int i = 0; i < n; i++) {
            visited[i] = 0;
            dist[i] = a[0][i];
            from[i] = 0;
        }
        visited[0] = 1;
        int edges = n - 1;
        while (edges > 0) {
            int min = 100, u = -1, v = -1;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && dist[i] < min) {
                    min = dist[i];
                    v = i;
                    u = from[v];
                }
            }

            if (u != -1 && v != -1) {
                b[u][v] = b[v][u] = min;
                sum += min;
                visited[v] = 1;
                edges--;

                for (int i = 0; i < n; i++) {
                    if (!visited[i] && a[i][v] < dist[i]) {
                        dist[i] = a[i][v];
                        from[i] = v;
                    }
                }
            }
        }
        cout << "The sum of the minimum spanning tree is: " << sum << endl;
    }

    void input() {
        cout << "Enter the adjacency matrix weights (Enter -1 for no edge):\n";
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) { 
                cout << "Enter the weight of the edge (" << i << "," << j << ") = ";
                cin >> a[i][j];

                if (a[i][j] == -1) {  
                    a[i][j] = a[j][i] = 100; 
                } else {
                    a[j][i] = a[i][j]; 
                }
            }
            a[i][i] = 0;  
        }
    }

    void display() {
        cout << "Minimum Spanning Tree Adjacency Matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
   
    graph g(n);
    g.input();
    g.prims();
    g.display();

    return 0;
}

