
/*
    COMSC-210 Data Structures
    Lab 34: Network Graph I
    Step 3: Data Center Network Monitoring
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
using namespace std;

const int SIZE = 13;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;
    vector<int> vertices;
    vector<string> deviceNames;

    // Graph constructor
    Graph(vector<Edge> const &edges,
          vector<int> const &activeVertices,
          vector<string> const &names) {

        adjList.resize(SIZE);
        vertices = activeVertices;
        deviceNames = names;

        // Create undirected network connections
        for (const Edge &edge : edges) {
            adjList[edge.src].push_back(
                make_pair(edge.dest, edge.weight));

            adjList[edge.dest].push_back(
                make_pair(edge.src, edge.weight));
        }
    }

    // Display the data center network
    void printGraph() {
        cout << "Data Center Network Topology:\n";
        cout << "================================\n";

        for (int vertex : vertices) {
            cout << "Device " << vertex << " ("
                 << deviceNames[vertex]
                 << ") connects to:\n";

            for (Pair neighbor : adjList[vertex]) {
                cout << "    -> Device "
                     << neighbor.first << " ("
                     << deviceNames[neighbor.first]
                     << ") - Latency: "
                     << neighbor.second << " ms\n";
            }
        }
    }

    // DFS: Inspect connected devices deeply
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> nodes;

        nodes.push(start);

        cout << "\nNetwork Inspection (DFS) from Device "
             << start << " (" << deviceNames[start]
             << "):\n";

        cout << "Purpose: Explore connected devices "
             << "during a network inspection\n";
        cout << "================================\n";

        while (!nodes.empty()) {
            int current = nodes.top();
            nodes.pop();

            if (visited[current]) {
                continue;
            }

            visited[current] = true;

            cout << "Inspecting Device " << current
                 << " (" << deviceNames[current]
                 << ")\n";

            for (Pair neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    nodes.push(neighbor.first);
                }
            }
        }
    }

    // BFS: Discover devices layer by layer
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> nodes;

        visited[start] = true;
        nodes.push(start);

        cout << "\nNetwork Discovery (BFS) from Device "
             << start << " (" << deviceNames[start]
             << "):\n";

        cout << "Purpose: Discover devices by "
             << "connection hops\n";
        cout << "================================\n";

        while (!nodes.empty()) {
            int current = nodes.front();
            nodes.pop();

            cout << "Checking Device " << current
                 << " (" << deviceNames[current]
                 << ")\n";

            for (Pair neighbor : adjList[current]) {
                int next = neighbor.first;

                if (!visited[next]) {
                    visited[next] = true;
                    nodes.push(next);

                    cout << "    -> Discovered Device "
                         << next << " ("
                         << deviceNames[next]
                         << ") - Link latency: "
                         << neighbor.second << " ms\n";
                }
            }
        }
    }
};

int main() {
    // Step 2 graph: 2 removed, 6 added
    vector<int> vertices = {
        0, 1, 2, 5, 6, 7, 8, 9, 10, 11, 12
    };

    // Same network connections and weights as Step 2
    vector<Edge> edges = {
        {0,1,9},
        {0,2,11},
        {2,6,4},
        {5,6,7},
        {2,5,10},
        {1,7,6},
        {7,8,3},
        {8,9,5},
        {9,10,8},
        {10,11,2},
        {11,12,4},
        {12,5,12},
        {6,9,9},
        {2,8,7},
        {1,10,14},
        {7,12,13}
    };

    // Device names correspond to vertex IDs
    vector<string> deviceNames(SIZE);

    deviceNames[0] = "Main Router";
    deviceNames[1] = "Firewall";
    deviceNames[2] = "Core Switch";
    deviceNames[5] = "Database Server";
    deviceNames[6] = "Application Server";
    deviceNames[7] = "Security Switch";
    deviceNames[8] = "Distribution Switch";
    deviceNames[9] = "Backup Router";
    deviceNames[10] = "Web Server";
    deviceNames[11] = "Storage Server";
    deviceNames[12] = "Backup Server";

    // Create the data center network
    Graph network(edges, vertices, deviceNames);

    // Display network topology
    network.printGraph();

    // Perform network inspection using DFS
    network.DFS(0);

    // Perform network discovery using BFS
    network.BFS(0);

    return 0;
}
