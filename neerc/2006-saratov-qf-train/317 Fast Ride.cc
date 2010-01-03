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

struct Horse {
	int v, d;

	bool operator <(const Horse &other) const {
		return d < other.d;
	}
};

struct Stable {
	int x, m;
	Horse *h;

	double tm;
	int ok;

	bool operator <(const Stable &other) const {
		return x < other.x;
	}
} S[5010];

int B, N;

int main()
{
	scanf("%d %d", &B, &N);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &S[i].x, &S[i].m);

		if (S[i].x < 0 || S[i].x > B || S[i].m <= 0) {
			for (int j = 0; j < S[i].m; j++)
				scanf("%*d %*d");
			i--;
			N--;
			continue;
		}

		S[i].h = new Horse[S[i].m+1];
		for (int j = 0; j < S[i].m; j++)
			scanf("%d %d", &S[i].h[j].v, &S[i].h[j].d);

		sort(S[i].h, S[i].h+S[i].m);
		for (int j = S[i].m-2; j >= 0; j--)
			S[i].h[j].v = max(S[i].h[j].v, S[i].h[j+1].v);
	}

	sort(S, S+N);
	S[N].x = B;
	S[N].tm = 0;
	S[N].ok = 1;

	for (int i = N-1; i >= 0; i--) {
		S[i].ok = 0;
		S[i].tm = 1e99;

		if (S[i+1].x == S[i].x) {
			S[i].ok = S[i+1].ok;
			S[i].tm = S[i+1].tm;
		}

		for (int j = i+1, k = 0; j <= N; j++) {
			while (k < S[i].m && S[i].h[k].d < S[j].x-S[i].x) k++;
			if (k >= S[i].m) break;

			if (S[j].ok == 0) continue;

			double t1 = (S[j].x - S[i].x) / (double)S[i].h[k].v + S[j].tm;
			if (S[i].ok == 0 || t1 < S[i].tm) {
				S[i].ok = 1;
				S[i].tm = t1;
			}
		}
	}

	if (!S[0].ok) {
		printf("-1\n");
	} else {
		printf("%.8f\n", S[0].tm);
	}


}
