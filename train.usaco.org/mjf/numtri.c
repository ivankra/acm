/*
ID: mjf28791
PROG: numtri
LANG: C
*/
#include <stdio.h>
#include <string.h>

int main()
{
	int s[1024], a[1024], r, i, j;

	freopen("numtri.in", "r", stdin);
	freopen("numtri.out", "w", stdout);

	scanf("%d", &r);
	memset(s, '\0', sizeof(s));

	for (i = 0; i < r; i++) {
		for (j = 0; j <= i; j++)
			scanf("%d", &a[j]);

		for (j = i; j > 0; j--)
			s[j] = ((s[j] > s[j - 1]) ? s[j] : s[j - 1]) + a[j];
		s[0] += a[0];
	}

	for (j = s[0], i = 1; i < r; i++)
		if (s[i] > j) j = s[i];

	printf("%d\n", j);	

	return 0;
}
