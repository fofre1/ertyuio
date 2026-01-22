#pragma once

//Znalezione w internecie, w visualu potrzebne by³o aby kompilator wiedzial ze pliki zadanie125 sa z jezyka c
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
struct el {
    int klucz;
    struct el* nast;
};

typedef struct el ellisty;
typedef ellisty* lista;

void DNPL(lista* l, int x);
void DNKL(lista* l, int x);
void UPEL(lista* l);
void UOEL(lista* l);
lista* ZnajdzDanyElement(lista* l, int x);
void DZDEL(lista* l, int nowa, int szukana);
void DPDEL(lista* l, int nowa, int szukana);
void UZEL(lista* l, int szukana);
void printl(lista l);
void printlk(lista l);
void ZDP(lista l, FILE* plik);
void WZP(lista* l, FILE* plik);
void ZwolnijListe(lista* l);
void WyswietlMenu();
void UsunZListy(lista* zKtorejUsuwamy, lista zKtorejBierzemy);

#ifdef __cplusplus
}
#endif