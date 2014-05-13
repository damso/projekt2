#include <vector>
using namespace std;

class GrafLista {
	vector< vector< pair<short, short> > > lista;

	//Funkcja pomocnicza do Forda
	void ff(int k, int *wynik, bool *change);

	//Na potrzebny Kruskala
	short Find(short a, short *tab);
	bool Union(short a, short b, short *tab, short *liczebnosc);
public:
	void wpiszGraf(short **inputTab, int size);
	void wypiszGraf();

	int Prim();
	int Kruskal();
	vector<short> Dijkstry();
	void FordBellman();
};

