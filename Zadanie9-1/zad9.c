#include "zad9.h"

//Dodanie na poczatek listy dwu
void DNPL(lista* l, int x) {
    lista q = (lista)malloc(sizeof(ellisty));
    q->klucz = x;
    if (*l == 0) {
        q->nast = 0;
        q->pop = 0;
        *l = q;
    }
    else {
        q->nast = *l;
        q->pop = 0;
        (*l)->pop = q;
        *l = q;
    }
}

//Dodanie na koniec listy dwu
void DNKL(lista* l, int x) {
    if (*l == 0) {
        DNPL(l, x);
        return;
    }
    lista q = (lista)malloc(sizeof(ellisty));
    q->klucz = x;
    q->nast = 0;
    while ((*l)->nast)
        l = &(*l)->nast;
    q->pop = *l;
    (*l)->nast = q;
}


//Usuwanie pierwszego elementu dwu
void UPEL(lista* l) {
    lista q;
    if (*l) {
        q = *l;
        *l = (*l)->nast;
        if (*l)
            (*l)->pop = 0;
        free(q);
    }
}

//Usuwanie ostatniego elementu dwu
void UOEL(lista* l) {
    if (!*l) return;
    if ((*l)->nast == 0) {
        UPEL(l);
        return;
    }
    lista q, z;
    while ((*l)->nast)
        l = &(*l)->nast;
    z = (*l)->pop;
    z->nast = 0;
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
    lista a = *q;
    if (a == 0) return;
    if (a->nast == 0) {
        DNKL(&a, nowa);
        return;
    }
    q = &(*q)->nast;
    lista x = (lista)malloc(sizeof(ellisty));
    x->klucz = nowa;
    x->pop = a->pop;
    x->nast = a;
    a->pop->nast = x;
    a->pop = x;
}

//Dodawanie przed znalezionym elementem
void DPDEL(lista* l, int nowa, int szukana) {
    lista* q = ZnajdzDanyElement(l, szukana);
    lista a = *q;
    if (q == 0) return;
    if (a->pop == 0) {
        DNPL(&a, nowa);
        return;
    }
    lista x = (lista)malloc(sizeof(ellisty));
    x->klucz = nowa;
    x->pop = a->pop;
    x->nast = a;
    a->pop->nast = x;
    a->pop = x;
}

//Usuwanie znalezionego elementu
void UZEL(lista* l, int szukana) {
    lista* q = ZnajdzDanyElement(l, szukana);
    if (q == 0) return;
    lista a = *q;
    if (a->pop == 0) {
        UPEL(q);
        return;
    }
    if (a->nast == 0) {
        UOEL(q);
        return;
    }
    lista x, z;
    x = a->nast;
    z = a->pop;
    x->pop = z;
    z->nast = x;
    free(a);
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
