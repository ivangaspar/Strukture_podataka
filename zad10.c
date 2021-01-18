#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STRING 11

struct _tree;
typedef struct _tree* positionTree;
typedef struct _tree{
    positionTree left;
    positionTree right;
    char data[MAX_STRING];
}tree;

struct _list;
typedef struct _list* positionList;
typedef struct _list{
    positionList next;
    positionTree treePointer;
}list;

int pushToStack(positionTree, positionList);
positionTree popFromStack(positionList);
positionTree createNewTree(char *);
int isNumber(char*);
positionTree readFromFile(char*, positionList);
int printToFile(positionTree, FILE*);


int pushToStack(positionTree treePointer, positionList head)
{
    positionList newStackElement = NULL;
    newStackElement = (positionList)malloc(sizeof(list));

    if(!newStackElement){
        printf("Memory allocation failed!\n");
        return -1;
    }

    newStackElement->treePointer = treePointer;
    newStackElement->next = head->next;
    head->next = newStackElement;

    return 0;
}

positionTree popFromStack(positionList head)
{
    positionTree elementToPop = NULL;
    positionList firstStackEl = head->next;

    if(!firstStackEl){
        printf("Stack is empty!\n");
        return NULL;
    }

    head->next = firstStackEl->next;
    elementToPop = firstStackEl->treePointer;
    free(firstStackEl);

    return elementToPop;
}

positionTree createNewTree(char *data)
{
    positionTree newElement = NULL;
    newElement = (positionTree)malloc(sizeof(tree));

    if(!newElement)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newElement->left = NULL;
    newElement->right = NULL;
    strcpy(newElement->data, data);

    return newElement;
}

int isNumber(char *str)
{
    int number = 0;

    if(sscanf(str, " %d", &number) == 1)
    return 1;
    else
    return 0;

}

positionTree readFromFile(char *filename, positionList stackHead)
{
    positionTree result = NULL;
    positionTree newElement = NULL;
    char str[MAX_STRING] = {'\0'};
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if(!fp)
    {
        printf("Required file does not exist or you don't have access to open it!\n");
        return NULL;
    }
    while (!feof(fp))
    {
        char str[MAX_STRING] = {'\0'};
        fscanf(fp, " %s", str);
        newElement = createNewTree(str);
        if(isNumber(str))
        {
            pushToStack(newElement, stackHead);
        }
        else
        {
            newElement->right = popFromStack(stackHead);
            newElement->left = popFromStack(stackHead);
            pushToStack(newElement, stackHead);
        }
    }
    result = popFromStack(stackHead);
    if(!result)
    {
        printf("Postfix expression not correct!\n");
        return NULL;
    }
    if(popFromStack(stackHead))
    {
        printf("Postfix expression not correct!\n");
        return NULL;
    }
    return result;
}

int printToFile(positionTree root, FILE* fp)
{
	if (NULL == root) return;
    fprintf(fp, "(");
    printToFile(root->left, fp);
    fprintf(fp, "%s", root->data);
    printToFile(root->right, fp);
    fprintf(fp, ")");
    return 0;
}

int main(void){
    positionTree root = NULL;
    positionList stackHead = NULL;
    stackHead = (positionList)malloc(sizeof(list));
    if(!stackHead)
    {
        printf("Stack allocation failed");
    }
    stackHead->treePointer = NULL;
    stackHead->next = NULL;

    root = readFromFile("postfixIzraz.txt", stackHead);

	FILE* fp = NULL;
	fp = fopen("infixIzraz.txt", "w");
	if (!fp)
	{
		printf("Required file doesn't exist or you don't have access!\n");
		return -1;
	}

    printToFile(root, fp);
    printf("Program finished, ready to exit!\n");

system("pause");
return 0;
}







