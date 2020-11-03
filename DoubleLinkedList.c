#include <stdio.h>
#include <stdlib.h>
/*
 *
 */
typedef struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
} Node;
/*
 *
 */
typedef struct {
	Node* head;
	Node* tail;
} DoublyLinkedList;
/*
 *
 */
const DoublyLinkedList EmptyList = {NULL, NULL};
/*
 * convertArrayToDoublyLinkedList
 */
DoublyLinkedList convertArrayToDoublyLinkedList(int array[], int size) {
	DoublyLinkedList list = {NULL, NULL};
	int i;
    Node *node1 = NULL;
	for(i = 0; i<size ; i++){
        Node *node2 = malloc(sizeof(Node));
        node2->data = array[i];
        if(node1 == NULL){
            node1 = node2;
            node1->next = NULL;
            node1->prev = NULL;
            list.head = node1;
        }
        else if(i == size-1){
            node1->next = node2;
            node2->prev = node1;
            node2->next = NULL;
            list.tail = node2;
        }
        else{
            node1->next = node2;
            node2->prev = node1;
            node2->next = NULL;
            node1 = node2;
        }
	}
	return list;
}
/*
 * destroy
 */
void destroy(DoublyLinkedList* list) {
	Node *node = list->head ;
	while(node != NULL){
        Node *next = node->next;
        free(node);
        node = next;
	}
	list->head = NULL;
	list->tail = NULL;
}
/*
 * length: count the number of items stored in the list
 */
size_t length(DoublyLinkedList list) {
	size_t count = 0;
    Node *node = list.head;
    while(node != NULL){
        count++;
        node = node->next;
    }
	return count;
}
/*
 * duplicate
 */
DoublyLinkedList dup(DoublyLinkedList list) {
	DoublyLinkedList newlist = {NULL, NULL};
	int listSize = length(list);
	int array[listSize];
	int i = 0;
	while(list.head !=NULL){
        array[i] = list.head->data;
        list.head = list.head->next;
        i++;
	}
	newlist = convertArrayToDoublyLinkedList(array,listSize);
	return newlist;
}
/*
 * concatenate: concatenates the second list to the first one
 */
DoublyLinkedList concatenate(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList newlist = {NULL, NULL};
	if(list1.head == NULL)
        return list2;
    else if(list2.head == NULL)
        return list1;
    else if(list1.head == NULL && list2.head == NULL)
        return EmptyList;
    else{
        newlist.head = list1.head;
        list1.tail->next = list2.head;
        list2.head->prev = list1.tail;
        newlist.tail = list2.tail;
	return newlist;
    }
}
/*
 * isPalindrome: returns 1 if list is palindrome
 *               returns 0 if list is not palindrome
 *               a palindrome prints forwards as backwards
 *               e.g., 1 2 3 2 1
 *               e.g., 1 2 3 3 2 1
 */
int isPalindrome(DoublyLinkedList list) {
	Node *node1 = list.head;
	Node *node2 = list.tail;
	size_t x = length(list);
    while(x/2 > 0){
        if(node1->data == node2->data){
            node1 = node1->next;
            node2 = node2 ->prev;
        }
        else
            return 0;
        x--;
    }
    return 1;
}
/*
 * areEqual: returns 1 if both lists contain same elements
 *               returns 0 otherwise
 */
int areEqual(DoublyLinkedList list1, DoublyLinkedList list2) {
    Node *node1 = list1.head;
    Node *node2 = list2.head;
    while(node1 != NULL && node2 != NULL){
        if(node1->data == node2->data){
        node1 = node1->next;
        node2 = node2->next;
        }
        else{
            return 0;
        }
    }
    if(node1 == NULL && node2 == NULL){
        return 1;
    }
    else
        return 0;
}
/*
 * printlnListForward: prints the list {1, 3, 5, 7} as 1 3 5 7
 *                    prints end of line at the end
 */
void printlnListForward(DoublyLinkedList list) {
    Node *node = list.head;
    while(node != NULL){
        printf("%d ",node->data);
        node = node->next;
    }
	printf("\n");
}
/*
 * printlnListBackward: prints the list {1, 3, 5, 7} as 7 5 3 1
 *                    prints end of line at the end
 */
void printlnListBackward(DoublyLinkedList list) {
    Node *node = list.tail;
    while(node != NULL){
        printf("%d ",node->data);
        node = node->prev;
    }
	printf("\n");
}
/*
 *
 */
