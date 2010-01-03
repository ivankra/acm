#include <stdio.h>
#include <string.h>

char *cfg[] = {
	"c2347890", "d234789", "e23478", "f2347", "g234", "a23", "b2",
	"C3", "D1234789", "E123478", "F12347", "G1234", "A123", "B12", NULL
};

int tab[256][16];

int main()
{
	static char buf[1024];
	int i, k, t, use[16], r[16];
	char *s;

	memset(tab, 0, sizeof(tab));
	for (i = 0; cfg[i]; i++)
		for (s = cfg[i] + 1, k = cfg[i][0]; *s; s++)
			tab[k][*s - '0'] = 1;

	while (gets(buf) && sscanf(buf, "%d", &t) != 1);

	while (t-- > 0 && gets(buf)) {
		memset(use, 0, sizeof(use));
		memset(r, 0, sizeof(r));

		for (s = buf; *s; s++) {
			for (i = 0; i < 10; i++) {
				if (use[i] == tab[*s][i]) continue;

				if (tab[*s][i] == 1)
					r[i]++;

				use[i] = tab[*s][i];
			}
		}

		for (i = 1; i <= 9; i++)
			printf("%d ", r[i]);
		printf("%d\n", r[0]);
	}

	return 0;
}
