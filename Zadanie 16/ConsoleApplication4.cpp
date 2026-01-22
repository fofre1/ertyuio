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
	int tablica;
	struct elDrzewaB* lewy;
	struct elDrzewaB* prawy;
	struct elDrzewaB* rodzic;
};
typedef struct elDrzewaB wDrzewaB;
typedef wDrzewaB* drzewo;

void DDD(drzewo* d, int klucz, drzewo rodzic) {
	if (*d == NULL) {
		*d = (drzewo)malloc(sizeof(elDrzewaB));
		(*d)->lewy = (*d)->prawy = NULL;
		(*d)->rodzic = rodzic;
		(*d)->tablica = klucz;
		return;
	}
	if ((*d)->tablica<=klucz) {
		DDD(&(*d)->prawy, klucz, *d);
	}
	else if ((*d)->tablica > klucz) {
		DDD(&(*d)->lewy, klucz, *d);
	}
}

drzewo ZMinD(drzewo d) {
	if (d == 0) return 0;
	while (d->lewy) {
		d = d->lewy;
	}
	return d;
}

drzewo ZNastepnikaD(drzewo d) {
	if (d == 0) return 0;
	if (d->prawy) {
		d = d->prawy;
		while (d->lewy) d = d->lewy;
		return d;
	}
	drzewo p, q = d;
	p = d->rodzic;
	while (p && p->prawy == q) {
		q = p;
		p = p->rodzic;
	}
	if (p == 0) return 0;
	return p;
}

bool SprawdzCzySaTeSameWartosci(drzewo a, drzewo b) {
	drzewo a1, b1;
	a1 = ZMinD(a);
	b1 = ZMinD(b);
	if (a1 == 0 && b1 == 0)
		return true;
	while (a1 && b1) {
		if (a1->tablica != b1->tablica)
			return false;
		a1 = ZNastepnikaD(a1);
		b1 = ZNastepnikaD(b1);
	}
	if (a1 != 0 || b1 != 0)
		return false;
	return true;
}

void printd(drzewo d, int glebokosc) {
	if (d == 0) return;
	printd(d->prawy, glebokosc+1);
	for (int i = 0; i < glebokosc; i++) {
		printf("  ");
	}
	printf("%i\n", d->tablica);
	printd(d->lewy, glebokosc+1);
}



int main() {
	drzewo root = 0, root2 = 0;
	DDD(&root, 4, 0);
	DDD(&root, 3, 0);
	DDD(&root, 1, 0);
	DDD(&root, 7, 0);
	DDD(&root, 4, 0);
	DDD(&root, 10, 0);

	DDD(&root2, 10, 0);
	DDD(&root2, 4, 0);
	DDD(&root2, 1, 0);
	DDD(&root2, 3, 0);
	DDD(&root2, 4, 0);
	DDD(&root2, 7, 0);
	printf("\n");
	printd(root, 0);
	printf("\n");
	printd(root2, 0);
	printf("\n");
	if (SprawdzCzySaTeSameWartosci(root, root2))
		printf("Drzewa posiadaja takie same wartosci");
	else 
		printf("Drzewa nie posiadaja takich samych wartosci");
}