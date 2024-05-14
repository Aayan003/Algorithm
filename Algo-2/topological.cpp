#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class Stack {
private:
    Node* top;
public:
    Stack() : top(nullptr) {}

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(int data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            cerr << "Stack underflow\n";
            return -1;
        }
        int data = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class Graph {
private:
    int vertexCount;
    vector<vector<int>> adjMatrix;
    vector<char> colour;
    vector<int> parent;
    vector<int> discoveryTime;
    vector<int> finishTime;
    Stack stack;

    void dfsVisit(int start);

public:
    int time;

    Graph(int vertexCount) : vertexCount(vertexCount), adjMatrix(vertexCount, vector<int>(vertexCount, 0)),
                             colour(vertexCount, 'W'), parent(vertexCount, -1), discoveryTime(vertexCount, 0),
                             finishTime(vertexCount, 0), stack() {}

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
    }

    void DFS();

    vector<int> getTopologicalSort();
};


void Graph :: dfsVisit(int start) {
        discoveryTime[start] = ++time;
        colour[start] = 'G';
        for (int i = 0; i < vertexCount; i++) {
            if (adjMatrix[start][i] == 1 && colour[i] == 'W') {
                parent[i] = start;
                dfsVisit(i);
            }
        }
        finishTime[start] = ++time;
        colour[start] = 'B';
        stack.push(start);
    }

void Graph :: DFS() {
        time = 0;
        for (int i = 0; i < vertexCount; i++) {
            if (colour[i] == 'W') {
                dfsVisit(i);
            }
        }
    }

vector<int> Graph :: getTopologicalSort() {
        vector<int> result;
        while (!stack.isEmpty()) {
            result.push_back(stack.pop());
        }
        return result;
    }

int main() {
    int vertex, edge;
    cout << "Number of vertices: ";
    cin >> vertex;
    cout << "\nNumber of edges: ";
    cin >> edge;

    Graph DFS(vertex);

    for (int i = 0; i < edge; i++) {
        int u, v;
        cout << "Edge between u & v vertices:\n";
        cout << "u: ";
        cin >> u;
        cout << "v: ";
        cin >> v;
        DFS.addEdge(u - 1, v - 1);
    }

    DFS.DFS();

    cout << "\nTopological Sort:\n";
    vector<int> sortedVertices = DFS.getTopologicalSort();
    for (int i = 0; i < sortedVertices.size(); i++) {
        cout << sortedVertices[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}
