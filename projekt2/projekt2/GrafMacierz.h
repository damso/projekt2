#include <vector>
using namespace std;

class GrafMacierz{
	short **macierz;
	int wierzcholki;
	short* matrix(int x, int y);
	short Find(short a, short *tab);
	bool Union(short a, short b, short *tab, short *liczebnosc);
public:
	void wpiszGraf(short **inputTab, int size);
	void wypiszGraf();
	int Prim();
	int Kruskal();
	vector<short> Dijkstry();
	int FordBellman(int iloscKrawedzi);
};
