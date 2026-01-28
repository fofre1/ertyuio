#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "zadanie.h"

int main() {
    lista l = (lista)malloc(sizeof(ellisty));
    lista l1 = (lista)malloc(sizeof(ellisty));
    lista l2 = (lista)malloc(sizeof(ellisty));
    l->klucz = l1->klucz=l2->klucz=INT_MAX;
    l->nast = l1->nast=l2->nast= 0;
    int wybor, liczba, szukana, x;
    FILE* plik;
    while (1) {
        WyswietlMenu();
        scanf("%i", &wybor);
        switch (wybor) {
        case 1:
            printf("Jaka liczbe chcesz dodac?: ");
            scanf("%i", &liczba);
            DNE(&l, liczba);
            break;
        case 2:
            UPEL(&l);
            break;
        case 3:
            UOEL(&l);
            break;
        case 4:
            printf("Jaka liczbe chcesz usunac?: ");
            scanf("%i", &liczba);
            UZEL(&l, liczba);
            break;
        case 5:
            plik = fopen("zapis.txt", "r");
            if (!plik) {
                printf("Nie mozna otworzyc pliku do odczytu\n");
                _getch();
                break;
            }
            ZwolnijListe(&l);
            WZP(&l, plik);
            fclose(plik);
            break;
        case 6:
            plik = fopen("zapis.txt", "w");
            if (!plik) {
                printf("Nie mozna otworzyc pliku do zapisu\n");
                _getch();
                break;
            }
            ZDP(l, plik);
            fclose(plik);
            break;
        case 7:
            printf("1 - od poczatku, 2 - od konca: ");
            scanf("%i", &x);
            switch (x) {
            case 1:
                system("cls");
                printl(l);
                printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
                _getch();
                break;
            case 2:
                system("cls");
                printlk(l);
                printf("\nNacisnij dowolny klawisz, aby kontynuowac\n");
                _getch();
                break;
            }
            break;
        case 8:
            while (1) {
                system("cls");
                printf("Jaka liczbe chcesz dodac? (-1 by zakonczyc): ");
                scanf("%i", &liczba);
                if (liczba == -1)
                    break;
                DNE(&l1, liczba);
            }
            while (1) {
                system("cls");
                printf("Jaka liczbe chcesz dodac? (-1 by zakonczyc): ");
                scanf("%i", &liczba);
                if (liczba == -1)
                    break;
                DNE(&l2, liczba);
            }
            system("cls");
            printf("\n");
            printl(l1);
            printf("\n");
            printl(l2);
            printf("\n");
            polacz(&l1, &l2);
            printl(l1);
            _getch();
            break;
        case 0:
            ZwolnijListe(&l);
            return 0;
            break;
        }
    }
}