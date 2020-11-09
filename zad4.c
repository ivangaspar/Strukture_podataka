#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

struct _polinom;
typedef struct _polinom* Pok;
typedef struct _polinom
{
	int Koef;
	int Exp;
	Pok next;
}Polinom;

int CitajIzDat(char *, Pok);
int PostavljanjePokazivaca(Pok, Pok);
Pok Alokacija(void);
Pok NoviClan(int, int);
int SortiraniUnos(Pok, Pok);
int ZbrojiPolinome(Pok, Pok, Pok);
int PomnoziPolinome(Pok, Pok, Pok);
int Ispis(Pok);


int CitajIzDat(char *ImeDat, Pok P)
{
	FILE *fp = NULL;
	fp = fopen(ImeDat, "r");

	if (NULL == fp)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}
	else
	{
		while(!feof(fp))
		{
			Pok Q = NULL;
			Q = Alokacija();

			fscanf(fp, "%d %d", &Q->Koef, &Q->Exp);
			SortiraniUnos(P, Q);
		}
		fclose(fp);
		return 0;
	}
}

int PostavljanjePokazivaca(Pok P1, Pok P2)
{
	P2->next = P1->next;
	P1->next = P2;

	return 0;
}

Pok Alokacija(void)
{
	Pok Q = NULL;
	Q = (Pok)malloc(sizeof(Polinom));

	if (NULL == Q)
	{
		return NULL;
	}

	else
	{
		Q->next = NULL;
		return Q;
	}
}

Pok NoviClan(int k, int e)
{
	Pok P = NULL;
	P = Alokacija();

	P->Koef = k;
	P->Exp = e;
	P->next = NULL;

	return P;
}

int SortiraniUnos(Pok P1, Pok P2)
{
	while (P1->next != NULL && (P1->next->Exp < P2->Exp))
	{
		P1 = P1->next;
	}

	PostavljanjePokazivaca(P1, P2);

	return 0;
}

int ZbrojiPolinome(Pok P1, Pok P2, Pok head)
{
	Pok tmp = NULL, P3 = NULL;
	tmp = Alokacija();

	if (NULL == P1 && NULL == P2)
	{
		printf("Oba polinoma su jednaka nuli!\n");
		return -1;
	}

	else
	{
		while (P1 != NULL && P2 != NULL)
		{
			if (P1->Exp < P2->Exp)
			{
				P3 = NoviClan(P1->Koef, P1->Exp);
				SortiraniUnos(head, P3);

				P1 = P1->next;
			}
			else if (P1->Exp > P2->Exp)
			{
				P3 = NoviClan(P2->Koef, P2->Exp);
				SortiraniUnos(head, P3);

				P2 = P2->next;
			}
			else
			{
				if ((P1->Koef + P2->Koef) == 0)
				{
					printf("Zanemaren clan uz %d potenciju!\n", P1->Exp);

					P1 = P1->next;
					P2 = P2->next;
				}
				else
				{
					P3 = NoviClan(P1->Koef + P2->Koef, P1->Exp);
					SortiraniUnos(head, P3);

					P1 = P1->next;
					P2 = P2->next;
				}
			}
		}
		if (NULL == P1)
			tmp = P2;
		else
			tmp = P1;
		while (tmp != NULL)
		{
				SortiraniUnos(head, tmp);

				tmp = tmp->next;
		}
	}
	return 0;
}

int PomnoziPolinome(Pok P1, Pok P2, Pok head)
{
	Pok tmp1 = NULL;
	Pok tmp2 = NULL;
	Pok tmp3 = NULL;

	for (tmp1 = P1; tmp1 != NULL; tmp1 = tmp1->next)
	{
		for (tmp2 = P2; tmp2 != NULL; tmp2 = tmp2->next)
		{
			tmp3 = NoviClan(tmp1->Koef * tmp2->Koef, tmp1->Exp + tmp2->Exp);
			SortiraniUnos(head, tmp3);
		}
	}
	return 0;
}

int Ispis(Pok P)
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
			printf("(%dx^%d)\t +\t", P->Koef, P->Exp);
			P = P->next;
		}
		printf("\n");
		return 0;
	}
}

int main()
{
	Pok head1 = NULL, head2 = NULL, head3 = NULL, head4 = NULL;

	head1 = Alokacija();
	head2 = Alokacija();
	head3 = Alokacija();
	head4 = Alokacija();


	CitajIzDat("datoteka1.txt", head1);
	CitajIzDat("datoteka2.txt", head2);

	ZbrojiPolinome(head1->next, head2->next, head3);
	PomnoziPolinome(head1->next, head2->next, head4);

	printf("Pocetni polinomi: \n");
	Ispis(head1->next);
	Ispis(head2->next);
	printf("\n Suma polinoma: \n");
	Ispis(head3->next);
	printf("\n Pomnozeni polinomi: \n");
	Ispis(head4->next);

	system("pause");

	return 0;
}