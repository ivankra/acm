#include <stdio.h>
#include <string.h>

typedef struct {
	int p, q;
} ratio_t;

ratio_t tab[64][64];
char name[64][32];
int n;

int get(char *s)
{
	int i;

	for (i = 0; i < n && strcmp(name[i], s) != 0; i++);

	if (i < n)
		return i;

	strcpy(name[n], s);
	return n++;
}

void reduce(ratio_t *r)
{
	int x, y;

	if (r->p == 0) {
		r->q = 1;
		return;
	}

	while (((r->p | r->q) & 1) == 0) {
		r->p >>= 1;
		r->q >>= 1;
	}

	for (x = r->p, y = r->q; x != 0 && y != 0;) {
		while ((x & 1) == 0)
			x >>= 1;

		while ((y & 1) == 0)
			y >>= 1;

		if (x > y)
			x -= y;
		else
			y -= x;
	}

	x = (x != 0) ? x : y;
	r->p /= x;
	r->q /= x;
}

void update()
{
	int i, j, k;

	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			if (tab[i][k].p == 0)
				continue;

			for (j = 0; j < n; j++) {
				if (tab[i][j].p != 0 || tab[j][k].p == 0)
					continue;

				tab[i][j].p = tab[i][k].p * tab[k][j].p;
				tab[i][j].q = tab[i][k].q * tab[k][j].q;
				reduce(&tab[i][j]);
			}
		}
	}
}

int main()
{
	static char s1[256], s2[256];
	int u, c, m1, m2, x1, x2;

	memset(tab, 0, sizeof(tab));

	for (n = 0, u = 0; (c = getchar()) != EOF && c != '.';) {
		if (c == '!') {
			scanf("%d %[a-z] = %d %[a-z]", &m1, s1, &m2, s2);

			x1 = get(s1);
			x2 = get(s2);

			tab[x1][x2].p = m2;
			tab[x1][x2].q = m1;
			reduce(&tab[x1][x2]);

			tab[x2][x1].p = m1;
			tab[x2][x1].q = m2;
			reduce(&tab[x2][x1]);

			u++;
		} else if (c == '?') {
			scanf(" %[a-z] = %[a-z]", s1, s2);

			x1 = get(s1);
			x2 = get(s2);

			if (tab[x1][x2].p == 0 && u > 0) {
				update();
				u = 0;
			}

			if (tab[x1][x2].p == 0)
				printf("? %s = ? %s\n", s1, s2);
			else
				printf("%d %s = %d %s\n",
					tab[x1][x2].q, s1, tab[x1][x2].p, s2);
		}
	}

	return 0;
}
