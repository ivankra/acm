#include <stdio.h>
#include <stdlib.h>

int a[16], sum, n;
int tup[131072][16], total;

static int cmp(int b[])
{
	int i;
	/* a[n] = -0x1FFFFFFF; */
	for (i = 0; a[i] == b[i]; i++);
	return (b[i] > a[i] && i < n) ? 1 : 0;
}

static void check()
{
	static int b[32];
	int i, j;

	for (i = 0, j = 0; i < n; i++) b[j++] = a[i];
	for (i = 0; i < n; i++) b[j++] = a[i];
	for (i = 1; i < n; i++) if (b[i] == a[0] && cmp(b + i)) return;

	for (i = 1, j = n << 1; i < j; i++) b[i] = -b[i];
	for (i = 1; i < n; i++) if (b[i] == a[0] && cmp(b + i)) return;

	for (i = n, j = 0; i--;) b[j++] = a[i];
	for (i = n; i--;) b[j++] = a[i];
	for (i = 0; i < n; i++) if (b[i] == a[0] && cmp(b + i)) return;

	for (i = 0, j = n << 1; i < j; i++) b[i] = -b[i];
	for (i = 0; i < n; i++) if (b[i] == a[0] && cmp(b + i)) return;

	for (i = 0; i < n; i++)
		tup[total][i] = a[i];
	total++;
}

static void go(int p)
{
	if (p == (n - 1)) {
		if (-a[0] <= sum && sum <= a[0]) {
			a[p] = -sum;
			check();
		}
		return;
	}

	if (abs(sum) > ((n - p) * a[0]))
		return;

	for (a[p] = -a[0]; a[p] < a[0]; a[p]++) {
		if (a[p - 1] == a[0] && a[p] > a[1]) return;
		sum += a[p];
		go(p + 1);
		sum -= a[p];
	}

	if (a[p] == a[0] && a[p - 1] <= a[1]) {
		sum += a[0];
		go(p + 1);
		sum -= a[0];
	}
}

int main()
{
	int i, k, t = 0;

	while (scanf("%d %d", &n, &k) == 2) {
		if (t++) printf("\n");

		if (n == 1) {
/*damn case*/
			printf("1\n(0)\n");
			continue;
		}

		a[n] = -0x1FFFFFFF;
		total = 0;
		for (a[0] = 0; a[0] <= k; a[0]++) {
			sum = a[0];
			go(1);
		}

		printf("%d\n", total);
		for (i = 0; i < total; i++) {
			for (k = 0; k < n; k++)
				printf(k ? ",%d" : "(%d", tup[i][k]);
			printf(")\n");
		}
	}

	return 0;
}
