#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

const int MAXN = 1024;

int x[MAXN], y[MAXN], N;
bool tagged[MAXN];

int d(int i, int j) {
	return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &x[i], &y[i]);
		tagged[i] = false;
	}

	int pos = 0, left = N;
	for (;;) {
		if (!tagged[pos]) {
			if (left == 1) break;

			int best = 0, bestd = 1<<30;
			for (int cow = 0; cow < N; cow++) {
				if (cow != pos && !tagged[cow] && d(pos, cow) < bestd) {
					best = cow;
					bestd = d(pos, cow);
				}
			}
			tagged[best] = true;
			left--;
		}

		if (++pos == N) pos = 0;
	}

	printf("%d\n", pos+1);
}
