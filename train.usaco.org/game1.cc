/*
ID: infnty1
PROB: game1
LANG: C++
*/
#include <stdio.h>

int main()
{
	int a[128], s[128], f[128][128], i, j, n;

	freopen("game1.in", "r", stdin);
	freopen("game1.out", "w", stdout);

	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%d", &a[i]);
	for (s[0] = 0, i = 0; i < n; i++) s[i+1] = s[i] + a[i];

	for (i = 0; i < n; i++) f[1][i] = a[i];
	for (i = 2; i <= n; i++)
		for (j = 0; i+j <= n; j++)
			f[i][j] = s[j+i] - s[j] - (f[i-1][j] <? f[i-1][j+1]);

	printf("%d %d\n", f[n][0], s[n]-f[n][0]);
	return 0;
}
