#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct _student;
typedef struct _student* Position;

typedef struct _student {
	char Ime[MAX];
	char Prez[MAX];
	int GodRod;
	Position next;
}student;

Position NoviUnos(char*, char*, int);
int PostavljanjePokazivaca(Position, Position);
int UnosPocetak(Position);
int UnosKraj(Position);
int UnosIspred(char *, Position);
int UnosIza(char*, Position);
Position PretragaPreth(char*, Position);
Position Pretraga(char*, Position);
int Izbrisi(char*, Position);
int Ispis(Position);
int SortiraniUnos(Position, char *, char *, int);
int UnosUDatoteku(Position);
int BrojacElemenataListe(Position);

Position NoviUnos(char* Ime, char* Prez, int God)
{
	Position P = NULL;
	P = (Position)malloc(sizeof(student));

	if (NULL == P)
	{
		printf("Neuspjesna alokacija memorije!");
		return NULL;
	}

	P->GodRod = God;
	strcpy(P->Ime, Ime);
	strcpy(P->Prez, Prez);
	P->next = NULL;

	return P;
}

int PostavljanjePokazivaca(Position P, Position Q)            // funkcija uvezuje dva elementa liste
{
	Q->next = P->next;
	P->next = Q;

	return 0;
}

int UnosPocetak(Position P)               
{
	char ime[MAX], prezime[MAX];
	int godina;

	printf("Unesi ime: \n\t");
	scanf("%s", ime);
	printf("Unesi prezime: \n\t");
	scanf("%s", prezime);
	printf("Unesi godinu rodenja studenta: \n\t");
	scanf("%d", &godina);

	SortiraniUnos(P, ime, prezime, godina);

	return 0;
}

int UnosKraj(Position P)
{
	while (P->next != NULL)
	{
		P = P->next;
	}

	if (NULL == P->next)
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

Position Pretraga(char *str, Position P)
{
	while ((NULL != P) && (strcmp(P->Prez, str)))
		P = P->next;

	if (NULL == P)
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

	while (P != NULL && strcmp(P->Prez, str) != 0)
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

	if (NULL == prethodni)
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
	if (NULL == P)
	{
		printf("Lista je prazna!\n");
		return -1;
	}

	else
	{
		while (P != NULL)
		{
			printf("Student: %s %s , roden %d \n", P->Ime, P->Prez, P->GodRod);
			P = P->next;
		}

		return 0;
	}
}

int SortiraniUnos(Position P, char *Ime, char *Prez, int God)   //Sortiranje pri unosu po imenu i prezimenu
{
	Position Q = NoviUnos(Ime, Prez, God);

	while (P->next != NULL && strcmp(P->next->Prez, Prez) <  0)
		P = P->next;

	if (P->next != NULL)
	{
		if (strcmp(P->next->Prez, Prez) > 0)
			PostavljanjePokazivaca(P, Q);
		else
		{
			while (P->next != NULL && strcmp(P->next->Ime, Ime) < 0)
				P = P->next;
			if (P->next != NULL)
			{
				PostavljanjePokazivaca(P, Q);
				return 0;
			}
			else
			{
				return -1;
			}
		}
	}
	else
	{
		PostavljanjePokazivaca(P, Q);
	}
}

int UnosUDatoteku(Position P, char *ImeDat)              // funkcija unosi listu u datoteku
{
	FILE *fp = NULL;
	fp = fopen(ImeDat, "w");

	if (NULL == fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}
	while (P != NULL)
	{
		fprintf(fp, "Student: %-20s %-20s roden %-4d godine\n", P->Ime, P->Prez, P->GodRod);
		P = P->next;
	}

	fclose(fp);

	return 0;
}

int CitanjeIzDat(char *ImeDat)                       // funkcija cita lsitu iz datoteke
{
	FILE *fp = NULL;
	fp = fopen(ImeDat, "r");

	char buff[1024] = { 0 };
	if (NULL == fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}
	while (fgets(buff, 1024, fp) != NULL)
		puts(buff);

	fclose(fp);

	return 0;
}

int BrojacElemenataListe(Position P)          //funkcija broji koliko elemenata sadrzi lista
{
	int br = 0;

	while (P != NULL)
	{
		P = P->next;
		br++;
	}

	return br;
}

int main()
{
	Position head = NULL;
	head = (Position)malloc(sizeof(student));
	head->next = NULL;

	int n;

	printf("Unesite broj clanova koje zelite unijeti: \n");
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		UnosPocetak(head);
	}

	/*Ispis(head->next);
	printf("\n\n\n");
	Izbrisi("TestPrezime", head);              //test brisanje
	Ispis(head->next);
	printf("\n\n\n");
	UnosIspred("TestPrezime", head);       //test novih funkcija
	UnosIza("TestPrezime", head);
	Ispis(head->next);*/

	Ispis(head->next);
	printf("\n\n\n");
	UnosUDatoteku(head->next, "datoteka.txt");
	CitanjeIzDat("datoteka.txt");

	printf("Lista ima %d elemenata.\n", BrojacElemenataListe(head->next));

	system("pause");

	return 0;
}