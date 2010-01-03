#include <stdio.h>
#include <string.h>

static char x[16384], y[2048];
static int m, n;

#define NLIMBS 12

typedef unsigned long u_int32_t;
typedef unsigned long long u_int64_t;

struct num { u_int32_t d[NLIMBS]; };

static struct num tab1[256], tab2[256];
static struct num *tab, *tab_next;

static void make()
{
	register int i, j, k;
	register unsigned long long c;

	tab = tab1;
	memset(tab1, 0, sizeof(tab1));
	tab_next = tab2;

	tab[0].d[0] = 1;

	for (i = 1; i <= m; i++) {
		for (j = 0; j <= n; j++)
			for (k = 0; k < NLIMBS; k++)
				tab_next[j].d[k] = tab[j].d[k];

		for (j = 1; j <= n; j++) {
			if (x[i] != y[j])
				continue;

			for (c = 0, k = 0; k < NLIMBS; k++) {
				c += (u_int64_t)tab_next[j].d[k] +
					(u_int64_t)tab[j-1].d[k];
				tab_next[j].d[k] = (u_int32_t)c;
				c >>= 32;
			}
		}

		tab = tab_next;
		tab_next = (tab_next == tab1) ? tab2 : tab1;
	}
}

static void print(struct num *x)
{
	static char s[1024], t[1024];
	u_int64_t c;
	int i, k, r;

	for (k = 0;;) {
		for (i = NLIMBS - 1, c = 0; i >= 0; i--) {
			c = (c << 32) | (u_int64_t)x->d[i];
			x->d[i] = (u_int32_t)(c / 1000000000ULL);
			c %= 1000000000ULL;
		}

		r = (int)c;
		for (i = 0; i < 9; i++, r /= 10)
			s[k++] = (r % 10) + '0';

		for (i = 0; i < NLIMBS; i++)
			if (x->d[i] != 0) break;
		if (i >= NLIMBS) break;
	}

	for (k--; k > 0 && s[k] == '0'; k--);

	for (i = 0; k >= 0;)
		t[i++] = s[k--];
	t[i++] = '\0';

	printf("%s\n", t);
}

int main()
{
	int t;

	while (gets(x) && sscanf(x, "%d", &t) != 1);

	while (t-- > 0) {
		if (gets(x + 1) == NULL) break;
		m = strlen(x + 1);

		if (gets(y + 1) == NULL) break;
		n = strlen(y + 1);

		make();

		print(&tab[n]);
	}

	return 0;
}
