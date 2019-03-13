#pragma once
#include "Macierz.h"

class TS {
public:

	int *tabu;
	int kadencja;
	int iterNumber;
	int cities;
	int bestTempOne;
	int bestTempTwo;
	double bestResultOverAll = DBL_MAX;
	double bestNeighbourResult = DBL_MAX;
	double wayResult = 0;
	TS(Macierz);

	int *bestNeighbour;
	int *bestWayOverAll;
	int *way;
	int *firstWay;
	int tempOne;
	int tempTwo;

	void citiesAmount(Macierz);
	void NN(Macierz);
	void randomN();
	void natural();
	void toResult(int*, Macierz);
	void randomise();
	void toWay(int*);
	void toBestWay(int*);
	void toFirstWay(int*);
	void toBestNeighbour(int*);
	void swap();
	void insert();
	void invert();
	void localSearch(int, int, Macierz);

	~TS();
}; 
