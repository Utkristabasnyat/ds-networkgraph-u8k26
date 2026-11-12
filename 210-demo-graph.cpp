
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    // Adjacency list for the graph
    vector<vector<Pair>> adjList;

    // Graph constructor
    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        // Add edges in both directions
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;

        for (int i = 0; i < SIZE; i++) {
            cout << i << " --> ";

            for (Pair v : adjList[i]) {
                cout << "(" << v.first << ", "
                     << v.second << ") ";
            }

            cout << endl;
        }
    }

    // Depth-First Search using a stack
    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> nodes;

        nodes.push(start);

        cout << "DFS starting from vertex "
             << start << ":" << endl;

        while (!nodes.empty()) {
            int current = nodes.top();
            nodes.pop();

            if (visited[current]) {
                continue;
            }

            visited[current] = true;
            cout << current << " ";

            // Push neighbors onto the stack
            for (Pair neighbor : adjList[current]) {
                if (!visited[neighbor.first]) {
                    nodes.push(neighbor.first);
                }
            }
        }

        cout << endl;
    }

    // Breadth-First Search using a queue
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> nodes;

        visited[start] = true;
        nodes.push(start);

        cout << "BFS starting from vertex "
             << start << ":" << endl;

        while (!nodes.empty()) {
            int current = nodes.front();
            nodes.pop();

            cout << current << " ";

            // Visit neighbors in adjacency-list order
            for (Pair neighbor : adjList[current]) {
                int next = neighbor.first;

                if (!visited[next]) {
                    visited[next] = true;
                    nodes.push(next);
                }
            }
        }

        cout << endl;
    }
};

int main() {
    // Professor's original weighted graph
    vector<Edge> edges = {
        {0,1,12}, {0,2,8}, {0,3,21},
        {2,3,6}, {2,6,2}, {5,6,6},
        {4,5,9}, {2,4,4}, {2,5,5}
    };

    // Create the graph
    Graph graph(edges);

    // Display the adjacency list
    graph.printGraph();

    // Test DFS and BFS
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
