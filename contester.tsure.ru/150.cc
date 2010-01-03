#include <cstdio>

int main()
{
	int a[128][128], n, m, op[4]={0,0,0,0};
	char c;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	while (m-- > 0 && scanf(" %c", &c) == 1)
		op[c-'A'] ^= 1;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			int r = (x <? n-1-x <? y <? n-1-y) & 1;
			a[y][x] ^= (op[0] && r==0) ^ (op[1] && r==1);
		}
	}

	for (int i = 0, j = n-1; i < n; i++, j--) {
		int k1 = (i<?j), k2 = (i>?j);
		for (int k = k1; k <= k2; k++) {
			a[i][k] ^= op[3];
			a[k][i] ^= op[2];
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			printf(j+1<n?"%d ":"%d\n", a[i][j]);
}
