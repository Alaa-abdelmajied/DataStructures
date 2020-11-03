import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;

public class MazeSolver {

    public int[][] createMaze() {

        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the number of vertices:");
        int vertex = scanner.nextInt();
        int[][] maze = new int[vertex][vertex];
        System.out.println("Please enter the values for the maze:");
        for (int i = 0; i < vertex; i++) {
            for (int j = 0; j < vertex; j++) {
                maze[i][j] = scanner.nextInt();
            }
        }
        return maze;
    }

    public void makeMove(ArrayList<Integer> path, Stack<Integer> stepBack, int newX, int newY, int x, int y) {

        path.add(newX);
        path.add(newY);
        stepBack.push(x);
        stepBack.push(y);

    }

    public ArrayList<Integer> getPath(int[][] maze) {

        ArrayList<Integer> path = new ArrayList<>();
        if (maze[0][0] == 1 || maze[maze.length - 1][maze.length - 1] == 1) {
            path.add(0, -1);
            return path;
        }
        boolean[][] visited = new boolean[maze.length][maze.length];
        int x = 0;
        int y = 0;
        path.add(x);
        path.add(y);
        Stack<Integer> stepBack = new Stack<>();
        boolean moved;
        visited[x][y] = true;
        stepBack.push(x);
        stepBack.push(y);
        while (!visited[maze.length - 1][maze.length - 1]) {
            moved = false;
            if (x + 1 < maze.length && !moved) {
                if (maze[x + 1][y] == 0 && !visited[x + 1][y]) {
                    //down move
                    makeMove(path, stepBack, x + 1, y, x, y);
                    visited[++x][y] = true;
                    moved = true;
                }
            }
            if (y + 1 < maze.length && !moved) {
                if (maze[x][y + 1] == 0 && !visited[x][y + 1]) {
                    //right move
                    makeMove(path, stepBack, x, y + 1, x, y);
                    visited[x][++y] = true;
                    moved = true;
                }
            }
            if (x - 1 < maze.length && x - 1 > 0 && !moved) {
                if (maze[x - 1][y] == 0 && !visited[x - 1][y]) {
                    //up move
                    makeMove(path, stepBack, x - 1, y, x, y);
                    visited[--x][y] = true;
                    moved = true;
                }
            }
            if (y - 1 < maze.length && y - 1 > 0 && !moved) {
                if (maze[x][y - 1] == 0 && !visited[x][y - 1]) {
                    //left move
                    makeMove(path, stepBack, x, y - 1, x, y);
                    visited[x][--y] = true;
                    moved = true;
                }
            }
            if (!moved) {
                if (!stepBack.isEmpty()) {
                    //dead end
                    y = stepBack.pop();
                    x = stepBack.pop();
                    path.remove(path.size() - 1);
                    path.remove(path.size() - 1);
                } else {
                    path.add(0, -1);
                    return path;
                }
            }
        }
        return path;
    }

    public void mazeSolver() {

        int[][] maze = createMaze();
        double start = System.nanoTime();
        ArrayList<Integer> solution = getPath(maze);
        double end = System.nanoTime();
        double time = end - start;

        if (solution.get(0) != -1) {
            System.out.println("Solution:");
            for (int i = 0; i < solution.size(); i++) {
                System.out.print("(" + solution.get(i) + "," + solution.get(++i) + ")" + ",");
            }
            System.out.println("\b");
        } else {
            System.out.println("No path found!");
        }
        System.out.println("Time Taken = " + time / 1000000 + " milliseconds");
    }
}
