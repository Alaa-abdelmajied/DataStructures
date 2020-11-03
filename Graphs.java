import java.util.*;

public class Graphs {

    public static void main(String[] args) {
        menu();
    }

    static void menu() {
        Scanner s = new Scanner(System.in);
        String ip = null;

        System.out.println("\n******************Main Menu**********************");
        System.out.println("-> 1- Part 1\n-> 2- Part 2\n-> 3- Part 3\n-> 4- Exit");
        System.out.println("*************************************************");
        System.out.print("Select Part: ");
        ip = s.nextLine();

        switch (ip) {
            case "1":
                LinkedInConnections linkedInConnections = new LinkedInConnections();
                linkedInConnections.findConnections();
                returnToMenu();
                break;

            case "2":
                MazeSolver mazeSolver = new MazeSolver();
                mazeSolver.mazeSolver();
                returnToMenu();
                break;

            case "3":
                TripMinCost tripMinCost = new TripMinCost();
                tripMinCost.minCost();
                returnToMenu();
                break;

            case "4":
                System.exit(0);
                break;

            default:
                System.err.println("Invalid Input");
                menu();
                break;
        }
    }

    static void returnToMenu() {

        Scanner s = new Scanner(System.in);
        System.out.print("\nPress Y to continue, anything else to exit: ");
        String choice = s.nextLine();

        if (choice.equalsIgnoreCase("Y")) {
            menu();

        } else {
            System.exit(0);
        }
    }
}
