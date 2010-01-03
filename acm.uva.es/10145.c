#include <stdio.h>
#include <string.h>

#define DIV 16349

typedef struct {
	struct { int x, y, next; } a[65536];
	int h[DIV], n;
} map_t;

map_t m_blocked, m_excl, m_shar1, m_shar2;

void clear(map_t *m)
{
	memset(m->h, 0, DIV * sizeof(int));
	m->n = 0;
}

int look(map_t *m, int x)
{
	int i;

	for (i = m->h[x % DIV]; i != 0; i = m->a[i].next)
		if (m->a[i].x == x) return m->a[i].y;

	return -1;
}

void add(map_t *m, int x, int y)
{
	int i = ++m->n;
	m->a[i].x = x;
	m->a[i].y = y;
	m->a[i].next = m->h[x % DIV];
	m->h[x % DIV] = i;
}

int S(int x, int y)
{
	int t;

	t = look(&m_excl, y);
	if (t >= 0)
		return (t == x);

	t = look(&m_shar1, y);
	if (t == x) return 1;
	if (t < 0) {
		add(&m_shar1, y, x);
		return 1;
	}

	t = look(&m_shar2, y);
	if (t < 0)
		add(&m_shar2, y, x);

	return 1;
}

int X(int x, int y)
{
	int t;

	t = look(&m_excl, y);
	if (t >= 0)
		return (t == x);

	t = look(&m_shar1, y);
	if (t < 0 || (t == x && look(&m_shar2, y) < 0)) {
		add(&m_excl, y, x);
		return 1;
	}

	return 0;
}

int main()
{
	int c, t, x, y;

	for (scanf("%d", &t); t-- > 0;) {
		clear(&m_blocked);
		clear(&m_excl);
		clear(&m_shar1);
		clear(&m_shar2);

		for (;;) {
			while ((c = getchar()) != EOF)
				if (c == 'S' || c == 'X' || c == '#') break;
			if (c == EOF || c == '#') break;

			scanf("%d %d", &x, &y);

			if (look(&m_blocked, x) > 0) {
				printf("IGNORED\n");
				continue;
			}

			c = (c == 'S') ? S(x, y) : X(x, y);
			printf(c ? "GRANTED\n" : "DENIED\n");

			if (!c) add(&m_blocked, x, 1);
		}

		if (t > 0) printf("\n");
	}

	return 0;
}
