#include "zadanie.h"

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

//Dodawanie nowego z bez wartownika
void DNE(lista* l, int x) {
    if (*l == 0) {
        DNPL(l, x);
        return;
    }
    while ((*l)->klucz <= x) {
        l = &(*l)->nast;
        if ((*l) == 0) {
            DNPL(l, x);
            return;
        }
    }
    DNPL(l, x);
}

//Dodanie na koniec listy
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


//Usuwanie pierwszego elementu bez wartownika
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

//Usuwanie ostatniego elementu bez wartownika
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

//Znajdywanie elementu bez wartownika
lista* ZnajdzDanyElement(lista* l, int x) {
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

/*
Korzystaj¹c z tych samych struktur danych co w zadaniu 1, tworzymy teraz listê posortowan¹rosn¹co.
Repertuar operacji na takiej liœcie obejmuje:

DONE dodawanie nowego elementu (wstawiany jest do listy zgodnie z porz¹dkiem),
DONE pobieranie pierwszego i ostatniego elementu,
DONE wyszukiwanie zadanego elementu i usuwanie wyszukanego.
Operacje musz¹ uwzglêdniaæ, ¿e lista jestposortowana.
DONE Zapis i odczyt z pliku oraz wyœwietlanie listy bez zmian.
Zrealizowaæ wersjê listy z wartownikiem i bez wartownika.

*/
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