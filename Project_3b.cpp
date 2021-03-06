#include "stdafx.h"
#include "Macierz.h"
#include "TS.h"

//licznik czasu :
//double PCFreq = 0.0;
//__int64 licznik = 0;

/*
void czasStart()
{
LARGE_INTEGER li;
if (!QueryPerformanceFrequency(&li))
cout << "Bďż˝ďż˝d!\n";

PCFreq = double(li.QuadPart) / 1000.0;

QueryPerformanceCounter(&li);
licznik = li.QuadPart;
}
void pobierzCzas()

{
LARGE_INTEGER li;
QueryPerformanceCounter(&li);
cout << "Operacja zajela: " << (li.QuadPart - licznik) / PCFreq << " milisekund" << endl;
}*/
using namespace std;

double PCFreq = 0.0;
__int64 licznik = 0;
using namespace std;

void timeStart()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "Blad!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	licznik = li.QuadPart;
}

void getTime()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	cout << "Operacja zajela: " << (li.QuadPart - licznik) / PCFreq << " milisekund" << endl;
}


int ileMiast(ifstream & plik)
{
	string linia;
	int liczbaMiast = 0;

	for (int i = 2; i != 0; i--)
		getline(plik, linia);

	liczbaMiast = stoi(linia);

	return liczbaMiast;
}

Macierz *wczytajPlik(ifstream & plik)
{
	if (!plik)
	{
		cout << "Nie mozna otworzyc pliku" << endl;
		return NULL;
	}
	int liczba_miast = ileMiast(plik);
	cout << "LIczba miast: " << liczba_miast << endl;
	Macierz *macierz = new Macierz(liczba_miast);
	for (int i = 0; i < liczba_miast; i++)
	{
		for (int j = 0; j < liczba_miast; j++)
		{
			int odleglosc = 0;
			plik >> odleglosc;
			macierz->komorka(i, j) = odleglosc;
		}
	}

	/*
	printf("   ");
	for (int i = 0; i < liczba_miast; i++)
	{
	printf("%3d ", i);
	}
	printf("\n");
	printf("   ");
	for (int i = 0; i < liczba_miast; i++)
	{
	printf("----", i);
	}
	printf("\n");
	for (int i = 0; i < liczba_miast; i++)
	{
	printf("%2d|", i);
	for (int j = 0; j < liczba_miast; j++)
	{
	cout << macierz->komorka(i, j);
	}
	printf("\n");
	}*/
	/*
	for (int i = 0; i < liczba_miast; ++i, cout << endl)
	for (int j = 0; j < liczba_miast; ++j)
	cout << macierz->komorka(i, j) << '\t';
	*/
	return macierz;
}

void tabuSearch(Macierz &m) {
	TS example(m);

	int opt = 2;

	//cout << "1.NN, 2.Permutacja, 3.Losowy";
	//cin >> opt;

	switch (opt)
	{
	case 1:
		example.NN(m);
		break;
	case 2:
		example.natural();
		break;
	case 3:
		example.randomN();
		break;
	}

	int iteracje = 500;
	//cout << "Liczba iteracji";
	//cin >> iteracje;

	int opte = 1;
	//cout << "1.Swap, 2.Insert, 3.Invert";
	//cin >> opte;

	//switch (opte)
	{
	//case 1:
		
		example.localSearch(1, 500, m);
		
		cout << "Wynik: " << example.bestResultOverAll << " ";
		//break;
	//case 2:
		//timeStart();
		//example.localSearch(2, iteracje, m);
		//getTime();
		//cout << "Wynik: " << example.bestResultOverAll << " ";
		//break;
	//case 3:
		//timeStart();
		//example.localSearch(3, iteracje, m);
		//getTime();
		//cout << "Wynik: " << example.bestResultOverAll << " ";
		//break;
	}

	//for (int i = 0; i < example.cities; i++)
	//{
	//	cout << example.bestWayOverAll[i] << "->";
	//}
	

	//const double pc = 0.5;

}

int main()

{
	string nazwa;
	Macierz * macierz = NULL;
	srand(time(NULL));
	//cout << "Podaj nazwe pliku do wczytania" << endl;
	//cin >> nazwa;
	//nazwa = nazwa + ".txt";



	for (int i = 1; i < 16; i++)
	{
		if (i == 1)
			nazwa = "data17.txt";
		if (i == 2)
			nazwa = "data34.txt";
		if (i == 3)
			nazwa = "data36.txt";
		if (i == 4)
			nazwa = "data39.txt";
		if (i == 5)
			nazwa = "data43.txt";
		if (i == 6)
			nazwa = "data45.txt";
		if (i == 7)
			nazwa = "data48.txt";
		if (i == 8)
			nazwa = "data53.txt";
		if (i == 9)
			nazwa = "data56.txt";
		if (i == 10)
			nazwa = "data65.txt";
		if (i == 11)
			nazwa = "data70.txt";
		if (i == 12)
			nazwa = "data71.txt";
		if (i == 13)
			nazwa = "data100.txt";
		if (i == 14)
			nazwa = "data171.txt";
		if (i == 15)
			nazwa = "data323.txt";
		


		ifstream plik(nazwa);

		macierz = wczytajPlik(plik);
		
		timeStart();
		tabuSearch(*macierz);
		getTime();
	}


	system("pause");
	return 0;
}
