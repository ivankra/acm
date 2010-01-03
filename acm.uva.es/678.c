#include <stdio.h>
#include <string.h>

int u[128][128];

void doplay(int a[], int b[], int q)
{
	static int list[128], k;
	int i, j;

	for (i = 0, k = 0; i < q; i++)
		list[k++] = a[i];

	for (i = 0; i < q; i++)
		list[k++] = b[i];

	for (i = 0; i < k; i++) {
		if (list[i] < 0) continue;

		for (j = 0; j < k; j++) {
			if (list[j] < 0 || u[list[i]][list[j]]) continue;
			printf(" (%d-%d)", list[i]+1, list[j]+1);
			u[list[i]][list[j]] = 1;
			u[list[j]][list[i]] = 1;
			list[i] = -1;
			list[j] = -1;
			break;
		}
	}
}

int playtest(int a[], int b[], int q)
{
	static int list[128], k;
	int i, j;

	for (i = 0, k = 0; i < q; i++)
		list[k++] = a[i];

	for (i = 0; i < q; i++)
		list[k++] = b[i];

	for (i = 0; i < k; i++)
		for (j = 0; j < k; j++)
			if (u[list[i]][list[j]] == 0) return 1;

	return 0;
}

void travel(int a[], int b[], int q, int d)
{
	int i, t;

	printf("  Teams travelling between day %d and day %d: ", d, d + 1);
	for (i = 0; i < q; i++) {
		printf("%s%d,%d", i ? "," : "", a[i]+1, b[i]+1);
		t = a[i];
		a[i] = b[i];
		b[i] = t;
	}
	printf(".\n");
}

int main()
{
	static int p[4][128];
	int i, j, k, n, q, s, t;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		q = n / 4;

		for (i = 0; i < 4; i++)
			for (j = 0; j < q; j++)
				p[i][j] = i * q + j;

		memset(u, 0, sizeof(u));
		for (i = 0; i < n; i++)
			u[i][i] = 1;

		for (k = 0, s = 0;;) {
			printf("Day %d:\n", ++k);

			printf("  Taipei:");
			doplay(p[0], p[1], q);
			printf(".\n");

			printf("  Kaohsiung:");
			doplay(p[2], p[3], q);
			printf(".\n");

			if (playtest(p[0], p[1], q)) {
				printf("  No teams travelling between day %d and day %d.\n", k, k + 1);
				continue;
			}

			if (++s > 2)
				break;

			if (s == 1)
				travel(p[1], p[2], q, k);
			else
				travel(p[1], p[3], q, k);
		}

		printf("Total number of travels: %d\n", n);

		if (t > 0)
			printf("\n");
	}

	return 0;
}
