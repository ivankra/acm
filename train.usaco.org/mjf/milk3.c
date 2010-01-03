/*
ID: mjf28791
PROG: milk3
LANG: C
*/
#include <stdio.h>
#include <string.h>

int cap[3], result[32];
unsigned done[1024];

int min(int a, int b)
{
	return (a < b) ? a : b;
}

void search(int a[])
{
	int i, j, k, b[3];

	if (a[0] == 0)
		result[a[2]] = 1;

	for (j = 0, i = 0; i < 3; i++)
		j = j * (cap[i] + 1) + a[i];

	if ((done[j >> 5] >> (j & 31)) & 1) return;
	done[j >> 5] |= 1U << (j & 31);

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (i == j) continue;

			memcpy(b, a, 3 * sizeof(int));

			k = min(b[i], cap[j] - b[j]);
			b[i] -= k;
			b[j] += k;

			search(b);
		}
	}
}

int main()
{
	int a[3], i;

	freopen("milk3.in", "r", stdin);
	freopen("milk3.out", "w", stdout);

	scanf("%d %d %d", &cap[0], &cap[1], &cap[2]);

	memset(result, 0, sizeof(result));
	memset(done, 0, sizeof(done));

	memset(a, 0, sizeof(a));
	a[2] = cap[2];

	search(a);

	for (i = 0; i < cap[2]; i++)
		if (result[i]) printf("%d ", i);
	printf("%d\n", cap[2]);

	return 0;
}
