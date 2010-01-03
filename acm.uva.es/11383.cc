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
#define foreach(it, v) for (typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

#define MAXN 512

int a[MAXN][MAXN], lx[MAXN], ly[MAXN], N;
int mx[MAXN], my[MAXN], px[MAXN], py[MAXN], stk[MAXN];

void kuhnMunkres()
{
	for (int i = 0; i < N; i++) {
		lx[i] = a[i][0];
		for (int j = 0; j < N; j++)
			if (a[i][j] > lx[i]) lx[i] = a[i][j];
		ly[i] = 0;
		mx[i] = my[i] = -1;
	}

	for (int size = 0; size < N;) {
		int s, t = -1, m = 0;
		for (s = 0; mx[s] != -1; s++);

		stk[m++] = s;
		for (int i = 0; i < N; i++) px[i] = py[i] = -1;
		px[s] = s;

		while (m > 0) {
			int x = stk[--m];
			for (int y = 0; y < N; y++) {
				if (lx[x] + ly[y] == a[x][y] && py[y] == -1) {
					py[y] = x;
					if (my[y] == -1) {
						t = y;
						m = 0;
						break;
					}

					px[my[y]] = y;
					stk[m++] = my[y];
				}
			}
		}

		if (t != -1) {
			for (;;) {
				int x = py[t];
				mx[x] = t;
				my[t] = x;
				if (x == s) break;
				t = px[x];
			}
			size++;
		} else {
			int delta;
			bool flag = true;
			for (int x = 0; x < N; x++) {
				if (px[x] == -1) continue;
				for (int y = 0; y < N; y++) {
					if (py[y] != -1) continue;
					if (flag || lx[x] + ly[y] - a[x][y] < delta) {
						flag = false;
						delta = lx[x] + ly[y] - a[x][y];
					}
				}
			}

			for (int i = 0; i < N; i++) {
				if (px[i] != -1) lx[i] -= delta;
				if (py[i] != -1) ly[i] += delta;
			}
		}
	}

	int s = 0;
	for (int i = 0; i < N; i++) {
		printf(i == 0 ? "%d" : " %d", lx[i]);
		s += lx[i];
	}
	printf("\n");
	for (int i = 0; i < N; i++) {
		printf(i == 0 ? "%d" : " %d", ly[i]);
		s += ly[i];
	}
	printf("\n");
	printf("%d\n", s);
}

int main()
{
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &a[i][j]);
		kuhnMunkres();
	}
}
