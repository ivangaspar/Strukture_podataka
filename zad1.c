#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2048 //Velicina buffera

#define MAXBOD 30 //Maksimalan broj bodova na ispitu -> ovisno o datoteci 

typedef struct {
	char ime[20];
	char prezime[50];
	int bod;
	float prosjek;
}student;

int BrojRed(const char *ImeDat)                //funkcija za brojenje redova
{
	int br = 0;
	char buffer[SIZE + 1];

	FILE *fp = NULL;
	fp = fopen(ImeDat , "r");				 //otvaranje datoteke

	if(fp == NULL)
	{
		printf("Neuspjelo otvaranje datoteke!\n");
		return -1;
	}

	else
	{
		while(fgets(buffer, sizeof(buffer), fp) != NULL)
		{br++;}

		fclose(fp);                   //zatvaranje datoteke
		return br;
	}
}

int UnosPod(char *ImeDat, int br, student *st)		//funkcija za unos podataka
{
	char buffer[SIZE + 1];

	FILE *dat = NULL;
	dat = fopen(ImeDat, "r");

	if(dat == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	while(feof(dat) == 0)
	{
		fgets(buffer, sizeof(buffer), dat);      //preskok prvog reda u datoteci

		for(int i = 0; i < br; i++)
			{
				fscanf(dat, "%s %s %d", (st + i)->ime,(st + i)->prezime, &(st + i)->bod);
				(st + i)->prosjek =100*(double)(st + i)->bod/MAXBOD;
			}
	}

	fclose(dat);	

	return 0;
}

int IspisPod(int br, student *st)                   //funkcija za ispis podataka
{
	for(int j = 0; j < br; j++)
	{
		printf("Student %s  %s :\n Broj bodova: %d , postotak: %f% \n\n", (st + j)->ime, (st + j)->prezime, (st + j)->bod,(st + j)->prosjek);
	}

	return 0;
}

int main()
{
	int BrRed;
	BrRed = BrojRed("studenti.txt");

	student *st = NULL;
	st = (student *)malloc((BrRed - 1) * sizeof(student));

	if(st == NULL)
	{
		printf("Neuspjesna alokacija memorije!\n");
	}

	printf("Broj studenata u datoteci je: %d, maksimalan broj bodova je: %d \n\n", BrRed - 1, MAXBOD);

	UnosPod("studenti.txt", BrRed - 1, st);         
	IspisPod(BrRed - 1, st);                        
	free(st);

	return 0;
}

