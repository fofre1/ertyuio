#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "zadanie.h"

void DNPL(lista* l, int x) {
    lista q = (lista)malloc(sizeof(ellisty));
    q->klucz = x;
    q->nast = *l;
    *l = q;
}

//Dodawanie nowego z wartownika
void DNE(lista* l, int x) {
    while ((*l)->klucz <= x)
        l = &(*l)->nast;
    DNPL(l, x);
}

//Dodanie na koniec listy
void DNKL(lista* l, int x) {
    lista q = (lista)malloc(sizeof(ellisty));
    q->klucz = x;
    q->nast = 0;
    while ((*l))
        l = &(*l)->nast;
    *l = q;
}

//Usuwanie pierwszego elementu z wartownika
void UPEL(lista* l) {
    lista q;
    if (*l) {
        q = *l;
        *l = (*l)->nast;
        free(q);
    }
}

//Usuwanie ostatniego elementu bez wartownika
void UOEL(lista* l) {
    if (!*l) return;
    lista q, p;
    while ((*l)->nast && (*l)->nast->klucz != INT_MAX)
        l = &(*l)->nast;
    q = *l;
    p = (*l)->nast;
    free(q);
    *l = p;

}

//Znajdywanie elementu bez wartownika
lista* ZnajdzDanyElement(lista* l, int x) {
    if (x == INT_MAX) return 0; //Zabezpieczenie aby nie mozna bylo usunac wartownika
    while (*l) {
        if ((*l)->klucz > x) return 0; //Sprawdzamy czy juz przeszlismy ewewntualne miejsce gdzie moglo by byc x
        if ((*l)->klucz == x) return l;
        l = &(*l)->nast;
    }
    return 0;
}

//Usuwanie znalezionego elementu
void UZEL(lista* l, int szukana) {
    lista* q = ZnajdzDanyElement(l, szukana);
    if (q == 0) return;
    UPEL(q);
}

//Wyswietlanie listy od poczatku
void printl(lista l) {
    while (l) {
        if (l->klucz == INT_MAX) {
            printf("\n");
            return;
        }
        printf("%d ", l->klucz);
        l = l->nast;
    }
    printf("\n");
}

//Wyswietlanie listy od konca rekurencyjnie
void printlk(lista l) {
    if (l == 0) return;
    printlk(l->nast);
    if (l->klucz == INT_MAX) return;
    printf("%i ", l->klucz);
}

//Zapisz do pliku
void ZDP(lista l, FILE* plik) {
    while (l) {
        fprintf(plik, "%i", l->klucz);
        l = l->nast;
        if (l) fprintf(plik, " ");
    }
    fprintf(plik, "\n");
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

//Wczytaj z pliku
void WZP(lista* l, FILE* plik) {
    ZwolnijListe(l);
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

void WyswietlMenu() {
    system("cls");
    printf("Wybierz jaka operacje chcesz wykonac na liscie:\n");
    printf("1 - dodaj element do listy\n");                //DONE
    printf("2 - usun pierwszy element listy\n");                   //DONE
    printf("3 - usun ostatni element listy\n");                    //DONE
    printf("4 - usun wskazany element\n");                          //DONE
    printf("5 - wczytaj zawartosc listy z pliku\n");                //DONE
    printf("6 - zapisz zawartosc listy do pliku\n");                //DONE
    printf("7 - wyswietl zawartosc listy\n");                      //DONE
    printf("0 - zakoncz dzialanie programu\n");                     //DONE    
    printf("Nastepna operacja: ");
}