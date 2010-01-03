/*
ID: infnty1
PROB: clocks
LANG: C++
*/
#include <stdio.h>
#include <string.h>

char *moves[] = {
	"", "ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI",
	"DEGH", "GHI", "EFHI"
};

int apply(int s, char *m)
{
	int i, a[9];

	for (i = 0; i < 9; i++)
		a[i] = (s >> (2 * i)) & 3;

	while (*m) {
		i = *m++ - 'A';
		a[i] = (a[i] + 1) & 3;
	}

	for (s = i = 0; i < 9; i++)
		s |= a[i] << (2 * i);

	return s;
}

int seen[262144], q[262144+1024], prev[262144], prevmove[262144];

int main()
{
	int i, h, t, x;

	freopen("clocks.in", "r", stdin);
	freopen("clocks.out", "w", stdout);

	memset(seen, 0, sizeof(seen));

	q[0] = 0;
	for (i = 0; i < 9; i++) {
		scanf("%d", &x);
		q[0] |= ((x / 3) % 4) << (2 * i);
	}
	seen[q[0]] = 1;
	prevmove[q[0]] = 1;
	prev[q[0]] = -1;

	for (h = 0, t = 1; h < t && !seen[0]; h++) {
		for (i = prevmove[q[h]]; i <= 9; i++) {
			x = apply(q[h], moves[i]);
			if (seen[x]) continue;
			seen[x] = 1;
			q[t++] = x;
			prev[x] = q[h];
			prevmove[x] = i;
		}
	}

	for (i = t = 0; prev[i] >= 0; i = prev[i])
		q[t++] = prevmove[i];

	while (t-- > 0)
		printf(t ? "%d " : "%d", q[t]);
	printf("\n");

	return 0;
}
