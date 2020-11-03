#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct
{
    char *name;
    int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node
{
    Item data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *first;
    Node *last;
} Queue;
/*
 *
 */
void init(Queue *q)
{
    q->first = NULL;
    q->last = NULL;
}
/*
 *
 */
int isEmpty(Queue *q)
{
    if(q->first == NULL)
        return 1;
    else
        return 0;
}
/*
 *
 */
Item dequeue(Queue *q)
{
    if(isEmpty(&q))
        return NULL;
    else
    {
        Item item;
        Node *newnode = q->first;
        item = newnode->data;
        q->first = q->first->next;
        free(newnode);
        return item;
    }
}
/*
 *
 */
void enqueue(Queue *q, Item val)
{
    Node *newnode = malloc(sizeof(Node));
    if(q->last== NULL)
    {
        newnode->data = val;
        q->first = q->last = newnode;
    }
    else
    {
        newnode->data = val;
        q->last->next = newnode;
        q->last = newnode;
    }
}
/*
 *
 */
void destroy(Queue *q)
{
    while(!isEmpty(&q))
    {
        Node *newnode = q->first;
        q->first = q->first->next;
        free(newnode);
    }
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    Queue q;
    init(&q);
    int i = 0, j = 0, x,y;
    Item item;
    int processes = 0,remaining = 0;
    char str[20];
    char name[10][5];
    int enter[10],remaningTime[10];
    char *token;
    FILE *fp = fopen(filename, "r");
    while( fgets (str, 60, fp)!=NULL )
    {
        token = strtok(str," ");
        strcpy(name[processes],token);
        token = strtok(NULL, " ");
        enter[processes] = atoi(token);
        token = strtok(NULL, " ");
        remaningTime[processes] = atoi(token);
        processes++;
    }
    fclose(fp);

    while(processes != 0)
    {
        while(enter[i]==0)
        {
            Process *p = malloc(sizeof(Process));
            p->name = name[i];
            p->remaining_time = remaningTime[i];
            enqueue(&q,p);
            i++;
            processes--;
        }
        remaining = processes;
        while(j < enter[i])
        {
            x = j;
            if(processes != -1)
            {
                item = dequeue(&q);
                item->remaining_time --;
                if(item->remaining_time > 0)
                {
                    printf("%s (%d-->%d)\n",item->name,x,x+1);
                    if(j != enter[i] - 1)
                        enqueue(&q,item);
                }
                else
                {
                    printf("%s (%d-->%d) %s halts\n",item->name,x,x+1,item->name);
                    remaining--;
                }
                j++;
            }
            else
            {
                printf("idle (%d-->%d)\n",x,x+1);
                j++;
            }
        }
        while(enter[i]==j)
        {
            Process *p = malloc(sizeof(Process));
            p->name = name[i];
            p->remaining_time = remaningTime[i];
            enqueue(&q,p);
            i++;
            y = processes;
            if(y != 1)
                processes--;

        }
        remaining += processes;
        if(y != 0)
            enqueue(&q,item);
        while(j < enter[i])
        {
            x = j;
            if(remaining != 0)
            {
                item = dequeue(&q);
                item->remaining_time --;
                if(item->remaining_time > 0)
                {
                    printf("%s (%d-->%d)\n",item->name,x,x+1);
                    if(j != enter[i] - 1)
                        enqueue(&q,item);
                }
                else
                {
                    printf("%s (%d-->%d) %s halts\n",item->name,x,x+1,item->name);
                    remaining--;
                }
                j++;
            }
            else
            {
                printf("idle (%d-->%d)\n",x,x+1);
                j++;
            }
        }
        while(enter[i]==j)
        {
            Process *p = malloc(sizeof(Process));
            p->name = name[i];
            p->remaining_time = remaningTime[i];
            enqueue(&q,p);
            i++;
            y = processes;
            if(y != 1)
                processes--;

        }
        remaining += processes;
        if(--y != 0)
            enqueue(&q,item);
        while(j < enter[i])
        {
            x = j;
            if(remaining != 0)
            {
                item = dequeue(&q);
                item->remaining_time --;
                if(item->remaining_time > 0)
                {
                    printf("%s (%d-->%d)\n",item->name,x,x+1);
                    if(j != enter[i] - 1)
                        enqueue(&q,item);
                }
                else
                {
                    printf("%s (%d-->%d) %s halts\n",item->name,x,x+1,item->name);
                    remaining--;
                    processes--;

                }
                j++;
            }
            else
            {
                printf("idle (%d-->%d)\n",x,x+1);
                j++;
            }
        }

    }
    printf("EOF\n");
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

    RoundRobin(argv[1]);

    return 0;
}
