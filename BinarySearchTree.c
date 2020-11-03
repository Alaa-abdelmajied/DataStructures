#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node
{
    char data[100];
    struct Node *left;
    struct Node *right;
} node;


node* newNode(char *word)
{
    node *n = (node*)malloc(sizeof(node));
    strcpy(n->data,word);
    n->left = n->right = NULL;
    return n;
}

node* insert(node* root,char *data)
{
    if (root == NULL)
        root = newNode(data);

    if (strcmp(data, root->data)<0)
        root->left  = insert(root->left, data);

    else if (strcmp(data, root->data)>0)
        root->right = insert(root->right, data);

    return root;
}

int height(node *root)
{
    if(root == NULL)
        return -1;
    else
        return 1 + fmax(height(root->left), height(root->right));
}

int size(node* root)
{
    if (root == NULL)
        return 0;
    else
        return(size(root->left) + 1 + size(root->right));
}

node* inOrderSuccessor(node *root, node *word)
{
    node *node = NULL;

    if( word->right != NULL )
    {
        while (node->left != NULL)
            node = node->left;
    }

    while (root != NULL)
    {
        if (strcmp(word->data,root->data)<0)
        {
            node = root;
            root = root->left;
        }
        else if (strcmp(word->data,root->data)>0)
            root = root->right;
        else
            break;
    }

    return node;
}

node* inOrderPredecessor(node* root, node* word)
{
    node *node = NULL;

    if( word->left != NULL )
    {
        while(node->right!=NULL)
            node=node->right;
    }


    while (root != NULL)
    {
        if (strcmp(word->data,root->data)>0)
        {
            node = root;
            root = root->right;
        }
        else if (strcmp(word->data,root->data)<0)
            root = root->left;
        else
            break;
    }
    return node;
}

void search(node* root,char *data,node *treeRoot)
{

    if (strcmp(root->data,data) == 0)
        printf("%s - CORRECT\n",data);
    else if(root->left == NULL && root->right == NULL)
    {
        printf("%s - %s, %s, %s\n",data,root->data,inOrderSuccessor(treeRoot,root)->data,inOrderPredecessor(treeRoot,root)->data);
        return;
    }
    if (strcmp(data, root->data) < 0)
        search(root->left, data, treeRoot);
    else if (strcmp(data, root->data) > 0)
        search(root->right, data, treeRoot);
}


int main()
{
    FILE *fp;
    fp = fopen("EN-US-randomized-unique updated.txt", "r");
    char word[100];
    node *treeRoot;
    treeRoot = NULL;
    while (!feof(fp))
    {
        fscanf(fp, "%s\n", word);
        treeRoot = insert(treeRoot,word);
    }
    fclose(fp);
    printf("******************");
    printf("\nTree height: %d\n",height(treeRoot));
    printf("Tree size: %d\n",size(treeRoot));
    printf("\n******************\n");
    char input[50];
    printf("Input sentence: ");
    gets(input);
    char *token;
    token = strtok(input, " ");
    while(token != NULL)
    {
        search(treeRoot,token,treeRoot);
        token = strtok(NULL, " ");
    }

    return 0;
}
