#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIV  16349

struct {
	char s[32];
	int h, c, next;
} rec[16384];

int tab[DIV], n;

int hash(char *s)
{
	unsigned long a;

	for (a = 0; *s;)
		a = ((a << 5) | ((a >> 27) & 31)) ^ (*s++ - 'A');

	return (a % DIV);
}

void add(char *s)
{
	int i, h;

	for (i = tab[h = hash(s)]; i >= 0; i = rec[i].next) {
		if (rec[i].h == h && strcmp(rec[i].s, s) == 0) {
			rec[i].c++;
			return;
		}
	}

	i = n++;
	strcpy(rec[i].s, s);
	rec[i].h = h;
	rec[i].next = tab[h];
	tab[h] = i;
	rec[i].c = 1;
}

int main()
{
	static char buf[1024];
	int i, t, m;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);
	gets(buf);

	while (t-- > 0) {
		for (i = 0; i < DIV; i++)
			tab[i] = -1;

		for (n = m = 0; gets(buf) && buf[0] != '\0'; m++)
			add(buf);

		qsort(rec, n, sizeof(rec[0]), strcmp);

		for (i = 0; i < n; i++)
			printf("%s %.4f\n",
				rec[i].s, (double)rec[i].c * 100.0 / (double)m);

		if (t > 0)
			printf("\n");
	}

	return 0;
}
