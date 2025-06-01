#include <iostream>
#include <vector>
using namespace std;

class DependencyChecker {
public:
    bool hasCircularDependency(int n, vector<vector<int>>& edges) {
        // build adjacency list
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
        }

        vector<int> visited(n, 0); // 0 = unvisited, 1 = visiting, 2 = visited

        // check all components for cycles
        for (int i = 0; i < n; ++i) {
            if (visited[i] == 0 && dfs(i, graph, visited)) {
                return true; // cycle found
            }
        }
        return false; // no cycles found
    }

private:
    bool dfs(int node, vector<vector<int>>& graph, vector<int>& visited) {
        visited[node] = 1; // mark as visiting

        for (int neighbor : graph[node]) {
            if (visited[neighbor] == 1) return true; // cycle found
            if (visited[neighbor] == 0 && dfs(neighbor, graph, visited)) {
                return true;
            }
        }

        visited[node] = 2; // mark as visited
        return false;
    }
};

int main() {
    int n, e;
    cout << "Enter number of modules (n): ";
    cin >> n;

    cout << "Enter number of dependencies (edges): ";
    cin >> e;

    vector<vector<int>> edges;
    cout << "Enter each dependency as two space-separated integers (a b):\n";
    for (int i = 0; i < e; ++i) {
        int a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }

    DependencyChecker checker;
    bool result = checker.hasCircularDependency(n, edges);
    cout << "Contains circular dependency? " << (result ? "true" : "false") << endl;

    return 0;
}
