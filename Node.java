public class Node {

    private String word;
    private boolean black;
    private Node parent;
    private Node leftChild;
    private Node rightChild;

    public Node(String word) {
        this.word = word;
        black = false;
        parent = null;
        leftChild = null;
        rightChild = null;
    }

    public String getWord() {
        return word;
    }

    public boolean isBlack() {
        return black;
    }

    public void setBlack(boolean black) {
        this.black = black;
    }

    public Node getParent() {
        return parent;
    }

    public void setParent(Node parent) {
        this.parent = parent;
    }

    public Node getLeftChild() {
        return leftChild;
    }

    public void setLeftChild(Node leftChild) {
        this.leftChild = leftChild;
    }

    public Node getRightChild() {
        return rightChild;
    }

    public void setRightChild(Node rightChild) {
        this.rightChild = rightChild;
    }

}
