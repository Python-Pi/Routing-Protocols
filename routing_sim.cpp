// #include <iostream>
// #include <vector>
// #include <limits>
// #include <queue>
// #include <fstream>
// #include <sstream>
// #include <iomanip>

// using namespace std;

// const int INF = 9999;

// void printDVRTable(int node, const vector<vector<int>>& table, const vector<vector<int>>& nextHop) {
//     cout << "Node " << node << " Routing Table:\n";
//     cout << "Dest\tMetric\tNext Hop\n";
//     for (int i = 0; i < table.size(); ++i) {
//         cout << i << "\t" << table[node][i] << "\t";
//         if (nextHop[node][i] == -1) cout << "-";
//         else cout << nextHop[node][i];
//         cout << "\n";
//     }
//     cout << "\n";
// }

// void simulateDVR(const vector<vector<int>>& graph) {
//     int n = graph.size();
//     vector<vector<int>> dist = graph;
//     vector<vector<int>> nextHop(n, vector<int>(n));

//     for (int i = 0; i < n; ++i)
//         for (int j = 0; j < n; ++j)
//             nextHop[i][j] = (graph[i][j] != INF && i != j) ? j : -1;

//     bool updated;
//     do {
//         updated = false;
//         for (int u = 0; u < n; ++u) {
//             for (int v = 0; v < n; ++v) {
//                 for (int k = 0; k < n; ++k) {
//                     if (dist[u][k] != INF &&
//                         dist[k][v] != INF &&
//                         dist[u][v] > dist[u][k] + dist[k][v]) {
//                         dist[u][v] = dist[u][k] + dist[k][v];
//                         nextHop[u][v] = nextHop[u][k];
//                         updated = true;
//                     }
//                 }
//             }
//         }
//     } while (updated);

//     for (int i = 0; i < n; ++i)
//         printDVRTable(i, dist, nextHop);
// }

// void printLSRTable(int src, const vector<int>& dist, const vector<int>& prev) {
//     cout << "Node " << src << " Routing Table:\n";
//     cout << "Dest\tMetric\tNext Hop\n";
//     for (int i = 0; i < dist.size(); ++i) {
//         if (i == src) continue;
//         cout << i << "\t" << dist[i] << "\t";
//         int hop = i;
//         while (prev[hop] != src && prev[hop] != -1)
//             hop = prev[hop];
//         cout << (prev[hop] == -1 ? -1 : hop) << "\n";
//     }
//     cout << "\n";
// }

// void simulateLSR(const vector<vector<int>>& graph) {
//     int n = graph.size();
//     for (int src = 0; src < n; ++src) {
//         vector<int> dist(n, INF), prev(n, -1);
//         vector<bool> visited(n, false);
//         dist[src] = 0;

//         // Dijkstra
//         for (int i = 0; i < n; ++i) {
//             int u = -1;
//             for (int j = 0; j < n; ++j)
//                 if (!visited[j] && (u == -1 || dist[j] < dist[u]))
//                     u = j;
//             if (u == -1 || dist[u] == INF) break;
//             visited[u] = true;
//             for (int v = 0; v < n; ++v) {
//                 if (graph[u][v] != INF &&
//                     dist[v] > dist[u] + graph[u][v]) {
//                     dist[v] = dist[u] + graph[u][v];
//                     prev[v] = u;
//                 }
//             }
//         }

//         printLSRTable(src, dist, prev);
//     }
// }

// vector<vector<int>> readGraphFromFile(const string& filename) {
//     ifstream file(filename);
//     if (!file.is_open()) {
//         cerr << "Error: Could not open file " << filename << "\n";
//         exit(1);
//     }
//     int n; file >> n;
//     vector<vector<int>> graph(n, vector<int>(n));
//     for (int i = 0; i < n; ++i)
//       for (int j = 0; j < n; ++j) {
//         file >> graph[i][j];
//         if (i != j && graph[i][j] == 0)
//           graph[i][j] = INF;
//       }
//     return graph;
// }

// int main(int argc, char* argv[]) {
//     if (argc != 2) {
//         cerr << "Usage: " << argv[0] << " <input_file>\n";
//         return 1;
//     }
//     auto graph = readGraphFromFile(argv[1]);

//     cout << "\n--- Distance Vector Routing Simulation ---\n\n";
//     simulateDVR(graph);

//     cout << "--- Link State Routing Simulation ---\n\n";
//     simulateLSR(graph);

//     return 0;
// }

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

const int INF = 9999;

void printDVRTable(int node, const vector<vector<int>>& table, const vector<vector<int>>& nextHop) {
    cout << "Node " << node << " Routing Table:\n";
    cout << "Dest\tMetric\tNext Hop\n";
    for (int i = 0; i < table.size(); ++i) {
        cout << i << "\t" << table[node][i] << "\t";
        if (nextHop[node][i] == -1) cout << "-";
        else cout << nextHop[node][i];
        cout << "\n";
    }
    cout << "\n";
}

void simulateDVR(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;
    vector<vector<int>> nextHop(n, vector<int>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            nextHop[i][j] = (graph[i][j] != INF && i != j) ? j : -1;

    bool updated;
    int iteration = 0;
    do {
        cout << "Iteration " << iteration << ":\n";
        for (int i = 0; i < n; ++i)
            printDVRTable(i, dist, nextHop);
        iteration++;

        updated = false;
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                for (int k = 0; k < n; ++k) {
                    if (dist[u][k] != INF &&
                        dist[k][v] != INF &&
                        dist[u][v] > dist[u][k] + dist[k][v]) {
                        dist[u][v] = dist[u][k] + dist[k][v];
                        nextHop[u][v] = nextHop[u][k];
                        updated = true;
                    }
                }
            }
        }

    } while (updated);

    cout << "Final Distance Vector Routing Tables:\n";
    for (int i = 0; i < n; ++i)
        printDVRTable(i, dist, nextHop);
}

void printLSRTable(int src, const vector<int>& dist, const vector<int>& prev) {
    cout << "Node " << src << " Routing Table:\n";
    cout << "Dest\tMetric\tNext Hop\n";
    for (int i = 0; i < dist.size(); ++i) {
        if (i == src) continue;
        cout << i << "\t" << dist[i] << "\t";
        int hop = i;
        while (prev[hop] != src && prev[hop] != -1)
            hop = prev[hop];
        cout << (prev[hop] == -1 ? -1 : hop) << "\n";
    }
    cout << "\n";
}

void simulateLSR(const vector<vector<int>>& graph) {
    int n = graph.size();
    for (int src = 0; src < n; ++src) {
        vector<int> dist(n, INF), prev(n, -1);
        vector<bool> visited(n, false);
        dist[src] = 0;

        // Dijkstra
        for (int i = 0; i < n; ++i) {
            int u = -1;
            for (int j = 0; j < n; ++j)
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                    u = j;
            if (u == -1 || dist[u] == INF) break;
            visited[u] = true;
            for (int v = 0; v < n; ++v) {
                if (graph[u][v] != INF &&
                    dist[v] > dist[u] + graph[u][v]) {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;
                }
            }
        }

        printLSRTable(src, dist, prev);
    }
}

vector<vector<int>> readGraphFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << "\n";
        exit(1);
    }
    int n; file >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) {
        file >> graph[i][j];
        if (i != j && graph[i][j] == 0)
          graph[i][j] = INF;
      }
    return graph;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }
    auto graph = readGraphFromFile(argv[1]);

    cout << "\n--- Distance Vector Routing Simulation ---\n\n";
    simulateDVR(graph);

    cout << "--- Link State Routing Simulation ---\n\n";
    simulateLSR(graph);

    return 0;
}
