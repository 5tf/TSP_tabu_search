#include "stdafx.h"
#include "TS.h"
#include "Macierz.h"

using namespace std;

TS::TS(Macierz macierz)
{
	citiesAmount(macierz);
	bestNeighbour = new int[cities];
	bestWayOverAll = new int[cities];
	way = new int[cities];
	firstWay = new int[cities];
	tabu = new int[cities];
	kadencja = cities / 4;
	iterNumber = 0;
	for (int i = 0; i < cities; i++)
	{
		tabu[i] = 0;
	}
}

void TS::NN(Macierz macierz) //dobrze
{
	int n = macierz.getLiczbaMiast();
	int change = 0;
	firstWay[0] = change;
	double mindis;
	double curdis;
	bool *checked = new bool[n];
	for (int i = 0; i < n; i++)
		checked[i] = true;
	checked[change] = false;
	int li = 0;
	int ci = change;
	for (int i = 1; i < n; i++)
	{
		mindis = DBL_MAX;
		for (int j = 0; j < n; j++)
		{
			if (checked[j] && j != ci)
			{
				curdis = macierz.komorka(ci, j);
				if (curdis < mindis)
				{
					mindis = curdis;
					li = j;
				}
			}
		}
		checked[li] = false;
		firstWay[i] = li;
		ci = li;
	}
	firstWay[n] = change;
	delete[]  checked;
}

void TS::citiesAmount(Macierz macierz)
{
	cities = macierz.getLiczbaMiast();
}

void TS::randomN() //dobrze
{
	int change = 0;
	firstWay[0] = change;
	bool *checked = new bool[cities];
	for (int i = 0; i < cities; i++)
		checked[i] = true;
	checked[change] = false;

	for (int i = 1; i < cities; i++)
	{
	losuj:
		change = rand() % cities;
		if (checked[change] == true)
		{
			firstWay[i] = change;
			checked[change] = false;
		}
		else
			goto losuj;
	}
	delete[] checked;
}

void TS::natural() //dobrze
{
	for (int i = 0; i < cities; i++)
	{
		firstWay[i] = i;
	}
}

void TS::toResult(int *way, Macierz macierz) //dobrze
{
	wayResult = 0;

	for (int i = 0; i < cities - 1; i++)
	{
		wayResult += macierz.tablica(way[i], way[i + 1]);
	}

	wayResult += macierz.tablica(way[cities - 1], way[0]);
}

void TS::randomise()
{
	do
	{
		do
		{
			tempOne = rand() % cities;
			tempTwo = rand() % cities;

		} while (tempOne == tempTwo);

		if (tempOne > tempTwo)
		{
			int tempThree = tempOne;
			tempOne = tempTwo;
			tempTwo = tempThree;
		}
	} while (tabu[tempOne] > iterNumber && tabu[tempTwo] > iterNumber);
}

void TS::toWay(int* tab) //dobrze
{
	for (int i = 0; i < cities; i++)
		way[i] = tab[i];
}

void TS::toBestWay(int* tab) //dobrz
{
	for (int i = 0; i < cities; i++)
		bestWayOverAll[i] = tab[i];
}

void TS::toFirstWay(int* tab) //dobrze
{
	for (int i = 0; i < cities; i++)
		firstWay[i] = tab[i];
}

void TS::toBestNeighbour(int* tab) //dobrze
{
	for (int i = 0; i < cities; i++)
		bestNeighbour[i] = tab[i];
}

void TS::swap()
{
	randomise();
	int tempThree = way[tempOne];
	way[tempOne] = way[tempTwo];
	way[tempTwo] = tempThree;
}

void TS::insert()
{
	int *tempWay = new int[cities];
	for (int i = 0; i < cities; i++)
		tempWay[i] = way[i];
	randomise();
	way[tempOne] = way[tempTwo];
	for (int i = tempOne + 1; i <= tempTwo; i++)
		way[i] = tempWay[i - 1];
	for (int i = tempTwo + 1; i < cities; i++)
		way[i] = tempWay[i];
	delete[]  tempWay;
}

