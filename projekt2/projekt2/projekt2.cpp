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

using namespace std;

int losuj(short **tab, int wierzcholki, float gestosc){
	int krawedzie = (int)(gestosc * wierzcholki * (wierzcholki - 1) / 2);
	int krawedzieTemp = krawedzie;

	for (int i = 1; i < wierzcholki; i++) {
		for (int h = 0; h<i; h++) {
			tab[i][h] = 0;
		}
	}

	vector<short> vecHelp;
	vecHelp.push_back(0);
	while (krawedzie > 0) {
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
			krawedzie--;
		}
	}
	return krawedzieTemp;
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

int krawedzie;
int wierzcholki = 5;
float gestosc = 0.3;
short **tab = new short*[wierzcholki];

GrafMacierz A;
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
		//tutaj jaka funkcja, ktora wczyta graf z pliku
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

