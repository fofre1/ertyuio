#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

struct el {
    int klucz;
    struct el* nast;
    struct el* pop;
};

typedef struct el ellisty;
typedef ellisty* lista;
void DNPL(lista* l, int x);                 //Dodanie na poczatek listy
void DNKL(lista* l, int x);                 //Dodanie na koniec listy
void UPEL(lista* l);                        //Usuniecie pierwszego elementu
void UOEL(lista* l);                        //Usuniecie ostatniego elementu
lista* ZnajdzDanyElement(lista* l, int x);  //Znajdywanie zadanego elementu
void DZDEL(lista* l, int nowa, int szukana);//Dodawanie za znaleziony element
void DPDEL(lista* l, int nowa, int szukana);//Dodawanie przed znaleziony element
void UZEL(lista* l, int szukana);           //Usuniecie znalezionego elementu
void printl(lista l);                       //Wyswietlanie listy
void printlk(lista l);                      //Wyswietlanie listy od konca
void ZDP(lista l, FILE* plik);              //Zapis do pliku
void WZP(lista* l, FILE* plik);             //Wczytanie z pliku
void ZwolnijListe(lista* l);                //Zwolnienie pamieci zajmowana przez liste
void WyswietlMenu();                        //Wyswietla wszystkie mozliwe opcje

#ifdef __cplusplus
}
#endif