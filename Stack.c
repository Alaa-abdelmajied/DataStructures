#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union
{
    float fData;
    char* cpData;
} Item;
/*
 *
 */
typedef struct
{
    Item data;
    struct Node *prev;
} Node;
/*
 *
 */
typedef struct
{
    Node *node;
} Stack;
/*
 *
 */
void init(Stack *s)
{
    s->node = NULL;
}
/*
 *
 */
int isEmpty(Stack *s)
{
    if(s->node == NULL)
        return 1;
    else
        return 0;
}
/*
 *
 */
Item top(Stack *s)
{
    Item item = s->node->data;
    return item;
}
/*
 *
 */
Item pop(Stack *s)
{
    Item item;
    if(isEmpty(&s))
    {
        item.cpData='\0';
    }
    else
    {
        Node *node = s->node;
        item = node->data;
        s->node = node->prev;
        free(node);
    }
    return item;
}
/*
 *
 */
void push(Stack *s, Item val)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = val;
    newNode->prev = s->node;
    s->node = newNode;
}
/*
 *
 */
void destroy(Stack *s)
{
    while(!isEmpty(&s))
    {
        Node *node = s->node;
        s->node = node->prev;
        free(node);
    }
}
/*
 *
 */
int priority (char c )
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)*4 --> 23+4*
 */
void infixToPostfix(char* infix, char* postfix)
{
    Stack stack;
    init(&stack);
    char str[258];
    strcpy(postfix,"\0");
    strcpy(str,"( ");
    strcat(str,infix);
    strcat(str," )");
    char *token;
    token = strtok(str," ");
    while(token != NULL)
    {
        if(!strcmp(token,"("))
        {
            push(&stack,(Item)token);
        }
        else if(!strcmp(token,"^")||!strcmp(token,"*")||!strcmp(token,"/")||!strcmp(token,"+")||!strcmp(token,"-"))
        {
            if(!isEmpty(&stack))
            {
                while(!(priority(top(&stack).cpData)>=priority(token)))
                {
                    strcat(postfix,pop(&stack).cpData);
                    strcat(postfix," ");
                }
            }
            push(&stack,(Item)token);

        }
        else if(!strcmp(token,")"))
        {

            while(strcmp(top(&stack).cpData,"(")&&!isEmpty(&stack))
            {
                strcat(postfix,pop(&stack).cpData);
                strcat(postfix," ");
            }
            pop(&stack);
        }
        else
        {
            strcat(postfix,token);
            strcat(postfix," ");
        }
        token = strtok(NULL, " ");

    }
    while(!isEmpty(&stack))
    {
        strcat(postfix,pop(&stack).cpData);
        strcat(postfix," ");
    }
    strcat(postfix,"\0");
    if(!strcmp(postfix,"\0"))
        printf("------------- NO INPUT -------------\n");

}
/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
    if(!strcmp(postfix,"\0"))
    {
        return 0;
    }
    Stack *stack;
    init(&stack);
    Item item,first,second,result;
    result.fData = 0;
    char *token;
    token = strtok(postfix, " ");
    while(token != NULL)
    {
        if(!strcmp(token,"^")||!strcmp(token,"*")||!strcmp(token,"/")||!strcmp(token,"+")||!strcmp(token,"-"))
        {
            first = pop(&stack);
            second = pop(&stack);
            if(!strcmp(token,"^"))
            {
                result.fData = pow(second.fData,first.fData);
            }
            else if(!strcmp(token,"*"))
            {
                result.fData = second.fData*first.fData;
            }
            else if(!strcmp(token,"/"))
            {
                result.fData = second.fData/first.fData;
            }
            else if(!strcmp(token,"+"))
            {
                result.fData = second.fData+first.fData;
            }
            else if(!strcmp(token,"-"))
            {
                result.fData = second.fData-first.fData;
            }

            push(&stack,result);
        }
        else
        {
            item.fData = strtof(token,NULL);
            push(&stack,item);
        }
        token = strtok(NULL, " ");
    }
    result = pop(&stack);
    return result.fData;
}
/*
 *
 */
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