void Investigate(char* title, DoublyLinkedList list) {
	printf("%s\n", title);
	printf("List =         ");
	printlnListForward(list);
	printf("Reverse List = ");
	printlnListBackward(list);
	printf("List Length = %u\n", length(list));
	printf("List isPalindrome = %d\n", isPalindrome(list));
	printf("...................................................\n");
}
/*
 *
 */
void testConcatenate1(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList list3, list4, emptyList1;

	list3 = dup(list1);
	Investigate("List3 = dup(List1)\n==================", list3);
	emptyList1 = dup(EmptyList);
	Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
	DoublyLinkedList list5 = concatenate(list3, emptyList1);
	Investigate("List5 = List3<->EmptyList1\n==========================", list5);
	destroy(&list5);
	Investigate("List5 (after destroy)\n=====================", list5);
	//destroy(&list3);			//already destroyed when list5 got destroyed
	//destroy(&emptyList1);		//already destroyed when list5 got destroyed
}
/*
 *
 */
void testConcatenate2(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList list3, list4, emptyList1;
	list3 = dup(list1);
	emptyList1 = dup(EmptyList);
	DoublyLinkedList list6 = concatenate(emptyList1, list3);
	Investigate("List6 = EmptyList1<->List3\n==========================", list6);
	destroy(&list6);
	Investigate("List6 (after destroy)\n=====================", list6);
	//destroy(&list3);			//already destroyed when list6 got destroyed
	//destroy(&emptyList1);		//already destroyed when list6 got destroyed
}
/*
 *
 */
void testConcatenate3(DoublyLinkedList list1, DoublyLinkedList list2) {
	DoublyLinkedList list3, list4, emptyList1;

	list3 = dup(list1);
	list4 = dup(list2);
	DoublyLinkedList list7 = concatenate(list3, list4);
	Investigate("List7 = List3<->List4\n=====================", list7);
	destroy(&list7);
	Investigate("List7 (after destroy)\n=====================", list7);
	//destroy(&list3);			//already destroyed when list7 got destroyed
	//destroy(&list4);			//already destroyed when list7 got destroyed
}
/*
 *
 */
void testConcatenate() {
	int array1[] = {0, 1, 2, 3, 4, 5, 6};
	int array2[] = {7, 8, 9};

	DoublyLinkedList list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
	Investigate("List1\n=====", list1);
	DoublyLinkedList list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
	Investigate("List2\n=====", list2);

	testConcatenate1(list1, list2);
	testConcatenate2(list1, list2);
	testConcatenate3(list1, list2);

	destroy(&list1);
	destroy(&list2);
}
/*
 *
 */
void testPalindrome() {
	int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
	int array4[] = {7, 8, 9, 9, 8, 7};

	DoublyLinkedList list8 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
	Investigate("List8\n=====", list8);
	DoublyLinkedList list9 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
	Investigate("List9\n=====", list9);

	destroy(&list8);
	destroy(&list9);
}
/*
 *
 */
void testAreEqual() {
	int array5[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
	int array6[] = {7, 8, 9, 9, 8, 7};
	int array7[] = {0, 1, 2, 3, 4, 5};

	DoublyLinkedList list10 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
	Investigate("List10\n=====", list10);
	DoublyLinkedList list11 = convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
	Investigate("List11\n=====", list11);
	DoublyLinkedList list12 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
	Investigate("List12\n=====", list12);
	DoublyLinkedList emptyList1 = dup(EmptyList);
	Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
	DoublyLinkedList emptyList2 = dup(EmptyList);
	Investigate("EmptyList2 = dup(EmptyList)\n===========================", emptyList2);

	printf("areEqual(List10, List10) = %d\n", areEqual(list10, list10));
	printf("areEqual(List10, List11) = %d\n", areEqual(list10, list11));
	printf("areEqual(List10, List12) = %d\n", areEqual(list10, list12));
	printf("areEqual(List11, List10) = %d\n", areEqual(list11, list10));
	printf("areEqual(List10, EmptyList1) = %d\n", areEqual(list10, emptyList1));
	printf("areEqual(EmptyList1, List10) = %d\n", areEqual(emptyList1, list10));
	printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

	destroy(&list10);
	destroy(&list11);
	destroy(&list12);

}
/*
 *
 */
main() {
	testConcatenate();
	testPalindrome();
	testAreEqual();
	return 0;
}
