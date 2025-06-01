import java.util.*;

public class DependencyChecker {

    public boolean hasCircularDependency(int n, List<List<Integer>> edges) {
        // create adjacency list
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) graph.add(new ArrayList<>());
        for (List<Integer> edge : edges) {
            graph.get(edge.get(0)).add(edge.get(1));
        }

        int[] visited = new int[n]; // 0 = unvisited, 1 = visiting, 2 = visited

        // check for cycles in each component
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0 && dfs(i, graph, visited)) {
                return true;
            }
        }
        return false;
    }

    // recursive DFS to detect cycle
    private boolean dfs(int node, List<List<Integer>> graph, int[] visited) {
        visited[node] = 1; // mark as visiting

        for (int neighbor : graph.get(node)) {
            if (visited[neighbor] == 1) return true; // cycle detected
            if (visited[neighbor] == 0 && dfs(neighbor, graph, visited)) {
                return true;
            }
        }

        visited[node] = 2; // mark as visited
        return false;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        DependencyChecker checker = new DependencyChecker();

        // take number of nodes from user
        System.out.print("Enter number of modules (n): ");
        int n = sc.nextInt();

        // take number of edges
        System.out.print("Enter number of dependencies (edges): ");
        int e = sc.nextInt();

        // collect edge list
        List<List<Integer>> edges = new ArrayList<>();
        System.out.println("Enter each dependency as two space-separated integers (a b):");
        for (int i = 0; i < e; i++) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            edges.add(Arrays.asList(a, b));
        }

        // check for cycle
        boolean result = checker.hasCircularDependency(n, edges);
        System.out.println("Contains circular dependency? " + result);
    }
}
