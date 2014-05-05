#include "stdafx.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "GrafMacierz.h"

using namespace std;

vector<short> waga;
struct cmp
{
	bool operator() (const short &a, const short &b)
	{
		if (waga[a] < waga[b]) return true;
		if (waga[a] > waga[b]) return false;
		return a<b;
	}
};

//Funkcje pomocnicze
short* GrafMacierz::matrix(int x, int y) {
	if (x>y)
		return &macierz[x][y];
	else
		return &macierz[y][x];
}

short GrafMacierz::Find(short a, short *tab) {
	if (tab[a] == a) return a;
	short fa = Find(tab[a], tab);
	tab[a] = fa;
	return fa;
}

bool GrafMacierz::Union(short a, short b, short *tab, short *liczebnosc) {
	short fa = Find(a, tab);
	short fb = Find(b, tab);

	if (fa == fb) return false;
	if (liczebnosc[fa] <= liczebnosc[fb])
	{
		liczebnosc[fb] += liczebnosc[fa];
		tab[fa] = fb;
	}
	else
	{
		liczebnosc[fa] += liczebnosc[fb];
		tab[fb] = fa;
	}
	return true;
}


//Gettery i Settery
void GrafMacierz::wpiszGraf(short **inputTab, int size) {
	vertexs = size;
	macierz = new short*[vertexs];
	for (int i = 1; i<vertexs; i++)
		macierz[i] = new short[i];

	for (int x = 1; x<vertexs; x++)
	for (int y = 0; y<x; y++)
		*(matrix(x, y)) = inputTab[x][y];
	//wypiszGraf();
}

void GrafMacierz::wypiszGraf() {
	for (int x = 1; x<vertexs; x++){
		for (int y = 0; y<x; y++)
			std::cout << macierz[x][y] << " ";
		std::cout << std::endl;
	}
}


//Algorytmy
int GrafMacierz::Prim() {
	set<short, cmp> kopiec2;
	vector<short> pi(vertexs);
	vector<bool> visited(vertexs, false);

	short MAX = 32767;
	waga.resize(vertexs, MAX);

	pi[0] = 0;
	waga[0] = 0;

	for (short i = 0; i<vertexs; i++)
		kopiec2.insert(i);

	int suma = 0;
	while (kopiec2.empty() == false)
	{
		short min = *(kopiec2.begin());
		suma += waga[min];
		kopiec2.erase(kopiec2.begin());
		visited[min] = true;

		for (int i = 0; i<vertexs; i++)
		if (min != i && (*matrix(min, i) != 0))
		if (visited[i] == false)
		if (*matrix(min, i) < waga[i])	{
			kopiec2.erase(kopiec2.find(i));
			waga[i] = *matrix(min, i);
			kopiec2.insert(i);
			pi[i] = min;
		}
	}

	return suma;
}

int GrafMacierz::Kruskal() {
	vector< pair< short, pair<short, short> > > krawedzie;
	for (int x = 1; x<vertexs; x++)
	for (int y = 0; y<x; y++)
	if (*(matrix(x, y)) != 0)
		krawedzie.push_back(make_pair(*matrix(x, y), make_pair(x, y)));

	sort(krawedzie.begin(), krawedzie.end());

	vector< pair<short, short> > MST;

	short *helpVec = new short[vertexs];
	short *liczebnosc = new short[vertexs];

	for (int i = 0; i<vertexs; i++) {
		helpVec[i] = i;
		liczebnosc[i] = 1;
	}

	vector< pair<short, pair<short, short> > >::iterator it = krawedzie.begin();

	int licznik = 0, suma = 0;
	while (licznik<vertexs - 1) {
		if (Union((*it).second.first, (*it).second.second, helpVec, liczebnosc) == true) {
			MST.push_back(make_pair((*it).second.first, (*it).second.second));
			licznik++;
			suma += (*it).first;
		}
		it++;
	}

	return suma;
}

vector<short> GrafMacierz::Dijkstry() {
	set<int, cmp> kopiec2;
	vector<short> pi(vertexs);
	vector<bool> visited(vertexs, false);

	short MAX = 32767;
	waga.resize(vertexs, MAX);

	pi[0] = 0;
	waga[0] = 0;

	for (short i = 0; i<vertexs; i++)
		kopiec2.insert(i);

	while (kopiec2.empty() == false)
	{
		short min = *(kopiec2.begin());
		kopiec2.erase(kopiec2.begin());
		visited[min] = true;

		for (int i = 0; i<vertexs; i++)
		if (min != i && (*matrix(min, i) != 0))
		if (visited[i] == false)
		if ((*matrix(min, i) + waga[min]) < waga[i])	{
			kopiec2.erase(kopiec2.find(i));
			waga[i] = *matrix(min, i) + waga[min];
			kopiec2.insert(i);
			pi[i] = min;
		}
	}

	return pi;

}

int GrafMacierz::FordBellman(int iloscKr) {
	vector<int>D;
	vector< vector<int> > E;

	int iloscK = iloscKr * 2;
	const int MAX_INT = 1000;
	int s = 1;

	E.resize(iloscK);

	int i = 0;
	for (int x = 0; x<vertexs; x++)
	{
		for (int y = 0; y<vertexs; y++)
		{
			if (x != y)
			if (*matrix(x, y) != 0)
			{
				E[i].reserve(3);
				E[i][0] = y + 1;
				E[i][1] = x + 1;
				E[i][2] = *matrix(x, y);
				i++;
			}

		}
	}

	D.resize(vertexs);

	for (int i = 1; i < vertexs; i++) D[i] = MAX_INT; //D jest tablicą, w której trzymamy "koszt" dotarcia do danego wierzchołka z wierzchołka s. Na początku zakładamy, że dotarcie do reszty wierzchołków jest bardzo drogie
	D[s] = 0; //ale do wierzchołka s możemy dostać się za darmo
	for (int i = 1; i <= vertexs; i++)
	{
		for (int j = 0; j < iloscK; j++)
		{
			int a = E[j][0], b = E[j][1], c = E[j][2];
			if (D[a] != MAX_INT && D[a] < D[b] - c) //jeżeli koszt dotarcia do poprzedniego wierzchołka (+7) jest mniejszy niż koszt dostanie się do aktualnego wierzchołka
			{
				D[b] = D[a] + c; //to zamieniamy wartości. Należy pamiętać, aby do wartości z wierzchołka poprzedzającego dodać koszt przejścia po krawędzi do aktualnego wierzchołka

				if (i == vertexs) // jeżeli i dojdzie do n i wejdzie do tej pętli znaczy, że odkryliśmy cykl o ujemnej wadze
				{
					printf("NIE"); //więc program powinien na so tym poinformować i skończyć swoje działanie
					return 0;
				}
			}
		}
	}

	return 0;
}