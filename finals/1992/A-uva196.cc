#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

char *dup(const char *s) {
	char *t = (char *)malloc(strlen(s)+1);
	strcpy(t, s);
	return t;
}

struct Rec {
	char *s;
	int x;
};

Rec *tab;
int nrows, ncols;

bool readid(int &out, Rec &e) {
	while (e.s[e.x] == '+') e.x++;
	if (e.s[e.x] == 0) return 0;
	if (!('A' <= e.s[e.x] && e.s[e.x] <= 'Z')) return 0;

	int c = 0, r = 0;
	while ('A' <= e.s[e.x] && e.s[e.x] <= 'Z') {
		c = c * 26 + e.s[e.x++] - 'A';
		r++;
	}

	if (r == 2) c += 26;
	if (r == 3) c += 26 + 26*26;

	r = 0;
	while ('0' <= e.s[e.x] && e.s[e.x] <= '9')
		r = r * 10 + e.s[e.x++] - '0';
	r--;

	assert(0 <= r && r < nrows);
	assert(0 <= c && c < ncols);

        out = r * ncols + c;
        return 1;
}

int *eval_s;

void eval(int id)
{
	int *s = eval_s, n = 0, t;
	s[n++] = id;
	tab[id].x = 0;

	while (n > 0) {
		Rec &e = tab[s[n-1]];
		if (!readid(t, e)) {
			int sum = 0;
			for (e.x = 0; readid(t, e);)
				sum += tab[t].x;
			free(e.s);
			e.s = NULL;
			e.x = sum;
			n--;
			continue;
		}

		if (tab[t].s == NULL)
			continue;

		tab[t].x = 0;
		s[n++] = t;

		assert(n < nrows * ncols + 5);
	}
}

int main()
{
	static char s[65536];
	int T;
	scanf("%d", &T);
	while (T-- > 0 && scanf("%d %d", &ncols, &nrows) == 2) {
		tab = (Rec *)malloc(nrows * ncols * sizeof(Rec));
		assert(tab != NULL);

		for (int i = 0; i < nrows; i++) {
			for (int j = 0; j < ncols; j++) {
				Rec &r = tab[i*ncols+j];
				int t = scanf(" %s", s);
				assert(t == 1);
				if (s[0] != '=') {
					r.s = NULL;
					sscanf(s, "%d", &r.x);
				} else {
					r.s = dup(s+1);
				}
			}
		}

		eval_s = (int *)malloc((nrows * ncols + 10) * sizeof(int));
		assert(eval_s != NULL);

		for (int i = nrows*ncols-1; i >= 0; i--)
			if (tab[i].s != NULL) eval(i);
		free(eval_s);

		for (int i = 0; i < nrows; i++) {
			for (int j = 0; j < ncols; j++)
				printf(j ? " %d" : "%d", tab[i*ncols+j].x);
			printf("\n");
		}
		free(tab);

//		if (T) printf("\n");
	}
}
