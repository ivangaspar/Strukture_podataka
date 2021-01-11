#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _node;
typedef struct _node* Position;

typedef struct _node{
	int number;
	Position right;
	Position left;
}node;

Position createNew(int);
Position insert(Position, int);
Position printInorder(Position);
Position find(Position, int);
Position delete(Position, int);
Position findMinimum(Position);

Position createNew(int number)
{
	Position newEl = NULL;
	newEl = (Position)malloc(sizeof(node));
	newEl->number = number;
	newEl->left = NULL;
	newEl->right = NULL;
	return newEl;
}

Position insert(Position current, int number)
{
	Position newEl = createNew(number);
	if (NULL == current) return newEl;

	if (current->number > newEl->number){
		current->left = insert(current->left, newEl);
	}

	else if (current->number < newEl->number)
	{
		current->right = insert(current->right, newEl);
	}

	else
	{
		printf("\n Element you tried to insert (%d) already exists!\n", newEl->number);
		free(newEl);
	}
	return current;
}

Position printInorder(Position current)
{
	if (NULL == current) return;
	printInorder(current->left);
	printf("%d\t", current->number);	
	printInorder(current->right);		
	return current;
}

Position find(Position current, int number)
{
	if (current == NULL) return NULL;
	if (current->number == number)
	{
		return current;
	}

	else if (current->number > number)
	{
		return find(current->left, number);
	}

	else
	{
		return find(current->right, number);
	}
}

Position delete(Position current, int number)
{
	Position tmp = NULL;

	if (current != NULL)
	{
		if (number < current->number)
			current->left = delete(number, current->left);
		else if (number > current->number)
			current->right = delete(number, current->right);
		else
		{
			if (current->right != NULL && current->left != NULL) //ima dvoje djece
			{
				tmp = findMinimum(current->right);
				current->number = tmp->number;
				current->right = delete(tmp->number, current->right);
			}
			else
			{
				tmp = current;

				if (current->left != NULL)
					current = current->right;
				else
					current = current->left;
				free(tmp);
			}
		}
	}
	return current;
}

Position findMinimum(Position current)
{
	if (NULL == current) return NULL;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

int main()
{
	Position root = NULL;
	Position x = NULL;
	int a, num;

	do
	{
		printf("\n\n1 - Add new element \n");
		printf("2 - Print everything\n");
		printf("3 - Search\n");
		printf("4 - Delete\n");
		printf("0 - Exit\n");

		printf("\n Insert number of the function: \n");
		scanf(" %d", &a);

		switch (a)
		{
		case 1:
			printf("\nInsert value of new element: \n");
			scanf(" %d", &num);
			root = insert(root, num);
			if (root == NULL) printf("\n An error occurred!\n");
			break;

		case 2:
			if (root == NULL) printf("The tree is empty.\n");
			else
				x = printInorder(root);
			break;

		case 3:
			printf("\nElement you are looking for: \n");
			scanf(" %d", &num);
			x = find(root, num);
			if (x == NULL) printf("Element does not exist in this binary tree!\n");
			else printf("Element (%d) found!\n", x->number);
			break;

		case 4:
			printf("\nInsert the element you want to delete: \n");
			scanf(" %d", &num);
			root = delete(root, num);
			if (root == NULL) printf("\nAn error occurred!.\n");
			break;

		case 0:
			printf("\n Exit. \n");
			break;

		default:
			printf("\nIncorrect function call!\n");
		}
	} while (a != 0);
	system("pause");
	return 0;
}