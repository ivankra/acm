/*
ID: mjf28791
PROG: gift1
LANG: C
*/
#include <stdio.h>
#include <string.h>

int main()
{
	char names[16][16], s[256];
	int profit[16], i, m, n, k, r;

	freopen("gift1.in", "r", stdin);
	freopen("gift1.out", "w", stdout);

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf(" %[A-Za-z]", names[i]);

	for (i = 0; i < n; i++)
		profit[i] = 0;

	for (r = 0; r < n && scanf(" %[A-Za-z]", s) == 1; r++) {
		scanf("%d %d", &m, &k);

		if (k == 0)
			continue;

		for (i = 0; strcmp(s, names[i]) != 0; i++);

		profit[i] = profit[i] - m + (m % k);
		m /= k;

		while (k-- > 0 && scanf(" %[A-Za-z]", s) == 1) {
			for (i = 0; strcmp(s, names[i]) != 0; i++);
			profit[i] += m;
		}
	}

	for (i = 0; i < n; i++)
		printf("%s %d\n", names[i], profit[i]);

	return 0;
}
