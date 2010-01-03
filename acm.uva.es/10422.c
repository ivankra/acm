#include <stdio.h>

#define DIV 131071

struct {
	int enc, dist, next;
} tab[131072];

int htab[DIV], tab_last;

int encode_s(char s[])
{
	int i, r;

	for (i = r = 0; i < 25; i++)
		if (s[i] == ' ')
			r |= i << 25;
		else if (s[i] == '1')
			r |= 1 << i;

	return r;
}

int find(int e)
{
	int i;

	for (i = htab[e % DIV]; i != 0; i = tab[i].next)
		if (tab[i].enc == e) return tab[i].dist;

	return -1;
}

void add(int e, int d)
{
	int i;

	i = ++tab_last;
	tab[i].enc = e;
	tab[i].dist = d;
	e %= DIV;
	tab[i].next = htab[e];
	htab[e] = i;
}

void make()
{
	static int dx[] = {  2,  2,  1,  1, -1, -1, -2, -2 };
	static int dy[] = {  1, -1,  2, -2,  2, -2,  1, -1 };
	static int queue[1048576], head, tail;
	int i, d, x, y, m, p, x1, y1, z, p1;

	memset(htab, 0, sizeof(htab));
	tab_last = 0;

	head = tail = 0;
	add(queue[tail++] = encode_s("111110111100 110000100000"), 0);

	while (head < tail) {
		if ((d = find(m = queue[head++])) >= 10)
			break;
		p = (m >> 25);
		y = p / 5;
		x = p % 5;
		m &= (1 << 25) - 1;

		for (i = 0; i < 8; i++) {
			x1 = x + dx[i];
			y1 = y + dy[i];

			if (x1 < 0 || x1 >= 5 || y1 < 0 || y1 >= 5)
				continue;

			p1 = y1 * 5 + x1;

			z = (m & ~(1 << p1)) | (((m >> p1) & 1) << p) | (p1 << 25);
			if (find(z) >= 0) continue;

			add(z, d + 1);
			queue[tail++] = z;
		}
	}
}

int main()
{
	char s[32];
	int i, c, t;

	for (make(), scanf("%d", &t); t-- > 0;) {
		for (i = 0; i < 25 && (c = getchar()) != EOF;)
			if (c == ' ' || c == '0' || c == '1') s[i++] = c;

		if ((i = find(encode_s(s))) < 0)
			printf("Unsolvable in less than 11 move(s).\n");
		else
			printf("Solvable in %d move(s).\n", i);
	}


	return 0;
}
