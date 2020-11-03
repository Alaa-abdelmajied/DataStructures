public class DoubleHashing {

    public int hashFunction(int number) {

        return number % 13;
    }
    public int collisionResolution(int number) {

        return 7 - (number % 13);
    }

    public void insert(int number, int[] hash) {

        int index = hashFunction(number);
        if (hash[index] != 0) {
            int i = 1;
            while (hash[index] != 0 && i < 13) {
                index = hashFunction(number) + i * collisionResolution(number);
                index = index % 13;
                i++;
            }
        }
        hash[index] = number;

    }
    public boolean search(int number, int[] hash) {

        int index = hashFunction(number);
        if (hash[index] == number) {
            return true;
        } else {
            int i = 1;
            while (hash[index] != number && i < 13) {
                index = hashFunction(number) + i * collisionResolution(number);
                index = index % 13;
                i++;
            }
            if (hash[index] == number) {
                return true;
            } else {
                return false;
            }
        }
    }

    public static void main(String[] args) {

        DoubleHashing doubleHashing = new DoubleHashing();
        int hash[] = new int[13];
        doubleHashing.insert(18,hash);
        doubleHashing.insert(41,hash);
        doubleHashing.insert(22,hash);
        doubleHashing.insert(44,hash);
        System.out.println(doubleHashing.search(44,hash));

    }
}
