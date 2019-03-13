#pragma once
class Macierz
{
public:
	Macierz();
	double tablica(int, int);
	Macierz(unsigned int rozmiar);
	~Macierz();
	Macierz(const Macierz & m);
	Macierz & operator = (const Macierz & m);
	double & komorka(unsigned int w, unsigned int k);
	int getLiczbaMiast();

private:

	int liczba_wierszy, liczba_kolumn;
	double **tab;
};
