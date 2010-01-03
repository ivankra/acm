/*
ID: infnty1
PROB: inflate
LANG: C++
*/
#include <stdio.h>
#include <string.h>

int a[16384], n, m, p, t;

int main()
{
	freopen("inflate.in", "r", stdin);
	freopen("inflate.out", "w", stdout);

	scanf("%d %d", &m, &n);

	memset(a, 0, sizeof(a));
	while (n-- > 0 && scanf("%d %d", &p, &t) == 2)
		for (int i = t; i <= m; i++) a[i] >?= a[i-t]+p;

	printf("%d\n", a[m]);

	return 0;
}
