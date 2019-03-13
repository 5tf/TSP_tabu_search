#include "stdafx.h"
#include "Macierz.h"

using namespace std;

Macierz::Macierz() { }

Macierz::Macierz(unsigned int rozmiar) {
	liczba_wierszy = liczba_kolumn = rozmiar;

	tab = new double *[liczba_wierszy];
	for (int i = 0; i < liczba_wierszy; ++i) {
		tab[i] = new double[liczba_kolumn];
	}
}

Macierz::Macierz(const Macierz & m) {
	liczba_wierszy = m.liczba_wierszy;
	liczba_kolumn = m.liczba_kolumn;

	tab = new double *[liczba_wierszy];
	for (int i = 0; i < liczba_wierszy; ++i) {
		tab[i] = new double[liczba_kolumn];
	}

	for (int i = 0; i < liczba_wierszy; ++i) {

		for (int j = 0; j < liczba_kolumn; ++j)
			tab[i][j] = m.tab[i][j];
	}
}

Macierz & Macierz::operator = (const Macierz & m) {
	if (tab) {
		for (int i = 0; i < liczba_wierszy; ++i)
			delete[] tab[i];
		delete[] tab;
		tab = NULL;
	}
	liczba_wierszy = m.liczba_wierszy;
	liczba_kolumn = m.liczba_kolumn;

	tab = new double *[liczba_wierszy];
	for (int i = 0; i < liczba_wierszy; ++i) {
		tab[i] = new double[liczba_kolumn];
	}

	for (int i = 0; i < liczba_wierszy; ++i) {
		for (int j = 0; j < liczba_kolumn; ++j)
			tab[i][j] = m.tab[i][j];
	}
	return *this;
}

double & Macierz::komorka(unsigned int w, unsigned int k)
{
	return tab[w][k];
}

double Macierz::tablica(int i, int j)
{
	return tab[i][j];
}

int Macierz::getLiczbaMiast()
{
	return liczba_kolumn;
}

Macierz::~Macierz()
{
	if (tab) {
		for (int i = 0; i < liczba_wierszy; ++i)
			delete[] tab[i];
		delete[] tab;
		tab = NULL;
	}
}