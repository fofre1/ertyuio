
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) ((i-1)/2)


void Kopiec(const char** a, int i, int heapSize) {
	int l, r, largest;
	const char* temp;
	l = LEFT(i);
	r = RIGHT(i);
	if (l<heapSize && strcmp(a[l], a[i])>0)
		largest = l;
	else
		largest = i;
	if (r<heapSize && strcmp(a[r], a[largest])>0)
		largest = r;
	if (largest != i) {
		temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		Kopiec(a, largest, heapSize);
	}
}

void BudowanieKopiec(const char** a, int n) {
	int i;
	const char* temp;
	for (i = PARENT(n); i >= 0; i--)
		Kopiec(a, i, n);
}

void SortowanieKopiec(const char** a, int n) {
	int i;
	const char* temp;
	for (i = n - 1; i > 0; i--) {
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;

		Kopiec(a, 0, i);
	}
}

int main() {
	const char* tablica[] = { "woda", "obiad", "krzeslo", "arbuz", "sesja", "tabaluga", "laptop", "bartosz"};
	int n = sizeof(tablica) / sizeof(tablica[0]);

	printf("Przed sortowaniem:\n");
	for (int i = 0; i < n; i++)
		printf("%s ", tablica[i]);
	printf("\n");

	BudowanieKopiec(tablica, n);
	printf("Po zbudowaniu:\n");
	for (int i = 0; i < n; i++)
		printf("%s ", tablica[i]);
	printf("\n");

	SortowanieKopiec(tablica, n);
	printf("Po sortowaniu:\n");
	for (int i = 0; i < n; i++)
		printf("%s ", tablica[i]);
	printf("\n");

	return 0;
}
