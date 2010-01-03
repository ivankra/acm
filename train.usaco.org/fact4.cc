/*
ID: infnty1
PROB: fact4
LANG: C++
*/
#include <stdio.h>

int main()
{
	freopen("fact4.in", "r", stdin);
	freopen("fact4.out", "w", stdout);

	int n;
	scanf("%d", &n);

	int r = 1, k = 0;
	for (int j = 2; j <= n; j++) {
		int i = j;
		while ((i % 2) == 0) k++, i /= 2;
		while ((i % 5) == 0) k--, i /= 5;
		r = (r * i) % 10;
	}
	while (k--) r = (r * 2) % 10;

	printf("%d\n", r);	

	return 0;
}
