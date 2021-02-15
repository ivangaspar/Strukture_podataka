#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100
#define tableSize 11

struct person;

typedef struct person* personPtr;

typedef struct person
{
	char name[MAX_STRING];
	char surname[MAX_STRING];
	int matBroj;
	personPtr next;
};

int key(char*);
int initializeTable(personPtr*);
personPtr createNew(void);
int addPerson(personPtr*);
personPtr find(personPtr*);
int printTable(personPtr*);
int deleteTable(personPtr*);

int key(char* surname)
{
	int sum = 0;
	for (int i = 0; i < 5; i++)
		sum += surname[i];

	return sum % tableSize;
}

int initializeTable(personPtr* table)
{
	for (int i = 0; i < tableSize; i++)
	{
		table[i] = (personPtr)malloc(sizeof(struct person));
	}

	for (int i = 0; i < tableSize; i++)
	{
		if (table[i] == NULL)
		{
			printf("Memory allocation failed!\n");
			return -1;
		}
		else
		{
			table[i]->next = NULL;
			return 0;
		}
	}
}

personPtr createNew(void)
{
	personPtr tmp = NULL;
	tmp = (personPtr)malloc(sizeof(struct person));

	if (NULL == tmp)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}

	printf("\n Insert name: ");
	scanf("%s", tmp->name);
	printf("\n Insert surname: ");
	scanf("%s", tmp->surname);
	printf("\n Insert number: ");
	scanf("%d", &tmp->matBroj);
	tmp->next = NULL;

	return tmp;
}

int addPerson(personPtr* table)
{
	personPtr newPerson = NULL;
	newPerson = createNew();
	
	if (table[key(newPerson->surname)]->next == NULL)
	{
		newPerson->next = table[key(newPerson->surname)]->next;
		table[key(newPerson->surname)]->next = newPerson;
	}
	else
	{
		personPtr tmp = table[key(newPerson->surname)];
		if (tmp->next != NULL)
		{
			while (tmp->next != NULL && strcmp(tmp->next->surname, newPerson->surname) < 0)
			{
				tmp = tmp->next;
			}
		}
		newPerson->next = tmp->next;
		tmp->next = newPerson;
	}
	return 0;
}

personPtr find(personPtr* table)
{
	char tmpName[MAX_STRING] = { '\0' };
	char tmpSurname[MAX_STRING] = { '\0' };

	printf("\nInsert name: ");
	scanf("%s", tmpName);
	printf("\nInsert surname: ");
	scanf("%s", tmpSurname);

	personPtr tmp = table[key(tmpSurname)];

	while (tmp != NULL)
	{
		if (strcmp(tmp->name, tmpName) == 0 && strcmp(tmp->surname, tmpSurname) == 0)
		{
			printf("\n Person %s  %s found!\n", tmpName, tmpSurname);
			return tmp;
		}
		else
			tmp = tmp->next;
	}

	printf("\n Person %s  %s not found!\n", tmpName, tmpSurname);
	return NULL;
}

int printTable(personPtr* table)
{
	for (int i = 0; i < tableSize; i++)
	{
		printf("\n\n %d ---->", i);
		if (table[i]->next == NULL)
			printf("  ");

		else
		{
			personPtr tmp = table[i]->next;
			while (tmp != NULL)
			{
				printf("%s %s %d \t", tmp->name, tmp->surname, tmp->matBroj);
				tmp = tmp->next;
			}
		}
	}
}

int deleteTable(personPtr* table)
{
	for (int i = 0; i < tableSize; i++)
	{
		if (table[i]->next != NULL)
		{
			while (table[i]->next != NULL)
			{
				personPtr tmp = NULL;
				tmp = table[i]->next;
				table[i]->next = tmp->next;

				free(tmp);
			}
		}
	}
	return 0;
}
int main()
{
	personPtr hashTable[tableSize];
	initializeTable(hashTable);

	int n = 0;
	printf("\nInsert number of persons: ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		addPerson(hashTable);
	}

	printf("\n----> FINAL TABLE <----\n");
	printTable(hashTable);

	find(hashTable);
	deleteTable(hashTable);

	system("pause");
	return 0;
}