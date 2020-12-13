//Program racuna postfix izraz pomocu stoga
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _list;
typedef struct _list* node;
typedef struct _list
{
char el;
node next;
}list;

int calculatePostfix(char*, node, int *);
int push(node, int);
int pop(node);

int push(node stack, int x)
{
    node newEl = NULL;
    newEl = (node)malloc(sizeof(struct _list));
    if (NULL == newEl)
    {
        printf("Memory allocation failed!\n");
        return -1;
    }
    else
    {
        newEl->el = x;
        newEl->next = stack->next;
        stack->next = newEl;
        return 0;
    }
}

int pop(node stack)
{
    node deletedValue = NULL;
    deletedValue = (node)malloc(sizeof(struct _list));
    if(NULL == stack->next)
    {
        printf("\nPop function failed, the stack is empty!\n");
    }
    else
    {
        int helpEl = 0;
        deletedValue = stack->next;
        helpEl = deletedValue->el;
        stack->next = deletedValue->next;
        free(deletedValue);
        return helpEl;
    }
}

int calculatePostfix(char *filename, node stack, int *result)
{
    char *buff = NULL;
    buff = (char*)malloc(1024 * sizeof(char));
    int  check = 0, count = 0, number = 0, num1 = 0, num2 = 0, num3 = 0;
    FILE* fp = NULL;
    fp = fopen(filename, "r");
    if (NULL == fp)
    {
        printf("ERROR: File not successfuly opened!\n");
        return -1;
    }
    else
    {
        memset(buff, '\0', sizeof(buff));
        fgets(buff, sizeof(buff), fp);
        fclose(fp);
        while(*buff != '\0')
        {
        check = sscanf(buff, "%d%n", &number, &count);
        if(check)
        {
            push(stack, number);
            buff += count;
        }
        else
        {
            char helpEl;
            sscanf(buff, "%c%n", &helpEl, &count);
            buff += count;
            switch(helpEl)
            {
                case '+':
                {
                    num1 = pop(stack);
                    num2 = pop(stack);
                    num3 = num1 + num2;
                    push(stack, num3);
                    break;
                }
                case '-':
                {
                    num1 = pop(stack);
                    num2 = pop(stack);
                    num3 = num1 - num2;
                    push(stack, num3);
                    break;
                }
                case '*':
                {
                    num1 = pop(stack);
                    num2 = pop(stack);
                    num3 = num1 * num2;
                    push(stack, num3);
                    break;
                }
                default:
                {
                    printf("\n You have reached the end of your postfix!\n");
                    break;
                }
            }
        }
    }
}
*result = pop(stack);
return 0;
}

int main()
{
    int *result = NULL;
    node stack = NULL;
    stack = (node)malloc(sizeof(struct _list));
    calculatePostfix("postfixIzraz.txt", stack, result);
    printf("The given postfix equals to: %d\n", *result);
    system("pause");
    return 0;
}
