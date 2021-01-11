#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 128

struct _directory;
typedef struct _directory* positionDirectory;
typedef struct _directory {
	char name[MAX_SIZE];
	positionDirectory sibling;
	positionDirectory child;
}directory;

struct _stack;
typedef struct _stack* positionStack;
typedef struct _stack {
	positionDirectory dir;
	positionStack next;
}stack;

enum exit_value {
	SUCCESS,
	ALLOCATION_FAIL,
	DUPLICATE_NAME
};

int pushStack(positionStack, positionDirectory);
positionDirectory popStack(positionStack);
positionDirectory findDirectory(positionDirectory, char*);
int deleteAllDirectories(positionDirectory);
int deleteAllStack(positionStack);
int makeDirectory(positionDirectory);
int printFromCurrent(positionDirectory);


int main()
{
	directory root;
	strcpy(root.name, "C:");
	root.sibling = NULL;
	root.child = NULL;
	positionDirectory current = &root;

	stack stog;
	stog.next = NULL;

	char function[MAX_SIZE] = { '\0' };
	printf("\n Directory creator\n Choose the function:\n mkdir ---> creates new directory\n cd ---> switches to a desired directory\n cd.. ---> takes you one step backwards\n dir ---> prints all directories inside of a current one\n exit ---> deletes all directories and closes the console\n");
	while (strcmp(function, "exit\n") != 0)
	{
		memset(function, MAX_SIZE, '\0');
		fgets(function, MAX_SIZE - 1, stdin);
		if (strcmp(function, "mkdir\n") == 0)
		{
			makeDirectory(current);
		}
		else if (strcmp(function, "cd\n") == 0)
		{
			char name[MAX_SIZE] = { '\0' };
			printf("\n Enter the name of the directory you would like to switch to: ");
			fgets(name, MAX_SIZE - 1, stdin);
			if (findDirectory(current->child, name))
			{
				pushStack(&stog, current);
				current = findDirectory(current->child, name);
				printf("\nYou are now in -->%s<-- directory\n", current->name);
			}
			else
				printf("\n The directory you wanted to access does not exist!\n");
		}
		else if (strcmp(function, "cd..\n") == 0)
		{
			current = popStack(&stog);
			printf("\nYou are now in -->%s<-- directory\n", current->name);
		}
		else if (strcmp(function, "dir\n") == 0)
		{
			printf("\n Content of current directory: \n");
			if (current->child)
				printFromCurrent(current->child);
			else
				printf("Empty directory!\n");
		}
		else if (strcmp(function, "exit\n") == 0)
		{
			printf("\n Program over, changes no longer possible\n");
			deleteAllDirectories(&root);
			deleteAllStack(&stog);
		}
		else
		{
			printf("\nIncorrect function name, try again!\n");
		}
	}
	return EXIT_SUCCESS;
}

int deleteAllDirectories(positionDirectory current) {
	if (NULL == current) return;
	deleteAllDirectories(current->sibling);
	deleteAllDirectories(current->child);
	free(current);
	return SUCCESS;
}

int deleteAllStack(positionStack head) {
	while (head->next != NULL) {
		positionStack tmp = head->next;
		head->next = head->next->next;
		free(tmp);
	}
}

int pushStack(positionStack head, positionDirectory dir) {
	positionStack newStackElement = NULL;
	newStackElement = (positionStack)malloc(sizeof(stack));
	if (NULL == newStackElement) return ALLOCATION_FAIL;
	newStackElement->dir = dir;
	newStackElement->next = head->next;
	head->next = newStackElement;
	return SUCCESS;
}

positionDirectory popStack(positionStack head) {
	if (head->next != NULL) {
		positionStack toDelete = head->next;
		positionDirectory helpElement = head->next->dir;
		head->next = head->next->next;
		free(toDelete);
		return helpElement;
	}
	else
		return NULL;
}

positionDirectory findDirectory(positionDirectory current, char* name) {
	if (NULL == current->child) {
		return NULL;
	}
	current = current->child;
	if (strcmp(current->name, name) == 0)
	{
		return current;
	}
	while (current->sibling != NULL && strcmp(current->name, name) != 0)
	{
		current = current->sibling;
	}
	if (NULL == current) 
		return NULL;
	else
		return current;
}

int makeDirectory(positionDirectory current) {
	char name[MAX_SIZE] = { '\0' };
	printf("\nInsert the name of a new directory: ");
	fgets(name, MAX_SIZE - 1, stdin);
	positionDirectory newDirectory = NULL;
	newDirectory = (positionDirectory)malloc(sizeof(directory));
	if (NULL == newDirectory) return ALLOCATION_FAIL;
	if (findDirectory(current, name) != NULL) return DUPLICATE_NAME;
	strcpy(newDirectory->name, name);
	newDirectory->sibling = NULL;
	newDirectory->child = NULL;
	if (current->child == NULL)
	{
		current->child = newDirectory;
		return SUCCESS;
	}
	if(strcmp(current->child->name, name) > 0)
	{
		newDirectory->sibling = current->child;
		current->child = newDirectory;
		return SUCCESS;
	}
	current = current->child;
	while (current->sibling != NULL && strcmp(current->sibling->name, name) < 0)
		current = current->sibling;
	newDirectory->sibling = current->sibling;
	current->sibling = newDirectory;
	return SUCCESS;
}

int printFromCurrent(positionDirectory current) {
	if (NULL == current) return;
	printFromCurrent(current->sibling);
	printFromCurrent(current->child);
	printf("\n%s", current->name);
	return 0;
}

