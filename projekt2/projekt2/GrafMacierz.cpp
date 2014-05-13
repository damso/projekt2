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

//wpisywanie i wyswietlanie grafu
void GrafMacierz::wpiszGraf(short **inputTab, int size) {
	wierzcholki = size;
	macierz = new short*[wierzcholki];
	for (int i = 1; i < wierzcholki; i++)
		macierz[i] = new short[i];

	for (int x = 1; x < wierzcholki; x++)
	for (int y = 0; y < x; y++)
		*(matrix(x, y)) = inputTab[x][y];
}

void GrafMacierz::wypiszGraf() {
	for (int x = 1; x < wierzcholki; x++){
		for (int y = 0; y < x; y++)
			std::cout << macierz[x][y] << " ";
		cout << endl;
	}
}

//zaimplementowane algorytmy
int GrafMacierz::Prim() {
	set<short, cmp> kopiecMacierz;
	vector<short> pi(wierzcholki);
	vector<bool> odwiedzone(wierzcholki, false);

	short MAX = 32767;
	waga.resize(wierzcholki, MAX);

	pi[0] = 0;
	waga[0] = 0;

	for (short i = 0; i < wierzcholki; i++)
		kopiecMacierz.insert(i);

	int suma = 0;
	while (kopiecMacierz.empty() == false)
	{
		short min = *(kopiecMacierz.begin());
		suma += waga[min];
		kopiecMacierz.erase(kopiecMacierz.begin());
		odwiedzone[min] = true;

		for (int i = 0; i < wierzcholki; i++)
		if (min != i && (*matrix(min, i) != 0))
		if (odwiedzone[i] == false)
		if (*matrix(min, i) < waga[i])	{
			kopiecMacierz.erase(kopiecMacierz.find(i));
			waga[i] = *matrix(min, i);
			kopiecMacierz.insert(i);
			pi[i] = min;
		}
	}
	printf("Koszt minimalnego drzewa spinajacego wynosi %d\n", suma);
	printf("Drzewo zlozone jest z nastepujacych krawedzi:\n");
	for (int i = 1; i<pi.size(); i++)
		printf("%d -- %d\n", i + 1, pi[i] + 1);
	return suma;
}

int GrafMacierz::Kruskal() {
	vector< pair< short, pair<short, short> > > krawedzie;
	for (int x = 1; x<wierzcholki; x++)
	for (int y = 0; y<x; y++)
	if (*(matrix(x, y)) != 0)
		krawedzie.push_back(make_pair(*matrix(x, y), make_pair(x, y)));

	sort(krawedzie.begin(), krawedzie.end());

	vector< pair<short, short> > MST;

	short *helpVec = new short[wierzcholki];
	short *liczebnosc = new short[wierzcholki];

	for (int i = 0; i<wierzcholki; i++) {
		helpVec[i] = i;
		liczebnosc[i] = 1;
	}

	vector< pair<short, pair<short, short> > >::iterator it = krawedzie.begin();

	int licznik = 0, suma = 0;
	while (licznik<wierzcholki - 1) {
		if (Union((*it).second.first, (*it).second.second, helpVec, liczebnosc) == true) {
			MST.push_back(make_pair((*it).second.first, (*it).second.second));
			licznik++;
			suma += (*it).first;
		}
		it++;
	}
	printf("Koszt minimalnego drzewa spinajacego wynosi %d\n", suma);
	return suma;
}

vector<short> GrafMacierz::Dijkstry() {
	set<int, cmp> kopiecMacierz;
	vector<short> pi(wierzcholki);
	vector<bool> visited(wierzcholki, false);

	short MAX = 32767;
	waga.resize(wierzcholki, MAX);

	pi[0] = 0;
	waga[0] = 0;

	for (short i = 0; i<wierzcholki; i++)
		kopiecMacierz.insert(i);

	while (kopiecMacierz.empty() == false)
	{
		short min = *(kopiecMacierz.begin());
		kopiecMacierz.erase(kopiecMacierz.begin());
		visited[min] = true;

		for (int i = 0; i<wierzcholki; i++)
		if (min != i && (*matrix(min, i) != 0))
		if (visited[i] == false)
		if ((*matrix(min, i) + waga[min]) < waga[i])	{
			kopiecMacierz.erase(kopiecMacierz.find(i));
			waga[i] = *matrix(min, i) + waga[min];
			kopiecMacierz.insert(i);
			pi[i] = min;
		}
	}
	for (int i = 1; i<pi.size(); i++)
		printf("%d -- %d Waga: %d\n", i + 1, pi[i] + 1, waga[i]);
	return pi;

}

int GrafMacierz::FordBellman(int _iloscKrawedzi) {
	vector<int>D;
	vector< vector<int> > E;

	int iloscKrawedzi = _iloscKrawedzi * 2;
	const int MAX_INT = 1000;
	int s = 1;

	E.resize(iloscKrawedzi);

	int i = 0;
	for (int x = 0; x<wierzcholki; x++)
	{
		for (int y = 0; y<wierzcholki; y++)
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

	D.resize(wierzcholki);

	for (int i = 1; i < wierzcholki; i++) D[i] = MAX_INT; //D jest tablic¹, w której trzymamy "koszt" dotarcia do danego wierzcho³ka z wierzcho³ka s. Na pocz¹tku zak³adamy, ¿e dotarcie do reszty wierzcho³ków jest bardzo drogie
	D[s] = 0; //ale do wierzcho³ka s mo¿emy dostaæ siê za darmo
	for (int i = 1; i <= wierzcholki; i++)
	{
		for (int j = 0; j < iloscKrawedzi; j++)
		{
			int a = E[j][0], b = E[j][1], c = E[j][2];
			if (D[a] != MAX_INT && D[a] < D[b] - c) //je¿eli koszt dotarcia do poprzedniego wierzcho³ka (+7) jest mniejszy ni¿ koszt dostanie siê do aktualnego wierzcho³ka
			{
				D[b] = D[a] + c; //to zamieniamy wartoœci. Nale¿y pamiêtaæ, aby do wartoœci z wierzcho³ka poprzedzaj¹cego dodaæ koszt przejœcia po krawêdzi do aktualnego wierzcho³ka

				if (i == wierzcholki) // je¿eli i dojdzie do n i wejdzie do tej pêtli znaczy, ¿e odkryliœmy cykl o ujemnej wadze
				{
					printf("NIE"); //wiêc program powinien na so tym poinformowaæ i skoñczyæ swoje dzia³anie
					return 0;
				}
			}
		}
	}

	return 0;
}