#include "zad9.h"

/*
Opracowaæ bibliotekê podstawowych funkcji operowania na jednokierunkowej liœcie prostej
DONE dodawanie na pocz¹tek i na koniec,
DONE usuwanie pierwszego i ostatniego elementu,
DONE szukanie elementu,
DONE dodawanie nowego elementu przed i za znalezionym,
DONE usuwanie znalezionego,
DONE wyœwietlanie listy od pocz¹tku i od koñca.
DONE wczytywanie z pliku i zapis ewentualnie
*/


int main() {
    lista l = (lista)malloc(sizeof(ellisty));
    l = 0;
    int wybor, liczba, szukana, x;
    FILE* plik;
    while (1) {
        WyswietlMenu();
        printl(l);
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
        case 0:
            ZwolnijListe(&l);
            return 0;
            break;
        }
    }
}