/*
ID: infnty1
PROB: calfflac
LANG: C++
*/
#include <stdio.h>
#include <ctype.h>

typedef struct { int a,b; } loc;

char text[32768];
int alpha[32768], offs[32768], n;

loc find(int s)
{
	static loc p[32768], r;
	int i, j, m;

	for (i = m = 0; i < n; i++) {
		p[m].a = i;
		p[m++].b = i+s;
	}
	r.a = r.b = 0;

	while (m > 0) {
		r = p[0];
		for (i = j = 0; i < m; i++) {
			if (p[i].a <= 0 || p[i].b >= n) continue;
			if (alpha[p[i].a-1] != alpha[p[i].b]) continue;
			p[j].a = p[i].a - 1;
			p[j++].b = p[i].b + 1;
		}
		m = j;
	}

	return r;
}

int main()
{
	int i, j;
	loc p, q;

	freopen("calfflac.in", "r", stdin);
	freopen("calfflac.out", "w", stdout);

	for (i = n = 0; (j = getchar()) != EOF; i++) {
		text[i] = j;
		if (isalpha(j)) { alpha[n]=tolower(j); offs[n++]=i; }
	}
	text[i] = 0;

	p = find(0);
	q = find(1);
	if (p.b-p.a < q.b-q.a) p = q;

	printf("%d\n", p.b-p.a);
	printf("%.*s\n", offs[p.b-1]-offs[p.a]+1, text+offs[p.a]);

	return 0;
}
