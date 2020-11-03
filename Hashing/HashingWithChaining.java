import java.util.ArrayList;

public class Chaining {

    public int hashFunction(int number) {

        return number % 13;
    }

    public void insert(int number, ArrayList<Integer>[] hash) {

        int index = hashFunction(number);
        if (hash[index] == null) {
            hash[index] = new ArrayList<Integer>();
        }
        hash[index].add(number);
    }

    public boolean search(int number, ArrayList<Integer>[] hash) {

        int index = hashFunction(number);
        if (hash[index] == null) {
            return false;
        } else {
           return hash[index].contains(number);
        }
    }

    public static void main(String[] args) {

        Chaining chaining = new Chaining();
        ArrayList<Integer>[] hash = new ArrayList[13];
        chaining.insert(18, hash);
        chaining.insert(41, hash);
        chaining.insert(22, hash);
        chaining.insert(44, hash);
        System.out.println(chaining.search(44,hash));
    }
}

