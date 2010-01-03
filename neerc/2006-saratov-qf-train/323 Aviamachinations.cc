#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

int N, K;

struct Edge {
	int a, b, c, p, id;
	bool operator <(const Edge &other) const {
		return p < other.p;
	}
};

struct UF {
	int p[2048];
	void clear() { for (int i = 0; i <= N; i++) p[i] = i; }

	int f(int x) {
		int z;
		for (z = x; p[z] != z; z = p[z]);
		while (x != z) { int y = p[x]; p[x] = z; x = y; }
		return z;
	}

	bool u(int x, int y) {
		x = f(x); y = f(y);
		if (x != y) {
			if ((rand() % 2) == 0) p[x] = y; else p[y] = x;
			return true;
		} else {
			return false;
		}
	}
};

int main()
{
	srand(time(NULL));

	int M;
	scanf("%d %d %d", &N, &K, &M);

	vector<Edge> E(M);
	for (int i = 0; i < M; i++) {
		Edge &e = E[i];
		scanf("%d %d %d %d", &e.a, &e.b, &e.c, &e.p);
		e.id = i+1;
	}
	sort(E.begin(), E.end());

	vector<Edge> CE[2048];
	for (int i = 0; i < M; i++)
		CE[E[i].c].push_back(E[i]);

	vector<Edge> mst;
	static UF uf;

	uf.clear();
	for (int i = 0; i < M; i++) {
		const Edge &e = E[i];
		if (uf.u(e.a, e.b)) mst.push_back(e);
	}

	int bestP = 0x7fffffff, bestC = 0, bestQ = 0;
	vector<int> bestF;
	for (int c = 1; c <= K; c++) {
		uf.clear();
		for (int i = 0; i < (int)CE[c].size(); i++)
			uf.u(CE[c][i].a, CE[c][i].b);

		int P = 0, Q = 0;
		vector<int> F;
		for (int i = 0; i < (int)mst.size(); i++) {
			const Edge &e = mst[i];
			if (e.c == c) continue;
			if (uf.u(e.a, e.b)) { P += e.p; Q++; F.push_back(e.id); }
		}

		if (P < bestP) {
			bestP = P;
			bestC = c;
			bestQ = Q;
			bestF = F;
		}
	}

	printf("%d %d %d\n", bestP, bestC, bestQ);

	sort(bestF.begin(), bestF.end());
	for (int i = 0; i < bestQ; i++)
		printf("%d\n", bestF[i]);
}
