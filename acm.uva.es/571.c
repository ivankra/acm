#include <stdio.h>
#include <string.h>

#define MAXDEPTH 65536

int ca, cb, dest;
unsigned map[32768];

char *sol[MAXDEPTH];
int n;

int min(int a, int b)
{
	return (a < b) ? a : b;
}

int solve(int a, int b)
{
	int t;

	t = a * (cb + 1) + b;
	if ((map[t >> 5] >> (t & 31)) & 1)
		return 0;
	map[t >> 5] |= 1 << (t & 31);

	if (a == dest || b == dest)
		return 1;

	if (n > MAXDEPTH)
		return 0;

	n++;

	if (a > 0 && b < cb) {
		sol[n - 1] = "pour A B";
		t = min(a, cb - b);
		if (solve(a - t, b + t)) return 1;
	}

	if (a < ca && b > 0) {
		sol[n - 1] = "pour B A";
		t = min(ca - a, b);
		if (solve(a + t, b - t)) return 1;
	}

	if (a > 0) {
		sol[n - 1] = "empty A";
		if (solve(0, b)) return 1;
	}

	if (b > 0) {
		sol[n - 1] = "empty B";
		if (solve(a, 0)) return 1;
	}

	if (a < ca) {
		sol[n - 1] = "fill A";
		if (solve(ca, b)) return 1;
	}

	if (b < cb) {
		sol[n - 1] = "fill B";
		if (solve(a, cb)) return 1;
	}

	n--;

	return 0;
}

int main()
{
	int i;

	while (scanf("%d %d %d", &ca, &cb, &dest) == 3) {
		memset(map, 0, sizeof(map));

		n = 0;
		if (solve(0, 0) == 0) {for(;;)malloc(10000000);}

		for (i = 0; i < n; i++)
			printf("%s\n", sol[i]);
		printf("success\n");
	}

	return 0;
}
