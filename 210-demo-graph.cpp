
/*
    COMSC-210 Data Structures
    Lab 34: Network Graph I
    Step 2: Modify the graph
*/

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// Highest vertex number is 12, so we need 13 positions
const int SIZE = 13;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;
    vector<int> vertices;

    // Graph constructor
    Graph(vector<Edge> const &edges,
          vector<int> const &activeVertices) {

        adjList.resize(SIZE);
        vertices = activeVertices;

        // Add both directions for an undirected graph
        for (const Edge &edge : edges) {
            adjList[edge.src].push_back(
                make_pair(edge.dest, edge.weight));

            adjList[edge.dest].push_back(
                make_pair(edge.src, edge.weight));
        }
    }

    // Print only the vertices remaining in the graph
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;

        for (int vertex : vertices) {
            cout << vertex << " --> ";

            for (Pair neighbor : adjList[vertex]) {
                cout << "(" << neighbor.first << ", "
                     << neighbor.second << ") ";
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
    // Original vertices 3 and 4 have been removed.
    // Six new vertices 7 through 12 have been added.
    vector<int> vertices = {
        0, 1, 2, 5, 6, 7, 8, 9, 10, 11, 12
    };

    // Modified weights and new connections
    vector<Edge> edges = {
        // Remaining original connections, with new weights
        {0,1,9},
        {0,2,11},
        {2,6,4},
        {5,6,7},
        {2,5,10},

        // Connections involving the six new vertices
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

    Graph graph(edges, vertices);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}
