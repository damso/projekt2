// projekt2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "GrafMacierz.h"
#include "GrafLista.h"
#include <fstream>
#include <time.h>

using namespace std;

int losuj(short **tab, int vertexs, float density){
	int edges = (int)(density*vertexs*(vertexs - 1) / 2);
	int edgesTemp = edges;

	for (int i = 1; i<vertexs; i++) {
		for (int h = 0; h<i; h++) {
			tab[i][h] = 0;
		}
	}

	vector<short> vecHelp;
	vecHelp.push_back(0);
	while (edges>0) {
		short x = vecHelp[rand() % (vecHelp.size())];
		short y = rand() % vertexs;

		short tempY = y;
		if (x<y) {
			short temp = x;
			x = y;
			y = temp;
		}

		if (x != y && tab[x][y] == 0)
		{
			tab[x][y] = rand() % 10000 + 1;;
			vecHelp.push_back(tempY);
			edges--;
		}
	}
	return edgesTemp;
}

int main(int argc, char * const argv[]) {

	ofstream plik;
	plik.open("Dane.txt", ios::out);

	srand(time(0));

	int vertexs = 200;
	float gestosc = 0.5;
	const int powtorzenia = 2;
	const int maxVertexs = 3000;
	const int skok = 200;

	double czas = 0;
	clock_t start, koniec;
	GrafMacierz A;

	
	/*
	plik << "Prim Macierz - 0.9" << endl;
	while (vertexs<maxVertexs) {
	for (int i=0; i<powtorzenia; i++) {
	short **tab = new short*[vertexs];
	for (int i=1; i<vertexs; i++)
	tab[i] = new short[i];

	losuj(tab,vertexs,gestosc);
	A.wpiszGraf(tab,vertexs);
	start = clock();
	A.Prim();
	koniec = clock();

	for (int i=1; i<vertexs; i++) {
	delete [] tab[i];
	}
	delete [] tab;

	czas += ((double) (koniec - start)) / CLOCKS_PER_SEC;
	}
	czas = czas/powtorzenia;
	plik << vertexs << " " << czas << endl;;
	vertexs += skok;
	}


	/*
	czas = 0;
	vertexs = 500;

	
	plik << "Kruskal Macierz - 0.9" << endl;
	while (vertexs<maxVertexs) {
	for (int i=0; i<powtorzenia; i++) {
	short **tab = new short*[vertexs];
	for (int i=1; i<vertexs; i++)
	tab[i] = new short[i];

	losuj(tab,vertexs,gestosc);
	A.wpiszGraf(tab,vertexs);
	start = clock();
	A.Kruskal();
	koniec = clock();

	for (int i=1; i<vertexs; i++) {
	delete [] tab[i];
	}
	delete [] tab;

	czas += ((double) (koniec - start)) / CLOCKS_PER_SEC;
	}
	czas = czas/powtorzenia;
	plik << vertexs << " " << czas << endl;
	vertexs += skok;
	}

	czas = 0;
	vertexs = 500;

	plik << "Dijkstry Macierz - 0.9" << endl;
	while (vertexs<maxVertexs) {
	for (int i=0; i<powtorzenia; i++) {
	short **tab = new short*[vertexs];
	for (int i=1; i<vertexs; i++)
	tab[i] = new short[i];

	losuj(tab,vertexs,gestosc);
	A.wpiszGraf(tab,vertexs);
	start = clock();
	A.Dijkstry();
	koniec = clock();

	for (int i=1; i<vertexs; i++) {
	delete [] tab[i];
	}
	delete [] tab;

	czas += ((double) (koniec - start)) / CLOCKS_PER_SEC;
	}
	czas = czas/powtorzenia;
	plik << vertexs << " " << czas << endl;;
	vertexs += skok;
	}
	*/
	
	GrafLista B;

	/*
	plik << "Prim Lista - 0.9" << endl;
	while (vertexs<maxVertexs) {
	for (int i=0; i<powtorzenia; i++) {
	short **tab = new short*[vertexs];
	for (int i=1; i<vertexs; i++)
	tab[i] = new short[i];

	losuj(tab,vertexs,gestosc);
	B.wpiszGraf(tab,vertexs);
	start = clock();
	B.Prim();
	koniec = clock();

	for (int i=1; i<vertexs; i++) {
	delete [] tab[i];
	}
	delete [] tab;

	czas += ((double) (koniec - start)) / CLOCKS_PER_SEC;
	}
	czas = czas/powtorzenia;
	plik << vertexs << " " << czas << endl;;
	vertexs += skok;
	}

	
	czas = 0;
	vertexs = 500;
	
	plik << "Kruskal Lista - 0.9" << endl;
	while (vertexs<maxVertexs) {
	for (int i=0; i<powtorzenia; i++) {
	short **tab = new short*[vertexs];
	for (int i=1; i<vertexs; i++)
	tab[i] = new short[i];

	losuj(tab,vertexs,gestosc);
	B.wpiszGraf(tab,vertexs);
	start = clock();
	B.Kruskal();
	koniec = clock();

	for (int i=1; i<vertexs; i++) {
	delete [] tab[i];
	}
	delete [] tab;

	czas += ((double) (koniec - start)) / CLOCKS_PER_SEC;
	}
	czas = czas/powtorzenia;
	plik << vertexs << " " << czas << endl;;
	vertexs += skok;
	}
	
	/*	czas = 0;
	vertexs = 500;

	plik << "Dijkstry Lista - 0.3" << endl;
	while (vertexs<maxVertexs) {
	for (int i=0; i<powtorzenia; i++) {
	short **tab = new short*[vertexs];
	for (int i=1; i<vertexs; i++)
	tab[i] = new short[i];

	losuj(tab,vertexs,gestosc);
	B.wpiszGraf(tab,vertexs);
	start = clock();
	B.Dijkstry();
	koniec = clock();

	for (int i=1; i<vertexs; i++) {
	delete [] tab[i];
	}
	delete [] tab;

	czas += ((double) (koniec - start)) / CLOCKS_PER_SEC;
	}
	czas = czas/powtorzenia;
	plik << vertexs << " " << czas << endl;;
	vertexs += skok;
	}
	

	gestosc = 0.3;
	czas = 0;
	vertexs = 500;
	
	*/

	plik << "Ford Belmann Macierz - 0.5" << endl;
	while (vertexs<maxVertexs) {
		for (int i = 0; i<powtorzenia; i++) {
			short **tab = new short*[vertexs];
			for (int i = 1; i<vertexs; i++)
				tab[i] = new short[i];

			int krawedzie = losuj(tab, vertexs, gestosc);
			A.wpiszGraf(tab, vertexs);
			start = clock();
			A.FordBellman(krawedzie);
			koniec = clock();

			for (int i = 1; i<vertexs; i++) {
				delete[] tab[i];
			}
			delete[] tab;

			czas += ((double)(koniec - start)) / CLOCKS_PER_SEC;
		}
		czas = czas / powtorzenia;
		plik << vertexs << " " << czas << endl;;
		vertexs += skok;
	}
	
	/*
	czas = 0;
	gestosc = 0.8;
	vertexs = 500;
	plik << "Ford Belmann Macierz - 0.8" << endl;
	while (vertexs<maxVertexs) {
		for (int i = 0; i<4; i++) {
			short **tab = new short*[vertexs];
			for (int i = 1; i<vertexs; i++)
				tab[i] = new short[i];

			int krawedzie = losuj(tab, vertexs, gestosc);
			A.wpiszGraf(tab, vertexs);
			start = clock();
			A.FordBellman(krawedzie);
			koniec = clock();

			for (int i = 1; i<vertexs; i++) {
				delete[] tab[i];
			}
			delete[] tab;

			czas += ((double)(koniec - start)) / CLOCKS_PER_SEC;
		}
		czas = czas / 4;
		plik << vertexs << " " << czas << endl;;
		vertexs += skok;
	}
	*/

	plik.close();

	system("PAUSE");
	return 0;
}

