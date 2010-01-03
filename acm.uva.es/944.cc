#include <cstdio>
#define INF 0x1000000

int f[100100], g[100100];

void gen(int n) {
	if (g[n] == 0) {
		g[n] = INF;
		gen(f[n]);
		if (g[f[n]] < INF)
			g[n] = 1 + g[f[n]];
	}
}

int main()
{
	f[0] = 0;
	for (int i = 0; i <= 10001; i++) {
		for (int j = 0; j <= 9; j++) {
			f[i*10+j] = f[i] + j*j;
		}
	}

	g[0] = INF;
	g[1] = 1;
	for (int i = 2; i <= 500; i++) gen(i);
	for (int i = 501; i <= 100005; i++) g[i] = 1 + g[f[i]];

	for (int i = 100005, j = 100005; i >= 0; i--) {
		if (g[i] < INF) j = i;
		f[i] = j;
	}

	int a, b;
	for (int cs = 1; scanf("%d %d", &a, &b) == 2; cs++) {
		if (cs != 1) printf("\n");
		for (a = f[a]; a <= b; a = f[a+1])
			printf("%d %d\n", a, g[a]);
	}

	return 0;
}
