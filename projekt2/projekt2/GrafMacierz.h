#include <vector>
using namespace std;

class GrafMacierz{
	short **macierz;
	int vertexs;

	short* matrix(int x, int y);

	//Union-Find
	short Find(short a, short *tab);
	bool Union(short a, short b, short *tab, short *liczebnosc);
public:
	//GrafMacierz(int vertexs);
	//~GrafMacierz();

	void wpiszGraf(short **inputTab, int size);
	void wypiszGraf();

	int Prim();
	int Kruskal();
	vector<short> Dijkstry();
	int FordBellman(int iloscK);
};
