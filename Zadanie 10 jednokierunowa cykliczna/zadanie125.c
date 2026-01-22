#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "zadanie125.h"

lista* znajdzkoniec(lista* l) {
    if (*l == 0) return 0;
    lista* start = l;
    while ((*l)->nast != *start) {
        l = &(*l)->nast;
    }
    return l; 
}

//Dodanie na poczatek listy
void DNPL(lista* l, int x) {
    lista q = (lista)malloc(sizeof(ellisty));
    q->klucz = x;
    if (*l == 0) {
        q->nast = q;
        *l = q;
        return;
    }
    lista* w = znajdzkoniec(l);
    q->nast = *l;
    (*w)->nast = q;
    *l = q;
}

//Dodanie na koniec listy
void DNKL(lista* l, int x) {
    if (*l == 0) {
        DNPL(l, x);
        return;
    }
    lista* w = znajdzkoniec(l);
    lista q = (lista)malloc(sizeof(ellisty));
    q->klucz = x;
    q->nast = (*w)->nast;
    (*w)->nast = q;
}

//Usuwanie pierwszego elementu
void UPEL(lista* l) {
    if (*l == 0) return;
    lista element = *l;
    if (element->nast == element) {
        free(element);
        *l = 0;
        return;
    }
    lista ostatni = znajdzkoniec(l);
    *l = element->nast; // przesuwamy wskaŸnik na nowy pocz¹tek
    ostatni->nast = *l;  // zachowujemy cyklicznoœæ
    free(element);
}

//Usuwanie ostatniego elementu
void UOEL(lista* l) {
    if (*l == 0) return;
    if ((*l)->nast == (*l)) {
        free(*l);
        *l = 0;
        return;
    }
    lista* w = znajdzkoniec(l);
    lista* przedostatni = l;
    while ((*przedostatni)->nast != *w) {
        przedostatni = &(*przedostatni)->nast;
    }

    free(*w);
    (*przedostatni)->nast = *l;
}

//Znajdywanie elementu
lista* ZnajdzDanyElement(lista* l, int x) {
    if (*l == 0) return;
    lista a = *l;
    lista* q = l;
    do {
        if ((*q)->klucz == x) return q;
        q = &(*q)->nast;
    } while (*q != a);
    return 0;
}


//Dodawanie zaa znaleziony element
void DZDEL(lista* l, int nowa, int szukana) {
    lista* q = ZnajdzDanyElement(l, szukana);
    if (q == 0) return;
    q = &(*q)->nast;
    DNPL(q, nowa);
}

//Dodawanie przed znalezionym elementem
void DPDEL(lista* l, int nowa, int szukana) {
    lista* q = ZnajdzDanyElement(l, szukana);
    if (q == 0) return;
    DNPL(q, nowa);
}

//Usuwanie znalezionego elementu
void UZEL(lista* l, int szukana) {
    lista* q = ZnajdzDanyElement(l, szukana);
    if (q == 0) return;
    UPEL(q);
}

//Wyswietlanie listy od poczatku
void printl(lista l) {
    if (!l) return;
    lista a = l;
    do {
        printf("%d ", l->klucz);
        l = l->nast;
    } while (l != a);
    printf("\n");
}

//Wyswietlanie listy od konca rekurencyjnie
void printlk(lista l) {
    if (!l) return;
    int x = l->klucz;
    lista* w = znajdzkoniec(&l);
    do {
        printf("%d ", (*w)->klucz);
        w = znajdzkoniec(w);
    } while (*w != l);
    printf("%d ", x);
    printf("\n");
}

//Zapisz do pliku
void ZDP(lista l, FILE* plik) {
    if (!l) {
        fprintf(plik, "\n");
        return;
    }
    lista start = l;
    do {
        fprintf(plik, "%i", l->klucz);
        l = l->nast;
        if (l != start) fprintf(plik, " ");
    } while (l != start);
    fprintf(plik, "\n");
}

//Wczytaj z pliku
void WZP(lista* l, FILE* plik) {
    char p;
    fscanf(plik, "%c", &p);
    while (p != '\n') {
        int pomocnicza = 0;
        while (p != ' ' && p != '\n') {
            pomocnicza = 10 * pomocnicza + ((int)p - 48);
            fscanf(plik, "%c", &p);
        }
        DNKL(l, pomocnicza);
        if (p != '\n') fscanf(plik, "%c", &p);
    }
}
//Zwolnienie listy
void ZwolnijListe(lista* l) {
    lista w = *l;
    while (*l) {
        *l = (*l)->nast;
        free(w);
        w = *l;
    }
}

void UsunZListy(lista* zKtorejUsuwamy, lista zKtorejBierzemy)
{
    if (zKtorejBierzemy == 0)
        return;

    lista p = zKtorejBierzemy;
    do {
        int klucz = p->klucz;
        while (ZnajdzDanyElement(zKtorejUsuwamy, klucz)) {
            UZEL(zKtorejUsuwamy, klucz);
        }
        p = p->nast;
    } while (p != zKtorejBierzemy);
}

/*
Opracowaæ bibliotekê podstawowych funkcji operowania na jednokierunkowej liœcie prostej
DONE dodawanie na pocz¹tek i na koniec,
DONE usuwanie pierwszego i ostatniego elementu,
DONE szukanie elementu,
DONE dodawanie nowego elementu przed i za znalezionym,
DONE usuwanie znalezionego,
DONE wyœwietlanie listy od pocz¹tku i od koñca.
DONE Uzupe³niæ program o funkcjê usuwaj¹c¹ z listy wszystkie wyst¹pienia wskazanej wartoœci x w
wersji nierekurencyjnej i rekurencyjnej.
DONE wczytywanie z pliku i zapis ewentualnie
*/
void WyswietlMenu() {
    system("cls");
    printf("Wybierz jaka operacje chcesz wykonac na liscie:\n");
    printf("1 - dodaj element na poczatku listy\n");                //DONE
    printf("2 - dodaj element na koncu listy\n");                   //DONE
    printf("3 - usun pierwszy element listy\n");                    //DONE
    printf("4 - usun ostatni element listy\n");                     //DONE
    printf("5 - dodaj nowy element przed lub za wskazanym\n");      //DONE
    printf("6 - usun wskazany element\n");                          //DONE
    printf("7 - wczytaj zawartosc listy z pliku\n");                //DONE
    printf("8 - zapisz zawartosc listy do pliku\n");                //DONE
    printf("9 - wyswietl zawartosc listy\n");                      //DONE
    printf("0 - zakoncz dzialanie programu\n");                     //DONE    
    printf("Nastepna operacja: ");

  }
