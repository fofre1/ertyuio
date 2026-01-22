#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "zadanie125.h"


int main() {
    lista l = (lista)malloc(sizeof(ellisty));
    l = 0;
    int wybor, liczba, szukana, x;
    FILE* plik;
    while (1) {
        WyswietlMenu();
        scanf("%i", &wybor);
        switch (wybor) {
        case 1:
            printf("Jaka liczbe chcesz dodac?: ");
            scanf("%i", &liczba);
            DNPL(&l, liczba);
            break;
        case 2:
            printf("Jaka liczbe chcesz dodac?: ");
            scanf("%i", &liczba);
            DNKL(&l, liczba);
            break;
        case 3:
            UPEL(&l);
            break;
        case 4:
            UOEL(&l);
            break;
        case 5:
            printf("Jaka liczbe chcesz dodac?: ");
            scanf("%i", &x);
            printf("Za jaka liczbe?: ");
            scanf("%i", &szukana);
            printf("Chcesz dodac za(1) czy przed(2)?: ");
            scanf("%i", &liczba);
            if (liczba == 1) {
                DZDEL(&l, x, szukana);
                break;
            }
            if (liczba == 2) {
                DPDEL(&l, x, szukana);
                break;
            }
            break;
        case 6:
            printf("Jaka liczbe chcesz usunac?: ");
            scanf("%i", &liczba);
            UZEL(&l, liczba);
            break;
        case 7:
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
        case 8:
            plik = fopen("zapis.txt", "w");
            if (!plik) {
                printf("Nie mozna otworzyc pliku do zapisu\n");
                _getch();
                break;
            }
            ZDP(l, plik);
            fclose(plik);
            break;
        case 9:
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
        case 10:
            printf("Chcesz usunac rekurencyjnie(1) czy iteracyjnie(2)?: ");
            scanf("%i", &liczba);
            printf("Jaka liczbe?: ");
            scanf("%i", &x);
            if (liczba == 1) {
                UsunWszystkieWystapieniaRekurencyjne(&l, x);
                break;
            }
            if (liczba == 2) {
                UsunWszystkieWystapieniaIteracyjnie(&l, x);
                break;
            }
            break;
        case 11:
            printf("Chcesz odwrocic rekurencyjnie(1) czy iteracyjnie(2)?: ");
            scanf("%i", &liczba);
            if (liczba == 1) {
                OdwrocListeRekurencyjnie(&l);
                break;
            }
            if (liczba == 2) {
                OdwrocListeIteracyjnie(&l);
                break;
            }
            break;
        case 12:
            printf("Podaj liczbe k: ");
            scanf("%i", &x);
            usunniepodz(&l, x);
            break;
        case 13:
            x = MaksymalneWystapienie(l);
            if (x == INT_MIN) {
                printf("Lista jest pusta, nie ma najczesciej wystepujacej wartosci\n");
                printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
                _getch();
                break;
            }
            printf("Wartosc wystepujaca najczesciej: %d\n", x);
            printf("Nacisnij dowolny klawisz, aby kontynuowac\n");
            _getch();
            break;
        case 0:
            ZwolnijListe(&l);
            return 0;
            break;
        }
    }
}