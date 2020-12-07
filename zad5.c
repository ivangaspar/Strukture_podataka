#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

struct _node;
typedef struct _node * Pok;
typedef struct _node {
	int el;
	Pok next;
}node;

int readFromFile(char*, Pok);
Pok newEntry(int);
int calculateUnion(Pok, Pok, Pok);
int calculateIntersection(Pok, Pok, Pok);
int print(Pok);
int deleteEntireList(Pok);

int readFromFile(char* filename, Pok group)
{
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (NULL == fp)
	{
		printf("ERROR: File opening error!\n");
		return -1;
	}
	else
	{
		int helpEl = 0;
		while (!feof(fp))
		{	
			fscanf(fp, " %d", &helpEl);
			Pok newElement = newEntry(helpEl);
			group->next = newElement;
			group = group->next;
		}
		fclose(fp);
		return 0;
	}
}

Pok newEntry(int newValue)
{
	Pok newEl = NULL;
	newEl =	(Pok)malloc(sizeof(struct _node));
	if (newEl == NULL)
	{
		printf("ERROR: Memory allocation did not succeed\n");
		return NULL;
	}
	newEl->el = newValue;
	newEl->next = NULL;
	return newEl;
}

int calculateUnion(Pok firstGroup, Pok secondGroup, Pok finalGroup)
{
	Pok tmp = NULL;
	while (firstGroup != NULL && secondGroup != NULL) 
	{
		if (firstGroup->el < secondGroup->el)
		{
			finalGroup->next = newEntry(firstGroup->el);
			firstGroup = firstGroup->next;
			finalGroup = finalGroup->next;
		}
		else if (firstGroup->el > secondGroup->el)
		{
			finalGroup->next = newEntry(secondGroup->el);
			secondGroup = secondGroup->next;
			finalGroup = finalGroup->next;
		}
		else
		{
			finalGroup->next = newEntry(firstGroup->el);
			firstGroup = firstGroup->next;
			secondGroup = secondGroup->next;
			finalGroup = finalGroup->next;
		}
	}
	if (firstGroup == NULL)
		tmp = secondGroup;
	else
		tmp = firstGroup;
	while (tmp != NULL)
	{
		finalGroup->next = newEntry(tmp->el);
		tmp = tmp->next;
		finalGroup = finalGroup->next;
	}
	return 0;
}

int calculateIntersection(Pok firstGroup, Pok secondGroup, Pok finalGroup)
{
	while (firstGroup != NULL && secondGroup != NULL) 
	{
		if (firstGroup->el < secondGroup->el)
			firstGroup = firstGroup->next;
		else if (firstGroup->el > secondGroup->el)
			secondGroup = secondGroup->next;
		else if(firstGroup->el == secondGroup->el)
		{
			finalGroup->next = newEntry(firstGroup->el);
			firstGroup = firstGroup->next;
			secondGroup = secondGroup->next;
			finalGroup = finalGroup->next;
		}
	}
	return 0;
}

int print(Pok head)
{
	while (head != NULL) 
	{
		printf("%d \t", head->el);
		head = head->next;
	}
	printf(" \n");
	return 0;
}

int deleteEntireList(Pok head)
{
	Pok tmp = NULL;
	while (head->next != NULL) 
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	return 0;
}

int main()
{
	 Pok head1 = NULL, head2 = NULL, head3 = NULL, head4 = NULL;
	 head1 = (Pok)malloc(sizeof(struct _node));
	 head2 = (Pok)malloc(sizeof(struct _node));
	 head3 = (Pok)malloc(sizeof(struct _node));
	 head4 = (Pok)malloc(sizeof(struct _node));

	 readFromFile("datoteka1.txt", head1);
	 readFromFile("datoteka2.txt", head2);
	 calculateUnion(head1->next, head2->next, head3);
	 calculateIntersection(head1->next, head2->next, head4);

	 printf("Starting groups: \n");
	 print(head1->next);
	 print(head2->next);
	 printf("\nUnion of these groups: \n");
	 print(head3->next);
	 printf("\nIntersection of these groups: \n");
	 print(head4->next);

	 deleteEntireList(head1);
	 deleteEntireList(head2);
	 deleteEntireList(head3);
	 deleteEntireList(head4);
	 system("pause");
return 0;
}