#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct sasiad {
    int wierzcholek;
    int krawedz;
    struct sasiad* nast;
};

typedef struct sasiad esasiad;
typedef esasiad* sasiedzi;

struct graph {
    int ilePkt;
    sasiedzi* lista;
};

typedef struct graph Graph;
typedef Graph* Graf;

Graf StworzGraf(int n) {
    Graf temp=(Graf)malloc(sizeof(Graph));
    temp->ilePkt = n;
    temp->lista = (sasiedzi*)malloc(n * sizeof(esasiad));
    for (int i = 0; i < n; i++)
        temp->lista[i] = NULL;
    return temp;
}

void dodaj(Graf* graf, int doKtorego, int waga, int zKtorym) {
    sasiedzi nowy = (sasiedzi)malloc(sizeof(esasiad));
    nowy->nast = NULL;
    nowy->krawedz = waga;
    nowy->wierzcholek = zKtorym;
    sasiedzi* p = &((*graf)->lista[doKtorego]);
    while (*p) {
        p = &(*p)->nast;
    }
    *p = nowy;

}

void WyswietlGraf(Graf graf) {
    for (int i = 0; i < graf->ilePkt; i++) {
        printf("Wierzcholek %d: ", i);
        sasiedzi p = graf->lista[i];
        if (!p) {
            printf("brak sasiadow");
        }
        while (p) {
            printf("-> %d(waga=%d) ", p->wierzcholek, p->krawedz);
            p = p->nast;
        }
        printf("\n");
    }
}

//https://eduinf.waw.pl/inf/alg/001_search/0138.php
//Wyswietlanie poza dijkstre
void Dijkstry(Graf graf, int zKtorego, int doKtorego) {
    int* zbiorS = (int*)malloc(graf->ilePkt * sizeof(int));
    for (int i = 0; i < graf->ilePkt; i++)
        zbiorS[i] = -1;
    int* zbiorQ = (int*)malloc(graf->ilePkt * sizeof(int));
    for (int i = 0; i < graf->ilePkt; i++)
        zbiorQ[i] = i;
    int* tabd = (int*)malloc(graf->ilePkt * sizeof(int));
    for (int i = 0; i < graf->ilePkt; i++)
        tabd[i] = INT_MAX;
    int* tabp = (int*)malloc(graf->ilePkt * sizeof(int));
    for (int i = 0; i < graf->ilePkt; i++)
        tabp[i] = -1;
    tabd[zKtorego] = 0;
    for (int i = 0; i < graf->ilePkt; i++) {
        int min = INT_MAX;
        int u = -1;
        for (int j = 0; j < graf->ilePkt; j++) {
            if (zbiorQ[j] != -1 && tabd[zbiorQ[j]] < min) {
                min = tabd[zbiorQ[j]];
                u = zbiorQ[j];
            }
        }
        if (u == -1)
            break;

        for (int j = 0; j < graf->ilePkt; j++) {
            if (zbiorQ[j] == u) {
                zbiorQ[j] = -1;
                break;
            }
        }
        zbiorS[i] = u;

        sasiedzi s = graf->lista[u];
        while (s) {
            int temp = s->wierzcholek;
            int waga = s->krawedz;

            if (tabd[temp] > tabd[u] + waga) {
                tabd[temp] = tabd[u] + waga;
                tabp[temp] = u;
            }
            s = s->nast;
        }
    }
    int* poprzednie = (int*)malloc(graf->ilePkt * sizeof(int)), ileByloPorzednio=1;
    poprzednie[0] = doKtorego;
    int pop = doKtorego;
    do {
        poprzednie[ileByloPorzednio]=tabp[pop];
        pop = tabp[pop];
        ileByloPorzednio++;
    } while (pop != zKtorego);
    ileByloPorzednio--;

    printf("Najtansza droga z %d do %d o koszcie %d przebiega przez: ", zKtorego, doKtorego, tabd[doKtorego]);
    while (ileByloPorzednio > -1) {
        printf("%d", poprzednie[ileByloPorzednio--]);
        if (ileByloPorzednio != -1)
            printf("->");
    }
}

int main() {
    int n = 8;
    Graf test = StworzGraf(n);
    dodaj(&test, 0, 3, 1);
    dodaj(&test, 0, 2, 6);
    dodaj(&test, 0, 5, 2);

    dodaj(&test, 1, 3, 0);
    dodaj(&test, 1, 2, 3);

    dodaj(&test, 2, 5, 0);
    dodaj(&test, 2, 1, 5);
    dodaj(&test, 2, 7, 3);
    dodaj(&test, 2, 3, 6);

    dodaj(&test, 3, 2, 1);
    dodaj(&test, 3, 7, 2);
    dodaj(&test, 3, 5, 4);

    dodaj(&test, 4, 5, 3);
    dodaj(&test, 4, 5, 5);

    dodaj(&test, 5, 1, 2);
    dodaj(&test, 5, 5, 4);
    dodaj(&test, 5, 3, 7);

    dodaj(&test, 6, 2, 0);
    dodaj(&test, 6, 3, 2);
    dodaj(&test, 6, 4, 7);

    dodaj(&test, 7, 3, 5);
    dodaj(&test, 7, 4, 6);
    WyswietlGraf(test);
    Dijkstry(test, 1, 7);
}
