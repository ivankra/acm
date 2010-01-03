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

struct Pos {
	int x, y;
	
	bool operator <(const Pos &other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

	bool operator ==(const Pos &other) const {
		return x == other.x && y == other.y;
	}
};

int cross(Pos o, Pos a, Pos b)
{
	return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}

int read()
{
	int a, b;
	scanf("%d . %d", &a, &b);
	return a * 100 + b;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int N;
		Pos p[200];

		scanf("%d", &N);

		for (int i = 0; i < N; i++) {
			p[i].x = read();
			p[i].y = read();
		}

		sort(p, p+N);
		N = unique(p, p+N) - p;

		int best = min(N, 2);
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				int c = 0;
				for (int k = 0; k < N; k++)
					if (cross(p[i], p[j], p[k]) == 0) c++;
				best >?= c;
			}
		}

		if (N == 1)
			printf("Data set #%d contains a single gnu.\n", cs);
		else
			printf("Data set #%d contains %d gnus, out of which a maximum of %d are aligned.\n", cs, N, best);
	}
}
