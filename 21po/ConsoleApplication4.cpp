/*
Porównanie wydajności algorytmów sortowania. 
Napisać osobne procedury sortowania metodami: 
bombelkowe
przez wstawianie
metodą Shella (na bazie sortowania bąbelkowego)
quick sort
W każdej z nich należy stosownie osadzić instrukcje zliczania wykonanych podstawień i porównań sortowanych danych. 
Program generuje losowo długą, testową serię liczb (N ∼ 10 000) i kolejno poddaje je (te same losowe dane!) 
sortowaniu wszystkimi wymienionymi metodami, rejestrując dla każdej z nich liczbę wykonanych porównań i podstawień
kluczy. Cykl ten powtarzany jest M ∼ 1000 razy, dla nowych losowych danych. Dla każdej z
wymienionych metod program powinien wyświetlić w tabeli następujące dane: maksymalna
i minimalna w serii M prób liczba wykonanych podstawień i porównań sortowanych kluczy
oraz średnia liczba podstawień i porównań.
*/

#define N 10000
#define M 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GenerowanieTablicy(int *tab) {
	for (int i = 0; i < N; i++)
		tab[i] = rand();
}

void ZamienMiejscami(int tab[], int zKtorego, int doKtorego) {
	int temp = tab[doKtorego];
	tab[doKtorego] = tab[zKtorego];
	tab[zKtorego] = temp;
}

void Bombelkowe(int tab[], int *porownania, int *przestawienia) {
	*porownania = *przestawienia = 0;
	for (int i = 1; i < N; i++){
		for (int j = N - 1; j >= i; j--) {
			(*porownania)++;
			if (tab[j-1] > tab[j]) {
				ZamienMiejscami(tab, j-1, j);
				(*przestawienia)+=3;
			}
		}
	}

}

void PoprzezWstawianie(int tab[], int* porownania, int* przestawienia) {
	*porownania = *przestawienia = 0;
	int temp, i, j;
	for (i = 1; i < N; i++) {
		(*porownania)++;
		if (tab[i] < tab[0]) {
			temp = tab[0];
			tab[0] = tab[i];
			(*przestawienia) += 2;
		}
		else {
			temp = tab[i];
			(*przestawienia)++;
		}
		for (j = i - 1; temp < tab[j]; j--) {
			(*porownania)++;
			tab[j + 1] = tab[j];
			(*przestawienia)++;
		}
		tab[j + 1] = temp;
		(*przestawienia)++;
	}
}

void MetodaShella(int tab[], int* porownania, int* przestawienia) {
	*porownania = *przestawienia = 0;
	int h = 1;
	while (h < N)
		h = 3 * h + 1;
	h /= 3;
	while (h > 0) {
		for (int i = h; i < N; i++) {
			for (int j = N - 1; j >= i; j--) {
				(*porownania)++;
				printf("l\n");
				if (tab[j - h] > tab[j]) {
					ZamienMiejscami(tab, j - h, j);
					(*przestawienia)+=3;
				}
			}
		}
		h /= 3;
	}
}

int Partition(int tab[], int* porownania, int* przestawienia, int poczatek, int koniec) {
	int _r = rand() % (koniec - poczatek + 1) + poczatek, x, i, j;
	ZamienMiejscami(tab, poczatek, _r);
	(*przestawienia)+=3;
	x = tab[poczatek];
	i = poczatek - 1;
	j = koniec + 1;
	do {
		do {
			j--;
			(*porownania)++;
		} while (tab[j] > x);
		do {
			i++;
			(*porownania)++;
		} while (tab[i] < x);
		if (i < j) {
			ZamienMiejscami(tab, i, j);
			(*przestawienia)+=3;
		}
	} while (i < j);
	return j;
}

void  QuickSort(int tab[], int* porownania, int* przestawienia, int poczatek, int koniec) {
	int q;
	if (poczatek < koniec) {
		q = Partition(tab, porownania, przestawienia, poczatek, koniec);
		QuickSort(tab, porownania, przestawienia, poczatek, q);
		QuickSort(tab, porownania, przestawienia, q+1, koniec);
	}
}




