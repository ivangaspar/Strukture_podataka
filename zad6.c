#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define upper 100
#define lower 10

struct _node;
typedef struct _node *pok;
typedef struct _node
{
	int el;
	pok next;
}Node;

int generateRandoms();
pok createElement(int);
int pushToStack(pok);
pok pushToQueue(pok, pok);
int pop(pok);
int print(pok);
int deleteEntireList(pok);

int generateRandoms()
{
	return (rand() % (upper - lower + 1)) + lower;
}

pok createElement(int x)
{
	pok newElement = NULL;
	newElement = (pok)malloc(sizeof(struct _node));
	if (NULL == newElement)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}
	else
	{
		newElement->el = x;
		newElement->next = NULL;
	}
	return newElement;
}

int pushToStack(pok stack)
{
	pok newEl = createElement(generateRandoms());
	newEl->next = stack->next;
	stack->next = newEl;
	return 0;
}

pok pushToQueue(pok queue, pok lastInQueue)
{
	pok newEl = createElement(generateRandoms());
	if (queue == lastInQueue)
	{
		queue->next = newEl;
		lastInQueue = newEl;
	}
	else
	{
		lastInQueue->next = newEl;
		lastInQueue = newEl;
	}
	return lastInQueue;
}

int pop(pok head)
{
	if (head->next != NULL)
	{
		pok numberToDelete = head->next;
		head->next = head->next->next;
		free(numberToDelete);
	}
	return 0;
}

int print(pok head)
{
	while (head != NULL)
	{
		printf("%d \t", head->el);
		head = head->next;
	}
	return 0;
}

int deleteEntireList(pok head)
{
	while (head != NULL)
	{
		if (head->next = NULL)
		{
			break;
		}
		pok tmp = head;
		head = head->next;
		free(tmp);
	}
	return 0;
}

int main()
{
	int number = 0;
	pok stack = NULL;
	stack = (pok)malloc(sizeof(struct _node));
	pok queue = NULL;
	queue = (pok)malloc(sizeof(struct _node));
	pok lastInQueue = queue;
	srand(time(NULL));
	printf("InsertNumber ---> 1->Push to stack\t 2->Pop from stack\t 3->Push to queue\t 4->Pop from queue\t 5->Continue program \n");
	while (number != 5)
	{
		scanf("%d", &number);
		if (number == 1)
		{
			pushToStack(stack);
		}
		else if (number == 2)
		{
			pop(stack);
		}
		else if (number == 3)
		{
			lastInQueue = pushToQueue(queue, lastInQueue);
		}
		else if (number == 4)
		{
			pop(queue);
		}
		else if (number == 5)
		{
			printf("All operations finished, ready to print the lists!\n");
			break;
		}
		else
		{
			printf("ERROR: The number you entered has no function!\n");
			break;
		}
	}

	printf("\nCurrent queue: \n");
	print(queue->next);
	printf("\nCurrent stack: \n");
	print(stack->next);

	deleteEntireList(stack);
	deleteEntireList(queue);
	system("pause");
	return 0;
}