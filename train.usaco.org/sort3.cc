/*
ID: infnty1
PROB: sort3
LANG: C++
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a[1024], b[1024], moves[4][4], n;

int cmp(const void *p, const void *q) { return *(int *)p - *(int *)q; }

int main()
{

	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) { scanf("%d", &a[i]); b[i] = a[i]; }
	qsort(b, n, sizeof(int), &cmp);

	memset(moves, 0, sizeof(moves));
	for (int i = 0; i < n; i++)
		moves[a[i]][b[i]]++;

	int r = 0;
	for (int i = 1; i <= 3; i++) {
		for (int j = i+1; j <= 3; j++) {
			int k = (moves[i][j] <? moves[j][i]);
			r += k;
			moves[i][j] -= k;
			moves[j][i] -= k;
		}	
		moves[i][i] = 0;
	}
	r += ((moves[1][2] + moves[2][1]) * 2);

	printf("%d\n", r);

	return 0;
}
