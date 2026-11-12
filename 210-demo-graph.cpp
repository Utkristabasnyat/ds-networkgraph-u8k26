
/*
    COMSC-210 Data Structures
    Lab 34: Network Graph I
    Step 5: Minimum Spanning Tree
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <limits>
#include <functional>
#include <algorithm>
using namespace std;

const int SIZE = 13;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

// Find the root of a vertex for Kruskal's algorithm
int findRoot(int vertex, vector<int> &parent) {
    if (parent[vertex] != vertex) {
        parent[vertex] = findRoot(parent[vertex], parent);
    }

    return parent[vertex];
}

class Graph {
public:
    vector<vector<Pair>> adjList;
    vector<int> vertices;
    vector<string> deviceNames;
    vector<Edge> connections;

    // Graph constructor
    Graph(vector<Edge> const &edges,
          vector<int> const &activeVertices,
          vector<string> const &names) {

        adjList.resize(SIZE);
        vertices = activeVertices;
        deviceNames = names;
        connections = edges;

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

    // DFS: Inspect connected network devices
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

    // BFS: Discover devices by connection hops
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

    // Dijkstra's shortest-path algorithm
    void shortestPaths(int start) {
        const int INF = numeric_limits<int>::max();

        vector<int> distance(SIZE, INF);
        distance[start] = 0;

        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int current = pq.top().second;
            pq.pop();

            if (currentDistance > distance[current]) {
                continue;
            }

            for (Pair neighbor : adjList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;

                int newDistance = currentDistance + weight;

                if (newDistance < distance[next]) {
                    distance[next] = newDistance;
                    pq.push(make_pair(newDistance, next));
                }
            }
        }

        cout << "\nShortest Network Paths from Device "
             << start << " (" << deviceNames[start]
             << "):\n";

        cout << "================================\n";

        for (int vertex : vertices) {
            cout << start << " -> " << vertex
                 << " (" << deviceNames[vertex] << ") : ";

            if (distance[vertex] == INF) {
                cout << "Unreachable\n";
            } else {
                cout << distance[vertex] << " ms\n";
            }
        }
    }

    // Kruskal's Minimum Spanning Tree algorithm
    void minimumSpanningTree() {
        // Sort connections by increasing weight
        vector<Edge> sortedEdges = connections;

        sort(sortedEdges.begin(), sortedEdges.end(),
             [](const Edge &a, const Edge &b) {
                 if (a.weight != b.weight) {
                     return a.weight < b.weight;
                 }
                 if (a.src != b.src) {
                     return a.src < b.src;
                 }
                 return a.dest < b.dest;
             });

        // Initially, each active vertex is its own group
        vector<int> parent(SIZE);

        for (int vertex : vertices) {
            parent[vertex] = vertex;
        }

        int totalWeight = 0;
        int edgeCount = 0;

        cout << "\nData Center Minimum Spanning Tree:\n";
        cout << "================================\n";

        // Select edges without creating cycles
        for (const Edge &edge : sortedEdges) {
            int rootSrc = findRoot(edge.src, parent);
            int rootDest = findRoot(edge.dest, parent);

            if (rootSrc != rootDest) {
                // Connect the two groups
                parent[rootSrc] = rootDest;

                cout << "Device " << edge.src
                     << " (" << deviceNames[edge.src]
                     << ") <-> Device " << edge.dest
                     << " (" << deviceNames[edge.dest]
                     << ") - Weight: "
                     << edge.weight << " ms\n";

                totalWeight += edge.weight;
                edgeCount++;

                // A spanning tree needs V - 1 edges
                if (edgeCount ==
                    static_cast<int>(vertices.size()) - 1) {
                    break;
                }
            }
        }

        cout << "================================\n";

        if (edgeCount ==
            static_cast<int>(vertices.size()) - 1) {
            cout << "Total MST weight: "
                 << totalWeight << "\n";
            cout << "Total MST edges: "
                 << edgeCount << "\n";
        } else {
            cout << "The network is disconnected. "
                 << "A complete MST cannot be formed.\n";
        }
    }
};

int main() {
    // Step 2: Two original vertices removed,
    // six new vertices added
    vector<int> vertices = {
        0, 1, 2, 5, 6, 7, 8, 9, 10, 11, 12
    };

    // Same 16 connections from previous steps
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

    Graph network(edges, vertices, deviceNames);

    // Previous functionality
    network.printGraph();
    network.DFS(0);
    network.BFS(0);
    network.shortestPaths(0);

    // New Step 5 functionality
    network.minimumSpanningTree();

    return 0;
}
