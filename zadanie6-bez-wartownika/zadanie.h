#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define INT_MAX  2147483647

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

    struct el {
        int klucz;
        struct el* nast;
    };

    typedef struct el ellisty;
    typedef ellisty* lista;

    void DNPL(lista* l, int x);
    void DNE(lista* l, int x);
    void DNKL(lista* l, int x);
    void UPEL(lista* l);
    void UOEL(lista* l);
    lista* ZnajdzDanyElement(lista* l, int x);
    void UZEL(lista* l, int szukana);
    void printl(lista l);
    void printlk(lista l);
    void ZDP(lista l, FILE* plik);
    void ZwolnijListe(lista* l);
    void WZP(lista* l, FILE* plik);
    void WyswietlMenu();

#ifdef __cplusplus
}
#endif