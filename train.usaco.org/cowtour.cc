/*
ID: infnty1
PROB: cowtour
LANG: C++
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int adj[160][160], n, cc[160];
double d[160][160], Far[160], Diam[160];
struct { int x, y; } p[160];

double sq(double x) { return x*x; }

double dist(int i, int j) {
	return sqrt(sq(p[i].x-p[j].x)+sq(p[i].y-p[j].y));
}

int f(int x) {
	int z;
	for (z = x; cc[z] != z; z = cc[z]);
	return cc[x] = z;
}

int main()
{
	freopen("cowtour.in", "r", stdin);
	freopen("cowtour.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d %d", &p[i].x, &p[i].y);

	for (int i = 0; i < n; i++)
		cc[i] = i;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			while ((adj[i][j] = getchar()) != EOF)
				if (adj[i][j] == '0' || adj[i][j] == '1') {
					adj[i][j] -= '0';
					if (adj[i][j]) cc[f(i)] = f(j);
					break;
				}

	for (int i = 0; i < n; i++)
		f(i);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			d[i][j] = adj[i][j] ? dist(i, j) : 1e99;
		d[i][i] = 0.;
	}

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				d[i][j] <?= d[i][k] + d[k][j];

	for (int i = 0; i < n; i++)
		Diam[i] = Far[i] = 0;

	for (int i = 0; i < n; i++) {
		Far[i] = 0;
		for (int j = 0; j < n; j++)
			if (cc[i] == cc[j]) Far[i] >?= d[i][j];
		Diam[cc[i]] >?= Far[i];
	}

	double best = 1e99;
	for (int x = 0; x < n; x++) {
		for (int y = x+1; y < n; y++) {
			if (cc[x] == cc[y]) continue;
			best <?= Diam[cc[x]] >? Diam[cc[y]] >? (Far[x]+dist(x,y)+Far[y]);
		}
	}
	printf("%.6f\n", best);

	return 0;
}
