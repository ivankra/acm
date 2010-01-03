/*
ID: infnty1
TASK: mooo
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int h[65536], v[65536], hears[65536], mm[16][65536], n;

int rmax(int a, int b) {
	int d = b - a + 1, k;
	for (k = 0; (1 << (k + 1)) <= d; k++);
	return mm[k][a] >? mm[k][b-(1<<k)+1];
}

int main()
{
	freopen("mooo.in", "r", stdin);
	freopen("mooo.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &h[i], &v[i]);
		mm[0][i] = h[i];
	}

	for (int i = 1; (1 << i) <= n; i++)
		for (int j = 0; j + i <= n; j++)
			mm[i][j] = (mm[i-1][j] >? mm[i-1][j + (1 << (i-1))]);

	memset(hears, 0, sizeof(hears));
	for (int i = 0; i < n; i++) {
		int a, b;
		for (a = 0, b = i-1; a < b;) {
			int c = (a + b + 1) >> 1;
			if (rmax(c, i-1) > h[i]) a = c; else b = c - 1;
		}
		if (a == b && h[a] > h[i]) hears[a] += v[i];

		for (a = i+1, b = n-1; a < b;) {
			int c = (a + b) >> 1;
			if (rmax(i+1, c) > h[i]) b = c; else a = c + 1;
		}
		if (a == b && h[a] > h[i]) hears[a] += v[i];
	}

	int best = 0;
	for (int i = 0; i < n; i++) best >?= hears[i];
	printf("%d\n", best);

	return 0;
}
