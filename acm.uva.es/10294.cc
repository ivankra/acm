// Polya-Burnside counting
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
using namespace std;
typedef vector<int> VI;

long long doit(int N, int C, bool canFlip)
{
	VI p(N);

	set<VI> G;
	for (int f = 0; f < 2; f++) {
		for (int s = 0; s < N; s++) {
			for (int i = 0; i < N; i++)
				p[i] = (i + s) % N;
			if (f == 1)
				reverse(p.begin(), p.end());
			G.insert(p);
		}
		if (!canFlip) break;
	}

	long long res = 0;
	for (set<VI>::iterator it = G.begin(); it != G.end(); ++it) {
		p = *it;
		long long t = 1;
		for (int i = 0; i < N; i++) {
			if (p[i] < 0) continue;
			for (int x = p[i]; p[x] != -1;) {
				int y = p[x];
				p[x] = -1;
				x = y;
			}
			t *= C;
		}
		res += t;
	}
	return res / G.size();
}

int main()
{
	int N, C;
	while (cin >> N >> C) {
		cout << doit(N, C, false) << ' ' << doit(N, C, true) << '\n';
	}
}
