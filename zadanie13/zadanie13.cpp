/*13. Zaimplementuj kolejkę priorytetową. Potrzebne będą następujące funkcje: dodaj nowy element; pobierz z listy element o największym PRIORYTECIE (usuwając go jednocześnie z
listy); zmień wartość PRIORYTETU wskazanego elementu.
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <limits.h>

struct el {
    int klucz;
    int priorytet;
    struct el* nast;
};

typedef struct el ellisty;
typedef ellisty* kolejka;

//Dodanie na poczatek listy
void DNPL(kolejka* l, int x, int priorytet) {
    kolejka q = (kolejka)malloc(sizeof(ellisty));
    q->klucz = x;
    q->nast = *l;
    q->priorytet = priorytet;
    *l = q;
}

void UPEL(kolejka* l) {
    kolejka q;
    if (*l) {
        q = *l;
        *l = (*l)->nast;
        free(q);
    }
}

//Dodawanie nowego z bez wartownika
void DNE(kolejka* l, int x, int priorytet) {
    if (*l == 0) {
        DNPL(l, x, priorytet);
        return;
    }
    while ((*l)->priorytet >= priorytet) {
        l = &(*l)->nast;
        if ((*l) == 0) {
            DNPL(l, x, priorytet);
            return;
        }
    }
    DNPL(l, x, priorytet);
}

void printl(kolejka l) {
    while (l) {
        printf("%d(%d) ", l->klucz, l->priorytet);
        l = l->nast;
    }
    printf("\n");
}

int pobierz(kolejka* k) {
    if (*k == 0) {
        return INT_MIN;
    }
    int wartosc = (*k)->klucz;
    UPEL(k);
    return wartosc;
}

void zmienprio(kolejka* k, int x, int noweprio) {
    if (*k == 0) {
        return;
    }
    kolejka* p = k;
    while (*p) {
        if ((*p)->klucz == x) {
            UPEL(p);
            break;
        }
        p = &(*p)->nast;
    }
    DNE(k, x, noweprio);
}

int main()
{
    kolejka k = 0;
    DNE(&k, 5, 10);
    DNE(&k, 3, 20);
    DNE(&k, 7, 15);
    printl(k);
    printf("Pobierz: %d\n", pobierz(&k));
    printl(k);
    zmienprio(&k, 5, 25);
    printl(k);
}

