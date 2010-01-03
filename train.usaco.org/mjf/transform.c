/*
ID: mjf28791
PROG: transform
LANG: C
*/
#include <stdio.h>
#include <string.h>

typedef int image_t[16][16];
int n;

void rot(image_t p)
{
	static image_t t;
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			t[i][j] = p[n - j - 1][i];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			p[i][j] = t[i][j];
}

void flip(image_t p)
{
	static image_t t;
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			t[i][j] = p[i][n - j - 1];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			p[i][j] = t[i][j];
}

int equal(image_t p, image_t q)
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (p[i][j] != q[i][j]) return 0;

	return 1;
}

void take(image_t p)
{
	int i, j, c;

	for (i = 0; i < n; i++)
		for (j = 0; j < n && (c = getchar()) != EOF;)
			if (c == '-' || c == '@') p[i][j++] = c;
}

int solve(image_t p, image_t q)
{
	int i;

	rot(p);
	for (i = 1; i < 4; i++, rot(p))
		if (equal(p, q)) return i;

	flip(p);
	for (i = 0; i < 4; i++, rot(p))
		if (equal(p, q)) return (i == 0) ? 4 : 5;

	flip(p);
	return (equal(p, q) ? 6 : 7);
}

int main()
{
	image_t p, q;

	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);

	scanf("%d", &n);
	take(p);
	take(q);

	printf("%d\n", solve(p, q));

	return 0;
}
