/*
ID: infnty1
PROB: stall4
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int s[256], a[256][256], b[256], seen[256], n, m;

int aug(int x) {
	if (seen[x]++) return 0;
	for (int i = 0; i < s[x]; i++) {
		int y = a[x][i];
		if (b[y] < 0 || aug(b[y])) {
			b[y] = x;
			return 1;
		}
	}
	return 0;
}

int main()
{
	freopen("stall4.in", "r", stdin);
	freopen("stall4.out", "w", stdout);

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &s[i]);
		for (int j = 0; j < s[i]; j++)
			scanf("%d", &a[i][j]);
	}

	int ret = 0;
	memset(b, 0xff, sizeof(b));
	for (int i = 0; i < n; i++) {
		memset(seen, 0, sizeof(seen));
		ret += aug(i);
	}
	printf("%d\n", ret);

	return 0;
}