void TS::invert()
{
	int *tempWay = new int[cities];
	for (int i = 0; i < cities; i++)
		tempWay[i] = way[i];
	randomise();
	int j = tempTwo;
	int i = tempOne;

	while (j >= tempOne) {
		way[i] = tempWay[j];
		j--, i++;
	}
	delete[]  tempWay;
}

void TS::localSearch(int opt, int iteracje, Macierz macierz)
{
	if (opt == 1)
	{
		toWay(firstWay);
		toBestWay(firstWay);
		toResult(way, macierz);
		bestResultOverAll = wayResult;

		for (int i = 0; i < iteracje; i++) {

			toWay(firstWay);

			for (int n = 100; n > 0; n--)
			{
				if (i % 100 == 0) {
					for (int j = 0; j < 10; j++)
					{
						swap();
					}
					for (int j = 0; j < cities; j++)
					{
						tabu[j] = 0;
					}
				}
				swap();
				toResult(way, macierz);
				if (wayResult < bestNeighbourResult)
				{
					toBestNeighbour(way);
					bestNeighbourResult = wayResult;
					bestTempOne = tempOne;
					bestTempTwo = tempTwo;
				}
				if (wayResult < bestResultOverAll)
				{
					toBestWay(way);
					bestResultOverAll = wayResult;
				}
				toWay(firstWay);

				if (n == 1)
				{
					toFirstWay(bestNeighbour);
					bestNeighbourResult = DBL_MAX;
				}
			}
			iterNumber++;
			tabu[bestTempOne] = iterNumber + kadencja;
			tabu[bestTempTwo] = iterNumber + kadencja;
		}
	}
	if (opt == 2)
	{
		toWay(firstWay);
		toBestWay(firstWay);
		toResult(way, macierz);
		bestResultOverAll = wayResult;

		for (int i = 0; i < iteracje; i++) {

			toWay(firstWay);

			for (int n = 100; n > 0; n--)
			{
				if (i % 10 == 0) {
					for (int j = 0; j < 10; j++)
					{
						insert();
					}
					for (int j = 0; j < cities; j++)
					{
						tabu[j] = 0;
					}
				}
				insert();
				toResult(way, macierz);
				if (wayResult < bestNeighbourResult)
				{
					toBestNeighbour(way);
					bestNeighbourResult = wayResult;
					bestTempOne = tempOne;
					bestTempTwo = tempTwo;
				}
				if (wayResult < bestResultOverAll)
				{
					toBestWay(way);
					bestResultOverAll = wayResult;
				}
				toWay(firstWay);

				if (n == 1)
				{
					toFirstWay(bestNeighbour);
					bestNeighbourResult = DBL_MAX;
				}
			}
			iterNumber++;
			tabu[bestTempOne] = iterNumber + kadencja;
			tabu[bestTempTwo] = iterNumber + kadencja;
		}
	}
	if (opt == 3)
	{
		toWay(firstWay);
		toBestWay(firstWay);
		toResult(way, macierz);
		bestResultOverAll = wayResult;

		for (int i = 0; i < iteracje; i++) {

			toWay(firstWay);

			for (int n = 100; n > 0; n--)
			{
				if (i % 10 == 0) {
					for (int j = 0; j < 10; j++)
					{
						invert();
					}
					for (int j = 0; j < cities; j++)
					{
						tabu[j] = 0;
					}
				}
				invert();
				toResult(way, macierz);
				if (wayResult < bestNeighbourResult)
				{
					toBestNeighbour(way);
					bestNeighbourResult = wayResult;
					bestTempOne = tempOne;
					bestTempTwo = tempTwo;
				}
				if (wayResult < bestResultOverAll)
				{
					toBestWay(way);
					bestResultOverAll = wayResult;
				}
				toWay(firstWay);

				if (n == 1)
				{
					toFirstWay(bestNeighbour);
					bestNeighbourResult = DBL_MAX;
				}
			}
			iterNumber++;
			tabu[bestTempOne] = iterNumber + kadencja;
			tabu[bestTempTwo] = iterNumber + kadencja;
		}
	}
}

TS::~TS()
{
	delete[] bestNeighbour;
	delete[] bestWayOverAll;
	delete[] way;
	delete[] firstWay;
	delete[] tabu;
}







