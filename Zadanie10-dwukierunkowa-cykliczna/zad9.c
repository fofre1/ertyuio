#include "zad9.h"

//Dodanie na poczatek listy dwu
void DNPL(lista* l, int x) {
    lista q = (lista)malloc(sizeof(ellisty));
    q->klucz = x;
    if (*l == 0) {
        q->nast = q;
        q->pop = q;
        *l = q;
    }
    else {
        q->nast = *l;
        q->pop = (*l)->pop;
        (*l)->pop = q;
        q->pop->nast = q;
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
    q->nast = *l;
    q->pop = (*l)->pop;
    (*l)->pop->nast = q;
    (*l)->pop = q;
    
}


//Usuwanie pierwszego elementu dwu
void UPEL(lista* l) {
    if (*l == 0) return;
    lista q;
    q = *l;
    if (q->nast == q) {
        free(q);
        *l = 0;
        return;
    }
    q->pop->nast = q->nast;
    q->nast->pop = q->pop;
    *l = q->nast;
    free(q);
}

//Usuwanie ostatniego elementu dwu
void UOEL(lista* l) {
    if (!*l) return;
    if ((*l)->nast == *l) {
        UPEL(l);
        return;
    }
    *l = (*l)->pop;
    UPEL(l);
}

//Znajdywanie elementu
lista* ZnajdzDanyElement(lista* l, int x) {
    lista *q = l;
    do {
        if ((*l)->klucz == x) return l;
        l = &(*l)->nast;
    } while (*l != *q);
    return 0;
}

//Dodawanie zaa znaleziony element
void DZDEL(lista* l, int nowa, int szukana) {
    lista* q = ZnajdzDanyElement(l, szukana);
    if (q == 0) return;
    DNPL(&(*q)->nast, nowa);
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
    do{
        printf("%d ", l->klucz);
        l = l->nast;
    } while (l != a);
    printf("\n");
}

//Wyswietlanie listy od konca rekurencyjnie
void printlk(lista l) {
    if (!l) return;
    lista a = l->pop;
    l = l->pop;
    do {
        printf("%d ", l->klucz);
        l = l->pop;
    } while (l != a);
    printf("\n");
}

//Zapisz do pliku
void ZDP(lista l, FILE* plik) {
    lista a = l;
    do {
        fprintf(plik, "%i", l->klucz);
        l = l->nast;
        if (l) fprintf(plik, " ");
    } while (l != a);
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
