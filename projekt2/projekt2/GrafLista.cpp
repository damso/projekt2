#include "stdafx.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "GrafLista.h"

using namespace std;

vector<short> weight;


//struktura porownujaca wagi. Jezeli waga jest wieksza zwraca false
struct cmp2
{
	bool operator() (const short &a, const short &b)
	{
		if (weight[a] < weight[b]) return true;
		if (weight[a] > weight[b]) return false;
		return a<b;
	}
};

//metoda potrzebna do implementacji algorytmu Forda
void GrafLista::ff(int k, int *wynik, bool *change)
{
	short max = 32767;
	//int i;
	for (size_t i = 0; i < lista[k].size(); ++i)
	{
		if (lista[k][i].second != 0)
		if ((lista[k][i].second + wynik[k] < max) & (wynik[k] + lista[k][i].second < wynik[lista[k][i].first]))
		{
			wynik[lista[k][i].first] = wynik[k] + lista[k][i].second; change[lista[k][i].first] = true;
		}
	}
}

//rekurencyjna metoda szukajaca. Zwraca reprezentanta zbioru
short GrafLista::Find(short a, short *tab) {
	if (tab[a] == a) return a; 
	short fa = Find(tab[a], tab);
	tab[a] = fa;
	return fa;
}

//metoda na potrzebny algorytmu Kruskala. ��czy dwa zbiory. Union-Find-Problem
bool GrafLista::Union(short a, short b, short *tab, short *liczebnosc) {
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

//metoda wpisujaca graf do Listy
void GrafLista::wpiszGraf(short **inputTab, int size) {
	lista.resize(size);
	for (int x = 1; x<size; x++)
	for (int y = 0; y<x; y++) {
		if (inputTab[x][y] != 0) {
			lista[x].push_back(make_pair(y, inputTab[x][y]));
			lista[y].push_back(make_pair(x, inputTab[x][y]));
		}
	}
	//wypiszGraf();
}

void GrafLista::wypiszGraf() {
	for (size_t x = 0; x<lista.size(); x++)
	for (size_t y = 0; y<lista[x].size(); y++)
		printf("%d -- %d Waga: %d\n", x + 1, lista[x][y].first + 1, lista[x][y].second);
}

//algorytm Prima
int GrafLista::Prim() {
	set<short, cmp2> kopiecLista;
	vector<short> pi(lista.size());
	vector<bool> visited(lista.size(), false);

	short MAX = 32767;
	weight.resize(lista.size(), MAX);

	pi[0] = 0;
	weight[0] = 0;

	for (size_t i = 0; i<lista.size(); i++)
		kopiecLista.insert(i);

	int suma = 0;
	while (kopiecLista.empty() == false)
	{
		short min = *(kopiecLista.begin());
		suma += weight[min];
		kopiecLista.erase(kopiecLista.begin());
		visited[min] = true;

		for (size_t i = 0; i<lista[min].size(); i++)
		if (visited[lista[min][i].first] == false)
		if (lista[min][i].second < weight[lista[min][i].first]) {
			kopiecLista.erase(kopiecLista.find(lista[min][i].first));
			weight[lista[min][i].first] = lista[min][i].second;
			kopiecLista.insert(lista[min][i].first);
			pi[lista[min][i].first] = min;
		}

	}
	printf("Koszt minimalnego drzewa spinajacego wynosi %d\n", suma);
	printf("Drzewo zlozone jest z nastepujacych krawedzi:\n");
	for (int i = 1; i<pi.size(); i++)
		printf("%d -- %d\n", i + 1, pi[i] + 1);
	return suma;
}

//algorytm Kruskala
int GrafLista::Kruskal() {
	vector< pair< short, pair<short, short> > >krawedzie;
	for (size_t x = 0; x<lista.size(); x++)
	for (size_t y = 0; y<lista[x].size(); y++) {
		krawedzie.push_back(make_pair(lista[x][y].second, make_pair(x, lista[x][y].first)));
	}

	sort(krawedzie.begin(), krawedzie.end());

	vector< pair<short, short> > MST;

	short *helpVec = new short[lista.size()];
	short *liczebnosc = new short[lista.size()];

	for (size_t i = 0; i<lista.size(); i++) {
		helpVec[i] = i;
		liczebnosc[i] = 1;
	}

	vector< pair<short, pair<short, short> > >::iterator it = krawedzie.begin(); //iterator do poruszania sie po krawedziach

	size_t licznik = 0, suma = 0;
	while (licznik<lista.size() - 1) {
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


//Algorytm Dijkstry
vector<short> GrafLista::Dijkstry() {

	set<short, cmp2> kopiecLista;
	vector<short> pi(lista.size());
	vector<bool> visited(lista.size(), false);

	short MAX = 32767;
	weight.resize(lista.size(), MAX);

	pi[0] = 0;
	weight[0] = 0;

	for (size_t i = 0; i<lista.size(); i++)
		kopiecLista.insert(i);

	int suma = 0;
	while (kopiecLista.empty() == false)
	{
		short min = *(kopiecLista.begin());
		suma += weight[min];
		kopiecLista.erase(kopiecLista.begin());
		visited[min] = true;

		for (size_t i = 0; i<lista[min].size(); i++)
		if (visited[lista[min][i].first] == false)
		if ((lista[min][i].second + weight[min]) < weight[lista[min][i].first]) {
			kopiecLista.erase(kopiecLista.find(lista[min][i].first));
			weight[lista[min][i].first] = weight[min] + lista[min][i].second;
			kopiecLista.insert(lista[min][i].first);
			pi[lista[min][i].first] = min;
		}

	}
	for (int i = 1; i<pi.size(); i++)
		printf("%d -- %d Waga: %d\n", i + 1, pi[i] + 1, weight[i]);
	return pi;
}

//Algorytm Bellmana
void GrafLista::FordBellman() {
	short max = 32767;
	int rozmiarListy, *wynik;
	bool *zmiana, koniec = true;
	rozmiarListy = lista.size();
	wynik = new int[rozmiarListy];
	zmiana = new bool[rozmiarListy];
	wynik[0] = 0;
	for (size_t i = 1; i < lista.size(); ++i)
	{
		wynik[i] = max; zmiana[i] = false;
	}
	ff(0, wynik, zmiana);
	while (koniec == false)
	{
		koniec = true;
		for (int k = 0; k < rozmiarListy; ++k)
		if (zmiana[k] == true)
		{
			ff(k, wynik, zmiana); 
			zmiana[k] = false; 
			koniec = false;
		}
	}
	delete[]wynik; 
	delete[]zmiana;
}