import java.util.*;

public class TripMinCost {

    private class Vertex {

        int vertex;
        int time;
        int cost;
        Vertex parent;

        public Vertex(int vertex, int time, int cost, Vertex parent) {
            this.vertex = vertex;
            this.time = time;
            this.cost = cost;
            this.parent = parent;
        }

        public Vertex(int vertex, int time, int cost) {

            this.vertex = vertex;
            this.time = time;
            this.cost = time * cost;

        }
    }

    Comparator<Vertex> vertexComparator = new Comparator<Vertex>() {
        @Override
        public int compare(Vertex v1, Vertex v2) {

            if (v1.cost < v2.cost)
                return -1;
            if (v1.cost > v2.cost)
                return 1;
            return 0;
        }
    };


    public void minCost() {

        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter amount M:");
        int M = scanner.nextInt();
        LinkedList<Vertex>[] graph = createGraph(scanner);
        System.out.println("Please enter source city:");
        int source = scanner.nextInt() - 1;
        System.out.println("Please enter destination city:");
        int destination = scanner.nextInt() - 1;
        Vertex dest = dijkstra(graph, source, destination);
        printShortestPath(dest, destination, M);
    }

    public LinkedList<Vertex>[] createGraph(Scanner scanner) {

        System.out.println("Please enter number of cities:");
        int cities = scanner.nextInt();
        LinkedList<Vertex>[] graph = new LinkedList[cities];
        System.out.println("Please enter number of routes:");
        int routes = scanner.nextInt();
        System.out.println("Please enter source , destination " +
                "time and cost for each route:");
        int source;
        for (int i = 0; i < routes; i++) {
            source = scanner.nextInt() - 1;
            if (graph[source] == null) {
                graph[source] = new LinkedList<>();
            }
            graph[source].add(new Vertex(scanner.nextInt() - 1, scanner.nextInt(), scanner.nextInt()));
        }
        return graph;
    }

    public Vertex dijkstra(LinkedList<Vertex>[] graph, int source, int destination) {

        Vertex vertex;
        Vertex city;
        Vertex dest = null;
        int[] shortestPath = new int[graph.length];
        ArrayList<Integer> visited = new ArrayList<>();
        PriorityQueue<Vertex> vertices = new PriorityQueue<>(vertexComparator);
        Arrays.fill(shortestPath, Integer.MAX_VALUE);
        shortestPath[source] = 0;
        vertices.add(new Vertex(source, 0, 0, null));
        while (visited.size() != graph.length && !vertices.isEmpty() && !visited.contains(destination)) {
            city = vertices.remove();
            if (city.parent != null && city.vertex != destination) {
                city.time++;
            }
            if (city.vertex == destination) {
                dest = city;
            }
            visited.add(city.vertex);
            if (graph[city.vertex] != null) {
                for (int i = 0; i < graph[city.vertex].size(); i++) {
                    vertex = graph[city.vertex].get(i);
                    if (!visited.contains(vertex.vertex)) {
                        if (shortestPath[city.vertex] + vertex.cost < shortestPath[vertex.vertex]) {
                            shortestPath[vertex.vertex] = shortestPath[city.vertex] + vertex.cost;
                        }
                        vertices.add(new Vertex(vertex.vertex, vertex.time + city.time, shortestPath[vertex.vertex], city));
                    }
                }
            }
        }
        return dest;
    }

    public void printShortestPath(Vertex dest, int destination, int M) {
        if (dest == null) {
            System.out.println("No path found!");
        } else if (dest.parent != null) {
            printShortestPath(dest.parent, destination, M);
            System.out.print(" --> " + (dest.vertex + 1));
            if (dest.vertex == destination) {
                System.out.println("\nTotal time " + dest.time + " hours");
                System.out.println("Total cost = " + (dest.cost + (M * dest.time)) + "$");
            }
        } else {
            System.out.println("The route with minimum cost is:");
            System.out.print(dest.vertex + 1);
        }
    }
}
