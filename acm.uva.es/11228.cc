#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int N, thresh, px[2000], py[2000];

struct Edge {
	short i, j;

	int len() const {
		return (px[i]-px[j])*(px[i]-px[j]) + (py[i]-py[j])*(py[i]-py[j]);
	}

	bool operator <(const Edge &other) const {
		return len() < other.len();
	}
};

Edge E[600000];
int EN;

int uf[2000];

int f(int x) {
	if (uf[x] != x) uf[x] = f(uf[x]);
	return uf[x];
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &thresh);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &px[i], &py[i]);

		EN = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				E[EN].i = i;
				E[EN].j = j;
				EN++;
			}
		}
		sort(E, E+EN);

		for (int i = 0; i < N; i++) uf[i] = i;

		int output1 = -1;
		double output2 = 0, output3 = 0;

		int ncc = N;

		for (int i = 0; i < EN; i++) {
			if (E[i].len() > thresh*thresh && output1 < 0) {
				output1 = ncc;
			}

			int x = f(E[i].i);
			int y = f(E[i].j);
			if (x == y) continue;

			if (rand() % 2 == 0) swap(x, y);
			uf[x] = y;
			ncc--;

			double len = sqrt(0.0 + E[i].len());
			if (output1 < 0)
				output2 += len;
			else
				output3 += len;
		}

		if (output1 < 0) output1 = 1;

		printf("Case #%d: %d %.0f %.0f\n", cs, output1, output2, output3);
	}
}
