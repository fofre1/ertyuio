#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "zadanie125.h"
#include <limits.h>


//Dodanie na poczatek listy
void DNPL(lista* l, int x) {
    lista q = (lista)malloc(sizeof(ellisty));
    if (*l == NULL) {
        q->klucz = x;
        q->nast = 0;
        *l = q;
        return;
    }
    q->klucz = x;
    q->nast = *l;
    *l = q;
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

//Usuwanie pierwszego elementu
void UPEL(lista* l) {
    lista q;
    if (*l) {
        q = *l;
        *l = (*l)->nast;
        free(q);
    }
}

//Usuwanie ostatniego elementu
void UOEL(lista* l) {
    if (!*l) return;
    lista q;
    while ((*l)->nast)
        l = &(*l)->nast;
    q = *l;
    free(q);
    *l = 0;
}

//Znajdywanie elementu
lista* ZnajdzDanyElement(lista* l, int x) {
    while (*l) {
        if ((*l)->klucz == x) return l;
        l = &(*l)->nast;
    }
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
    while (l) {
        printf("%d ", l->klucz);
        l = l->nast;
    }
    printf("\n");
}

//Wyswietlanie listy od konca rekurencyjnie
void printlk(lista l) {
    if (l == 0) return;
    printlk(l->nast);
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
//Usuwanie wszystkich wystapien iteracyjnie
void UsunWszystkieWystapieniaIteracyjnie(lista* l, int szukana) {
    while (*l) {
        if ((*l)->klucz == szukana)
            UPEL(l);
        else
            l = &(*l)->nast;
    }
}

//Usuwanie rekurencyje
void UsunWszystkieWystapieniaRekurencyjne(lista* l, int szukana) {
    if (*l == 0) return;
    if ((*l)->klucz == szukana) {
        UPEL(l);
        UsunWszystkieWystapieniaRekurencyjne(l, szukana);
    }
    else
        UsunWszystkieWystapieniaRekurencyjne(&(*l)->nast, szukana);
}

lista OdwrocListeIteracyjnie(lista* l) {
    lista odwrocona = 0;
    lista q = *l;
    lista nastepny = 0;
    while (q) {
        nastepny = q->nast;
        q->nast = odwrocona;
        odwrocona = q;
        q = nastepny;
    }
    *l = odwrocona;
    return odwrocona;
}


void OdwrocListeRekurencyjnie(lista* l) {
    if (*l == 0 || (*l)->nast == 0) {
        return;
    }
    lista pierwszy = *l;
    lista reszta = (*l)->nast;
    OdwrocListeRekurencyjnie(&reszta);
    pierwszy->nast->nast = pierwszy;
    pierwszy->nast = 0;
    *l = reszta;
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
    printf("10 - Usuwanie wszystkich wystopien wskazanej liczby\n"); //DONE
    printf("11 - Odwracanie listy\n"); //DONE
    printf("12 - Usun elementy niepodzielne przez k\n"); //DONE
    printf("13 - Znajdz wartosc wystepujaca najczesciej\n"); //DONE
    printf("0 - zakoncz dzialanie programu\n");                     //DONE    
    printf("Nastepna operacja: ");

}

void usunniepodz(lista* l, int k) {
    if (*l == 0) return;
    while (*l) {
        if ((*l)->klucz % k != 0) {
            UPEL(l);
        }
        else {
            l = &(*l)->nast;
        }
    }
}

int MaksymalneWystapienie(lista l) {
    if (l == 0) 
        return INT_MIN;
    int k = 0, w, max;
    lista p, q;
    for (p = l; p != NULL; p = p->nast) {
        w = 1;
        for (q = p->nast; q != NULL; q = q->nast)
            if (q->klucz == p->klucz) w++;
        if (k < w) {
            k = w;
            max = p->klucz;
        }
    }
    return max;
}
