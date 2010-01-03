#include <stdio.h>
#include <string.h>

int hp1, hp2, m, flimit, fnext;

typedef struct {
	int a[16], n, s, g;
} state_t;

void canonic(state_t *s)
{
	int i, j, t;

	for (i = 1; i < s->n; i++) {
		for (t = s->a[i], j = i - 1; j >= 0 && s->a[j] > t; j--)
			s->a[j + 1] = s->a[j];
		s->a[j + 1] = t;
	}

	if ((s->s + s->n) > m)
		s->s = m - s->n;
}

int estimate(state_t *s)
{
	int i, h, t;

	for (t = 1, i = 0; i < s->n; i++)
		if (s->a[i] > t) t = s->a[i];

	for (h = 0, i = 0; i < s->n; i++)
		h += t - s->a[i];

	if (s->n == m)
		return h;	/* exact */

	if (s->s >= (m - s->n))
		return (h + (m - s->n) * t);

	return (h + (m - s->n) * t + (m - s->n - s->s));
}

int find(state_t *s)
{
	state_t t;
	int i, k;

	k = s->g + estimate(s);
	if (k > flimit) {
		if (k < fnext) fnext = k;
		return 0;
	}

	if (s->n == m) {
		fnext = k;
		return 1;
	}

	for (k = s->s; k >= 0; k--) {
		t.n = s->n + k;
		if (t.n > m) continue;

		t.g = s->g + 1;
		t.s = s->s - k;

		for (i = 0; i < s->n; i++) {
			t.a[i] = s->a[i] + 1;
			if (t.a[i] == hp1 || t.a[i] == hp2) t.s++;
		}

		for (i = 0; i < k; i++)
			t.a[s->n + i] = 1;

		if (t.n == 0)
			continue;

		canonic(&t);

		for (i = t.n - 1; i >= 0; i--) {
			if (i > 0 && t.a[i - 1] == t.a[i])
				continue;

			t.a[i]++;
			if (t.a[i] == hp1 || t.a[i] == hp2) t.s++;

			if (find(&t)) return 1;

			if (t.a[i] == hp1 || t.a[i] == hp2) t.s--;
			t.a[i]--;
		}
	}

	return 0;
}

int solve()
{
	state_t s;

	for (fnext = 0;;) {
		flimit = fnext;
		fnext = 0x7FFFFFFF;

		s.n = s.g = 0;
		s.s = 1;

		if (find(&s))
			return fnext;
	}
}

int main()
{
	int c = 1, t;

	for (scanf("%d", &t); c <= t && scanf("%d %d %d", &hp1, &hp2, &m) == 3;)
		printf("Case %d: %d\n", c++, solve());

	return 0;
}
