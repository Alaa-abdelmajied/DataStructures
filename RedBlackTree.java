public class RedBlackTree {

    private Node root = null;

    public void insert(String word) {
        Node node = new Node(word);
        root = insert(root, node);
        fixViolation(node);
    }

    private Node insert(Node root, Node node) {

        if (root == null)
            return node;
        if (node.getWord().compareToIgnoreCase(root.getWord()) < 0) {
            root.setLeftChild(insert(root.getLeftChild(), node));
            root.getLeftChild().setParent(root);
        } else {
            root.setRightChild(insert(root.getRightChild(), node));
            root.getRightChild().setParent(root);
        }
        return root;
    }

    private void fixViolation(Node node) {

        Node parent;
        Node grandParent;

        while (node != root && !node.isBlack() && !node.getParent().isBlack()) {

            parent = node.getParent();
            grandParent = node.getParent().getParent();

            if (parent == grandParent.getLeftChild()) {

                Node uncle = grandParent.getRightChild();

                if (uncle != null && !uncle.isBlack()) {
                    grandParent.setBlack(false);
                    parent.setBlack(true);
                    uncle.setBlack(true);
                    node = grandParent;
                } else {

                    if (node == parent.getRightChild()) {
                        leftRotate(parent);
                        node = parent;
                        parent = node.getParent();
                    }

                    rightRotate(grandParent);
                    boolean temp = parent.isBlack();
                    parent.setBlack(grandParent.isBlack());
                    grandParent.setBlack(temp);
                    node = parent;
                }
            } else {

                Node uncle = grandParent.getLeftChild();

                if(uncle != null && !uncle.isBlack()){
                    grandParent.setBlack(false);
                    parent.setBlack(true);
                    uncle.setBlack(true);
                    node = grandParent;
                } else {

                    if(node == parent.getLeftChild()){
                        rightRotate(parent);
                        node = parent;
                        parent = node.getParent();
                    }

                    leftRotate(grandParent);
                    boolean temp = parent.isBlack();
                    parent.setBlack(grandParent.isBlack());
                    grandParent.setBlack(temp);
                    node = parent;
                }
            }

        }
        if(!root.isBlack()){
            root.setBlack(true);
        }

    }

    private void leftRotate(Node node) {

        Node temp = node.getRightChild();
        node.setRightChild(temp.getLeftChild());

        if (node.getRightChild() != null)
            node.getRightChild().setParent(node);

        temp.setParent(node.getParent());

        if (temp.getParent() == null)
            root = temp;
        else if (node == node.getParent().getLeftChild())
            node.getParent().setLeftChild(temp);
        else
            node.getParent().setRightChild(temp);

        temp.setLeftChild(node);
        node.setParent(temp);
    }

    private void rightRotate(Node node) {

        Node temp = node.getLeftChild();
        node.setLeftChild(temp.getRightChild());

        if (node.getLeftChild() != null)
            node.getLeftChild().setParent(node);

        temp.setParent(node.getParent());

        if (temp.getParent() == null)
            root = temp;
        else if (node == node.getParent().getLeftChild())
            node.getParent().setLeftChild(temp);
        else
            node.getParent().setRightChild(temp);

        temp.setRightChild(node);
        node.setParent(temp);
    }

    private int height(Node root) {

        if (root == null)
            return -1;
        else
            return 1 + (Math.max(height(root.getLeftChild()), height(root.getRightChild())));
    }

    public int printHeight() {
        return height(root);
    }


    private boolean search(Node root, String word) {

        if (root == null)
            return false;
        if (word.compareToIgnoreCase(root.getWord()) == 0)
            return true;
        else if (word.compareToIgnoreCase(root.getWord()) < 0)
            return search(root.getLeftChild(), word);
        else
            return search(root.getRightChild(), word);
    }

    public boolean search(String word) {
        return search(root, word);
    }
}
