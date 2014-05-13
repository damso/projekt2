// projekt2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "GrafMacierz.h"
#include "GrafLista.h"
#include <fstream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

//inicjalizacja licznika
double PCFreq = 0.0;
__int64 CounterStart = 0;
int c;
LARGE_INTEGER performanceCountStart, performanceCountEnd;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}


double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

//koniec licznika
vector<int> liczby;
int buduj_graf(){
	
	int ilosc, i = 0;
	fstream plik;
	plik.open("1.txt", std::ios::in | std::ios::out);

	if (plik.good() == true){
		while (!plik.eof()){
			plik>>ilosc;
			liczby.push_back(ilosc);
		}
		plik.close();
		return 0;
	}
	else return -1;
}

void wektor(){
	for (int i = 0; i < liczby.size(); i++){
		cout << liczby[i] << endl;
	}

}

int losuj(short **tab, int wierzcholki, float gestosc){
	int edges = (int)(gestosc*wierzcholki*(wierzcholki - 1) / 2);
	int edgesTemp = edges;

	for (int i = 1; i<wierzcholki; i++) {
		for (int h = 0; h<i; h++) {
			tab[i][h] = 0;
		}
	}

	vector<short> vecHelp;
	vecHelp.push_back(0);
	while (edges>0) {
		short x = vecHelp[rand() % (vecHelp.size())];
		short y = rand() % wierzcholki;

		short tempY = y;
		if (x<y) {
			short temp = x;
			x = y;
			y = temp;
		}

		if (x != y && tab[x][y] == 0) {
			tab[x][y] = rand() % 10 + 1;;
			vecHelp.push_back(tempY);
			edges--;
		}
	}
	return edgesTemp;
}

void menuGlowne();
void menuMacierz();
void menuLista();

void menuGlowne(){
	int wybor;
	system("cls");
	cout << "******* MENU GLOWNE *******" << endl
		<< "----------------------------" << endl
		<< "1. Reprezentacja macierzowa" << endl
		<< "2. Reprezantacja listowa" << endl
		<< "0. Zakoncz" << endl
		<< "----------------------------" << endl;

	wybor = _getch();
	switch (wybor){
	case '1':
		menuMacierz();
	case '2':
		menuLista();
	case '0':
		exit(0);
	default:
		menuGlowne();
	}
}
GrafMacierz A;
int krawedzie;
int wierzcholki = 10;
float gestosc = 0.3;
short **tab = new short*[wierzcholki];

void menuMacierz(){
	for (int i = 1; i < wierzcholki; i++)
		tab[i] = new short[i];
	int wybor;
	system("cls");
	cout << "******* MENU REPREZENTACJI MACIERZOWEJ *******\n"
		<< "-----------------------------------------------\n"
		<< "1. Wczytaj z pliku\n"
		<< "2. Wygeneruj graf losowo\n"
		<< "3. Wyswietl graf\n"
		<< "4. Algorytm Prima\n"
		<< "5. Algorytm Kruskala\n"
		<< "6. Algorytm Dijkstry\n"
		<< "7. Algorytm Forda-Bellmana\n"
		<< "****************************\n"
		<< "8. Powrot do menu glownego\n"
		<< "0. Zakoncz\n"
		<< "-----------------------------------------------\n";

	wybor = _getch();
	switch (wybor){
	case '1':
		buduj_graf();
		wektor();
		menuMacierz();
		//tutaj jaka funkcja, ktora wczyta graf z pliku
		//wczytywanie pliku nie skonczone :(
	case '2':
		//generowanie losowe
		krawedzie = losuj(tab, wierzcholki, gestosc);
		A.wpiszGraf(tab, wierzcholki);
		menuMacierz();
	case '3':
		//wyswietlenie grafu
		A.wypiszGraf();
		system("pause");
		menuMacierz();
	case '4':
		//prim
		A.Prim();
		system("pause");
		menuMacierz();
	case '5':
		//kruskal
		A.Kruskal();
		system("pause");
		menuMacierz();
	case '6':
		//dijsktra
		A.Dijkstry();
		system("pause");
		menuMacierz();
	case '7':
		//ford-bellman
		//A.FordBellman(krawedzie);
		menuMacierz();
	case '8':
		menuGlowne();
	case '0':
		exit(0);
	default:
		menuMacierz();
	}
}

GrafLista B;
void menuLista() {
	for (int i = 1; i < wierzcholki; i++)
		tab[i] = new short[i];
	int wybor;
	system("cls");
	cout << "******* MENU REPREZENTACJI LISTOWEJ *******\n"
		<< "-----------------------------------------------\n"
		<< "1. Wczytaj z pliku\n"
		<< "2. Wygeneruj graf losowo\n"
		<< "3. Wyswietl graf\n"
		<< "4. Algorytm Prima\n"
		<< "5. Algorytm Kruskala\n"
		<< "6. Algorytm Dijkstry\n"
		<< "7. Algorytm Forda-Bellmana\n"
		<< "****************************\n"
		<< "8. Powrot do menu glownego\n"
		<< "0. Zakoncz\n"
		<< "-----------------------------------------------\n";

	wybor = _getch();
	switch (wybor) {
	case '1':
		buduj_graf();
		wektor();
		menuMacierz();
		//tutaj jaka funkcja, ktora wczyta graf z pliku
		//wczytywanie pliku nie skonczone :(
		//tutaj jaka funkcja, ktora wczyta graf z pliku
	case '2':
		//generowanie losowe
		krawedzie = losuj(tab, wierzcholki, gestosc);
		B.wpiszGraf(tab, wierzcholki);
		menuLista();
	case '3':
		//wyswietlenie grafu
		B.wypiszGraf();
		system("pause");
		menuLista();
	case '4':
		//prim
		B.Prim();
		system("pause");
		menuLista();
	case '5':
		//kruskal
		B.Kruskal();
		system("pause");
		menuLista();
	case '6':
		//dijsktra
		B.Dijkstry();
		system("pause");
		menuLista();
	case '7':
		//ford-bellman
		B.FordBellman();
		system("pause");
		menuLista();
	case '8':
		menuGlowne();
	case '0':
		exit(0);
	default:
		menuLista();
	}
}

int main(int argc, char * const argv[]) {

	menuGlowne();
	return 0;
}

