// MST
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <algorithm>
using namespace std;

int S, N, u[512], x[512], y[512];

int f(int x) {
	int z = x;
	while (u[z] != z) z = u[z];
	while (x != z) { int y = u[x]; u[x] = z; x = y; }
	return z;
}

struct Edge { int x, y, d; };
bool operator <(const Edge &a, const Edge &b) { return a.d < b.d; }

Edge E[500*500/2+10];
int En;

int main()
{
	int T;
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &S, &N) == 2;) {
		assert(N <= 500);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &x[i], &y[i]);

		En = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				E[En].x = i;
				E[En].y = j;
				E[En].d = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
				En++;
			}
		}
		sort(E, E+En);

		for (int i = 0; i < N; i++) u[i] = i;

		int C = N, D = 0;
		for (int e = 0; C > S && e < En; e++) {
			D >?= E[e].d;
			int a = f(E[e].x), b = f(E[e].y);
			if (a != b) {
				C--;
				u[a] = b;
			}
		}

		printf("%.2f\n", sqrt((double)D)+1e-9);
	}
	return 0;
}