int main() {
	int maxPorownan[4], minPorownan[4], maxPrzestawien[4], minPrzestawien[4];
	long long sumaPodstawienia[4], sumaPorownania[4];
	float srPodstawienia[4], srPorownania[4];
	int tabB[N], tabPW[N], tabS[N], tabQS[N];
	//0 - Boblowe, 1 - Wstawianie, 2 - Shell, 3 - Quick

	int porownania = 0, przestawienia = 0;
	int tab[N];
	srand(time(NULL));

	//Jednorazowa próba aby ustalić wartości odniesienia min i max dla kazdego z algorytmów
	GenerowanieTablicy(tab);
	for (int i = 0; i < N; i++) {
		tabB[i] = tabPW[i] = tabS[i] = tabQS[i] = tab[i];
	}
	//Bombelkowe
	Bombelkowe(tabB, &porownania, &przestawienia);
	maxPorownan[0] = minPorownan[0] = porownania;
	maxPrzestawien[0] = minPrzestawien[0] = przestawienia;
	sumaPodstawienia[0] = sumaPorownania[0] = 0;
	sumaPodstawienia[0] += przestawienia;
	sumaPorownania[0] += porownania;
	porownania = przestawienia = 0;
	//Wstawianie
	PoprzezWstawianie(tabPW, &porownania, &przestawienia);
	maxPorownan[1] = minPorownan[1] = porownania;
	maxPrzestawien[1] = minPrzestawien[1] = przestawienia;
	sumaPodstawienia[1] = sumaPorownania[1] = 0;
	sumaPodstawienia[1] += przestawienia;
	sumaPorownania[1] += porownania;
	porownania = przestawienia = 0;
	// Shell
	MetodaShella(tabS, &porownania, &przestawienia);
	maxPorownan[2] = minPorownan[2] = porownania;
	maxPrzestawien[2] = minPrzestawien[2] = przestawienia;
	sumaPodstawienia[2] = sumaPorownania[2] = 0;
	sumaPodstawienia[2] += przestawienia;
	sumaPorownania[2] += porownania;
	porownania = przestawienia = 0;
	// QuickSort
	QuickSort(tabQS, &porownania, &przestawienia, 0, N - 1);
	maxPorownan[3] = minPorownan[3] = porownania;
	maxPrzestawien[3] = minPrzestawien[3] = przestawienia;
	sumaPodstawienia[3] = sumaPorownania[3] = 0;
	sumaPodstawienia[3] += przestawienia;
	sumaPorownania[3] += porownania;
	porownania = przestawienia = 0;
	//Głowna pętla testu
	for (int proba = 0; proba < M-1; proba++) {
		porownania = 0, przestawienia = 0;
		GenerowanieTablicy(tab);
		for (int i = 0; i < N; i++) {
			tabB[i] = tabPW[i] = tabS[i] = tabQS[i] = tab[i];
		}
		//Bombelkowe
		Bombelkowe(tabB, &porownania, &przestawienia);
		if (porownania > maxPorownan[0])	maxPorownan[0] = porownania;
		else if (porownania < minPorownan[0]) minPorownan[0] = porownania;
		if (przestawienia > maxPrzestawien[0])	maxPrzestawien[0] = przestawienia;
		else if (przestawienia < minPrzestawien[0]) minPrzestawien[0] = przestawienia;
		sumaPodstawienia[0] += przestawienia;
		sumaPorownania[0] += porownania;
		porownania = przestawienia = 0;
		// Wstawianie
		PoprzezWstawianie(tabPW, &porownania, &przestawienia);
		if (porownania > maxPorownan[1]) maxPorownan[1] = porownania;
		else if (porownania < minPorownan[1]) minPorownan[1] = porownania;
		if (przestawienia > maxPrzestawien[1]) maxPrzestawien[1] = przestawienia;
		else if (przestawienia < minPrzestawien[1]) minPrzestawien[1] = przestawienia;
		sumaPodstawienia[1] += przestawienia;
		sumaPorownania[1] += porownania;
		porownania = przestawienia = 0;
		// Shell
		MetodaShella(tabS, &porownania, &przestawienia);
		if (porownania > maxPorownan[2]) maxPorownan[2] = porownania;
		else if (porownania < minPorownan[2]) minPorownan[2] = porownania;
		if (przestawienia > maxPrzestawien[2]) maxPrzestawien[2] = przestawienia;
		else if (przestawienia < minPrzestawien[2]) minPrzestawien[2] = przestawienia;
		sumaPodstawienia[2] += przestawienia;
		sumaPorownania[2] += porownania;
		porownania = przestawienia = 0;
		// QuickSort
		QuickSort(tabQS, &porownania, &przestawienia, 0, N - 1);
		if (porownania > maxPorownan[3]) maxPorownan[3] = porownania;
		else if (porownania < minPorownan[3]) minPorownan[3] = porownania;
		if (przestawienia > maxPrzestawien[3]) maxPrzestawien[3] = przestawienia;
		else if (przestawienia < minPrzestawien[3]) minPrzestawien[3] = przestawienia;
		sumaPodstawienia[3] += przestawienia;
		sumaPorownania[3] += porownania;
		porownania = przestawienia = 0;
		printf("%d\n", proba);
	}
	for (int i = 0; i < 4; i++) {
		srPodstawienia[i] = (float)sumaPodstawienia[i] / M;
		srPorownania[i] = (float)sumaPorownania[i] / M;
	}

	printf("--------------------------------------------------------------------------------\n");
	printf("| %-20s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s |\n", "Metoda", "Min przes", "Max przes", "Sred przes", "Min por", "Max por", "Sred por");
	printf("--------------------------------------------------------------------------------\n");
    //bombel
	printf("| %-20s | %-10d | %-10d | %-10.0f | %-10d | %-10d | %-10.0f |\n", "Bąbelkowe", minPrzestawien[0], maxPrzestawien[0], srPodstawienia[0], minPorownan[0], maxPorownan[0], srPorownania[0]);
	//przemieszczenie
	printf("| %-20s | %-10d | %-10d | %-10.0f | %-10d | %-10d | %-10.0f |\n", "Wstawianie", minPrzestawien[1], maxPrzestawien[1], srPodstawienia[1], minPorownan[1], maxPorownan[1], srPorownania[1]);
	//shell
	printf("| %-20s | %-10d | %-10d | %-10.0f | %-10d | %-10d | %-10.0f |\n", "Shell", minPrzestawien[2], maxPrzestawien[2], srPodstawienia[2], minPorownan[2], maxPorownan[2], srPorownania[2]);
	//quickSort
	printf("| %-20s | %-10d | %-10d | %-10.0f | %-10d | %-10d | %-10.0f |\n", "QuickSort", minPrzestawien[3], maxPrzestawien[3], srPodstawienia[3], minPorownan[3], maxPorownan[3], srPorownania[3]);
	printf("--------------------------------------------------------------------------------\n");


}
