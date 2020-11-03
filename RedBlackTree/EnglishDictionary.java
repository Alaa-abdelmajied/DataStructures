import java.io.*;
import java.util.Scanner;

public class EnglishDictionary {

    RedBlackTree redBlackTree;
    int size = 0;

    public void loadDictionary() throws IOException {

        redBlackTree = new RedBlackTree();
        size = 0;
        File file = new File("dictionary.txt");
        FileReader fileReader = new FileReader(file);
        BufferedReader bufferedReader = new BufferedReader(fileReader);

        while (bufferedReader.ready()) {
            redBlackTree.insert(bufferedReader.readLine());
            size++;
        }

        System.out.println("\n\t\t****DONE LOADING****");
        dictionaryInfo();

        fileReader.close();
        bufferedReader.close();
    }

    public void writeIntoDictionary(String word) throws IOException {

        File file = new File("dictionary.txt");
        FileWriter fileWriter = new FileWriter(file, true);
        BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

        bufferedWriter.newLine();
        bufferedWriter.write(word);

        bufferedWriter.close();
        fileWriter.close();
    }

    public void dictionaryInfo() {

        System.out.println("\n-Current dictionary size: " + size);
        if (redBlackTree != null)
            System.out.println("-Current red black tree height: " + redBlackTree.printHeight());
        else
            System.out.println("-Current red black tree height: -1");
    }

    public void insertWord(String word) throws IOException {

        if (!redBlackTree.search(word)) {
            writeIntoDictionary(word);
            redBlackTree.insert(word);
            size++;
            System.out.println("\n-Word is successfully inserted.");
            dictionaryInfo();

        } else {
            System.out.println("\n-ERROR: Word already exists.");
        }
    }

    public void search(String word) {

        if (size > 0) {
            System.out.print("\n-Is the word available: ");
            if (redBlackTree.search(word))
                System.out.println("Yes");
            else
                System.out.println("No");
        } else
            System.out.println("ERROR: NO DATA LOADED!");
    }


    public void returnToMainMenu(String word) throws IOException, InterruptedException {

        if (word.compareTo("1") == 0) {
            userInterface();
        } else if (word.compareTo("0") == 0) {
            System.out.println("\n****Thank you for using our app****");
            System.exit(0);
        } else {
            System.out.println("WRONG CHOICE! PLEASE ENTER AGAIN");
            returnToMainMenu(word);
        }

    }

    public void options() {

        System.out.println("\n\t\t*********************************");
        System.out.println("\t\tWelcome to the English Dictionary");
        System.out.println("\t\t*********************************");
        System.out.println("\t\t\t\t\tMain Menu\n");

        System.out.println("1.Load Dictionary");
        System.out.println("2.Print Dictionary Size");
        System.out.println("3.Insert Word");
        System.out.println("4.Look up a Word");
        System.out.println("5.Exit");
        System.out.print("\n-Enter your choice(1-5): ");
    }

    public void userInterface() throws IOException, InterruptedException {

        options();
        Scanner scanner = new Scanner(System.in);
        int choice = Integer.parseInt(scanner.nextLine());
        String word;

        switch (choice) {

            case 1:
                loadDictionary();
                userInterface();
                break;

            case 2:
                dictionaryInfo();
                System.out.print("\n-Press 1 to return to main menu or 0 to exit: ");
                word = scanner.nextLine();
                returnToMainMenu(word);
                break;

            case 3:
                System.out.print("\n-Enter the word you want to insert: ");
                word = scanner.nextLine();
                insertWord(word);
                System.out.print("\n-Press 1 to return to main menu or 0 to exit: ");
                word = scanner.nextLine();
                returnToMainMenu(word);
                break;

            case 4:
                System.out.print("\n-Enter the word you want to find: ");
                word = scanner.nextLine();
                search(word);
                System.out.print("\n-Press 1 to return to main menu or 0 to exit: ");
                word = scanner.nextLine();
                returnToMainMenu(word);
                break;

            case 5:
                System.out.println("\n****Thank you for using our app****");
                System.exit(0);

            default:
                System.out.println("\nWRONG CHOICE! PLEASE ENTER AGAIN");
                userInterface();
                break;

        }
    }


    public static void main(String[] args) throws IOException, InterruptedException {

        EnglishDictionary englishDictionary = new EnglishDictionary();
        englishDictionary.userInterface();

    }
}
