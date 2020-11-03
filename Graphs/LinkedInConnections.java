import java.util.*;

public class LinkedInConnections {

    Scanner scanner = new Scanner(System.in);

    public LinkedList<Integer>[] createGraph() {

        System.out.println("Please enter number of vertices:");
        int vertex = scanner.nextInt();
        LinkedList<Integer>[] graph = new LinkedList[vertex];
        System.out.println("Please enter number of edges:");
        int edges = scanner.nextInt();
        System.out.println("Please enter edges in the form (u v):");
        int v1;
        int v2;
        for (int i = 0; i < edges; i++) {
            v1 = scanner.nextInt() - 1;
            v2 = scanner.nextInt() - 1;
            if (graph[v1] == null) {
                graph[v1] = new LinkedList<>();
            }
            if (graph[v2] == null) {
                graph[v2] = new LinkedList<>();
            }
            graph[v1].add(v2);
            graph[v2].add(v1);
        }
        return graph;
    }

    public int BFS(LinkedList<Integer>[] graph, int startVertex, int k) {

        boolean visited[] = new boolean[graph.length];
        Queue<Integer> queue = new LinkedList<>();
        int dummy = -1;
        visited[startVertex] = true;
        queue.add(startVertex);
        queue.add(dummy);
        int count = 0;
        while (!queue.isEmpty() && k != 0) {
            startVertex = queue.poll();
            if (startVertex != dummy) {
                Iterator<Integer> iterator = graph[startVertex].listIterator();
                while (iterator.hasNext()) {
                    int n = iterator.next();
                    if (!visited[n]) {
                        visited[n] = true;
                        queue.add(n);
                    }
                }
            } else {
                if (k - 1 != 0) {
                    queue.add(dummy);
                    k--;
                } else {
                    count = queue.size();
                    k--;
                }
            }
        }
        return count;
    }

    public void findConnections() {

        LinkedList<Integer>[] graph = createGraph();
        System.out.println("Please enter starting vertex:");
        int startVertex = scanner.nextInt();
        if (graph[startVertex] == null) {
            System.out.println("Error!");
            return;
        }
        System.out.println("Please enter value k :");
        int k = scanner.nextInt();
         System.out.println("There are " + BFS(graph, startVertex - 1, k) + " people with " + k +
                " connections away starting from " + startVertex);
    }
}
