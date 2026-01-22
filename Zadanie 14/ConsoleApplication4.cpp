/*Zaimplementuj operacje na drzewie binarnym łańcuchów znakowych z porządkiem: 
dodawanie, DONE
usuwanie, DONE
szukanie, DONE
wyznaczanie minimum i maksimum, DONE
wyznaczanie poprzednika i następnika wskazanego elementu 
(można korzystać ze wskaźnika na węzeł rodzica). 

Uzupełnij program o procedurę kontrolnego drukowania zawartości DONE
utworzonego drzewa z ukazaniem jego struktury.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

struct elDrzewaB {
	char* tablica;
	struct elDrzewaB* lewy;
	struct elDrzewaB* prawy;
	struct elDrzewaB* rodzic;
};
typedef struct elDrzewaB wDrzewaB;
typedef wDrzewaB* drzewo;

void DDD(drzewo* d, const char* klucz, drzewo rodzic) {
	if (*d == NULL) {
		*d = (drzewo)malloc(sizeof(elDrzewaB));
		(*d)->tablica = (char*)malloc(strlen(klucz) + 1);
		(*d)->lewy = (*d)->prawy = NULL;
		(*d)->rodzic = rodzic;
		strcpy((*d)->tablica, klucz);
		return;
	}
	int czyTablicaJestWiekszaNizKlucz=strcmp(klucz ,(*d)->tablica); //
	if (czyTablicaJestWiekszaNizKlucz >= 0) {
		DDD(&(*d)->prawy, klucz, *d);
	}
	else if (czyTablicaJestWiekszaNizKlucz < 0) {
		DDD(&(*d)->lewy, klucz, *d);
	}
}


drzewo* ZWD(drzewo* d, const char* klucz){
	drzewo *znalezione = 0;
	if (*d == NULL)
		return 0;
	int czyTablicaJestWiekszaNizKlucz = strcmp(klucz, (*d)->tablica);
	if (czyTablicaJestWiekszaNizKlucz == 0) {
		return d;
	}
	if (czyTablicaJestWiekszaNizKlucz > 0)
		znalezione = ZWD(&(*d)->prawy, klucz);
	else
		znalezione = ZWD(&(*d)->lewy, klucz);
	return znalezione;
}

void printd(drzewo d, int glebokosc) {
	if (d == 0) return;
	printd(d->lewy, glebokosc+1);
	for (int i = 0; i < glebokosc; i++) {
		printf("  ");
	}
	printf("%s\n", d->tablica);
	printd(d->prawy, glebokosc+1);
}

drzewo* ZMaxD(drzewo* d) {
	if (d == 0) return 0;
	while ((*d)->prawy) {
		d = &(*d)->prawy;
	}
	return d;
}

drzewo* ZMinD(drzewo* d) {
	if (d == 0) return 0;
	while ((*d)->lewy) {
		d = &(*d)->lewy;
	}
	return d;
}

drzewo* ZNastepnikaD(drzewo *d) {
	if (d == 0) return 0;
	if ((*d)->prawy) {
		d = &(*d)->prawy;
		while ((*d)->lewy) d = &(*d)->lewy;
		return d;
	}
	drzewo p, q = *d;
	p = (*d)->rodzic;
	while (p && p->prawy == q) {
		q = p;
		p = p->rodzic;
	}
	if (p == 0) return 0;
	return &p;
}

drzewo* ZPoprzednika(drzewo* d) {
	if (d == 0) return 0;
	if ((*d)->lewy) {
		d = &(*d)->lewy;
		while ((*d)->prawy) d = &(*d)->prawy;
		return d;
	}
	drzewo p, q=*d;
	p = (*d)->rodzic;
	if (p == 0) return 0;
	while ( p && p->lewy == q) {
		q = p;
		p = p->rodzic;
	}
	if (p == 0) return 0;
	return &p;
}

void UZD(drzewo* d, const char* klucz) {
	drzewo* q = ZWD(d, klucz);
	drzewo p = *q, dziecko;
	if (*q == 0)
		return;
	if ((*q)->lewy == 0 && (*q)->prawy == 0) {
		*q = NULL;
		free(p->tablica);
		free(p);
	}
	else if ((*q)->lewy == 0 || (*q)->prawy == 0) {
		if ((*q)->lewy == 0) {
			dziecko = p->prawy;
			dziecko->rodzic = p->rodzic;
			(*q) = dziecko;
			free(p->tablica);
			free(p);
		}
		else {
			dziecko = p->lewy;
			dziecko->rodzic = p->rodzic;
			(*q) = dziecko;
			free(p->tablica);
			free(p);
		}
	}
	else {
		drzewo* nast = ZMinD(&(p->prawy));
		char* temp = p->tablica;
		p->tablica = (*nast)->tablica;
		(*nast)->tablica = temp;
		UZD(&p->prawy, (*nast)->tablica);

	}
}


int main() {
	drzewo root = NULL;

	DDD(&root, "sliwka", NULL);
	DDD(&root, "jablko", NULL);
	DDD(&root, "gruszka", NULL);
	DDD(&root, "banan", NULL);
	DDD(&root, "winogrono", NULL);
	DDD(&root, "brzoskwinia", NULL);
	DDD(&root, "cytryna", NULL);
	DDD(&root, "wisnia", NULL);
	DDD(&root, "figa", NULL);
	DDD(&root, "kiwi", NULL);
	DDD(&root, "daktyl", NULL);
	printf("Drzewo in-order:\n");
	printd(root, 0);
	printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
	_getch();
	UZD(&root, "jablko");
	printd(root, 0);
	printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
	_getch();
	UZD(&root, "daktyl");
	printd(root, 0);
	printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
	_getch();
	UZD(&root, "cytryna");
	printd(root, 0);
	printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
	_getch();
	drzewo *p= ZWD(&root, "gruszka");
	printd(*ZPoprzednika(&(*p)), 0);
	printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
	_getch();
	printd(*ZNastepnikaD(&(*p)), 0);
	printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
	_getch();


}