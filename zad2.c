#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct _student;
typedef struct _student* Position;

typedef struct _student{
	char Ime[MAX];
	char Prez[MAX];
	int GodRod;
	Position next;
}student;

Position NoviUnos(char* , char* , int);
int UnosPocetak(Position);
int UnosKraj(Position);
int UnosIspred(char *, Position);
int UnosIza(char*, Position);
Position PretragaPreth(char*, Position);
Position Pretraga(char*, Position);
int Izbrisi(char*, Position);
int Ispis(Position);




Position NoviUnos(char* Ime, char* Prez, int God)
{
	Position p = NULL;
	p = (Position)malloc(sizeof(student));

	if (NULL == p)
	{
		printf("Neuspjesna alokacija memorije!");
		return NULL;
	}

	p->GodRod = God;
	strcpy(p->Ime, Ime);
	strcpy(p->Prez, Prez);
	p->next = NULL;

	return p;
}

int UnosPocetak(Position P)
{
	Position Q = NULL;
	char ime[MAX], prezime[MAX];
	int godina;

	printf("Unesi ime: \n\t");
	scanf("%s", ime);
	printf("Unesi prezime: \n\t");
	scanf("%s", prezime);
	printf("Unesi godinu rodenja studenta: \n\t");
	scanf("%d", &godina);

	Q = NoviUnos(ime, prezime, godina);

	Q->next = P->next;
	P->next = Q;

	return 0;
}

int UnosKraj(Position P)
{
	while(P->next != NULL)
		{P = P->next;}

	if(NULL == P->next)
	{
		UnosPocetak(P);
	}

	else
	{
		printf("Nije pronaden posljednji clan liste!\n");
		return -1;
	}

	return 0;
}

int UnosIspred(char *str, Position P)
{
	Position Q = NULL;
	Q = PretragaPreth(str, P);
	UnosPocetak(Q);
	if (NULL == Q)
	{
		printf("Neuspjesna pretraga elementa! \n");
		return -1;
	}
	return 0;
}

int UnosIza(char *str, Position P)
{
	Position Q = NULL;
	Q = Pretraga(str, P);
	UnosPocetak(Q);
	if (NULL == Q)
	{
		printf("Neuspjesna pretraga elementa! \n");
		return -1;
	}
	return 0;
}

Position Pretraga(char *str,  Position P)
{
	while((NULL != P) && (strcmp(P->Prez , str)))
		P = P->next;

	if(NULL == P)
	{
		printf("Ne postoji trazeni element!\n");
		return NULL;
	}
	return P;
}

Position PretragaPreth(char *str, Position P)
{
	Position prethodni = P;
	P = P->next;

	while (P !=NULL && strcmp(P->Prez, str) != 0)
	{
		prethodni = P;
		P = P->next;
	}

	if (NULL == P->next)
	{
		printf("Ne postoji trazeni element!\n\n");
		return NULL;
	}

	else
		return prethodni;
}

int Izbrisi(char *str, Position P)
{
	Position prethodni = NULL;
	prethodni = PretragaPreth(str, P);

	if(NULL == prethodni)
	{
		printf("Neuspjesna potraga prethodnog elementa!\n");
		return -1;
	}

	else
	{
		P = prethodni->next;
		prethodni->next = P->next;
		free(P);
	}
}

int Ispis(Position P)
{
	if(NULL == P)
	{
		printf("Lista je prazna!\n");
		return -1;
	}

	else
	{
	while(P != NULL)
	{
		printf("Student: %s %s , roden %d \n", P->Ime, P->Prez, P->GodRod);
		P = P->next;
	}

	return 0;
	}
}

int main()
{
	Position head = NULL;
	head = (Position)malloc(sizeof(student));
	head->next = NULL;

	char ime[MAX], prezime[MAX];
	int godina;

	UnosPocetak(head);
	UnosPocetak(head);
	UnosKraj(head);
	UnosKraj(head);

	Ispis(head->next);
	printf("\n\n\n");
	Izbrisi("Matic", head);              //test brisanje
	Ispis(head->next);
	printf("\n\n\n");
	UnosIspred("Kovacevic", head);       //test novih funkcija
	UnosIza("Kovacevic", head);
	Ispis(head->next);

	system("pause");

	return 0;
}
