#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
    char* cName;
    double balance;
    int order;
} Item;
/*
 * Heapify index i in array of Items with size n
 */
void max_heapify(Item *arr, int n, int i)
{
    int largest;
    Item temp;
    int left = 2*i+1;
    int right = 2*i+2;
    if (left < n && arr[left].balance > arr[i].balance)
        largest = left;
    else
        largest = i;
    if(left < n && arr[left].balance == arr[largest].balance && arr[left].order < arr[largest].order)
            largest = left;
    if (right < n && arr[right].balance > arr[largest].balance)
        largest = right;
    if(right < n && arr[right].balance == arr[largest].balance && arr[right].order < arr[largest].order)
        largest = right;
    if (largest != i)
    {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        max_heapify(arr,n,largest);
    }

}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{
    int i;
    for(i = (n- 1)/2  ; i >= 0 ; i--){
        max_heapify(arr,n,i);
    }
}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item*arr,int n)
{
    Item temp = arr[0];
    arr[0] = arr[n-1];
    arr[n-1] = temp;
    max_heapify(arr,n-1,0);
    return arr[n-1];
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
    FILE *fp;
    fp = fopen(fname, "r");
    int i = 0;
    char str[20];
    char *token;
    int j=1;
    while (fgets (str, 60, fp)!=NULL)
    {
            token = strtok(str," ");
            arr[i].cName =  malloc(sizeof(char)*100);
            strcpy(arr[i].cName,token);
            token = strtok(NULL, " ");
            arr[i].balance = atof(token);
            arr[i].order = j++;
            i++;
    }
    fclose(fp);
    return i;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
    int i;
    Item item;
    int j = 1;
    printf("Serving order\tEntering order\tName\t\tBalance\n");
    printf("------------------------------------------------------------\n");
    for(i = n ; i > 0 ; i--){
       item =  extract_maximum(arr,i);
        printf("%d\t\t%d\t\t%s\t\t%0.1lf\n",j,item.order,item.cName,item.balance);
        j++;
    }
}
/*
 *
 */
int main(int argc, char**argv)
{

    if(argc!=2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
