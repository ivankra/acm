#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct team {
	char name[32], lwr[32];
	int pt, gs, ga, won, lost, draw, gm, gdiff;
};

struct team teams[32];

int compare(const void *p1, const void *p2)
{
	struct team *p = (struct team *)p1, *q = (struct team *)p2;
	if (p->pt != q->pt) return (p->pt > q->pt) ? -1 : 1;
	if (p->won != q->won) return (p->won > q->won) ? -1 : 1;
	if (p->gdiff != q->gdiff) return (p->gdiff > q->gdiff) ? -1 : 1;
	if (p->gs != q->gs) return (p->gs > q->gs) ? -1 : 1;
	if (p->gm != q->gm) return (p->gm < q->gm) ? -1 : 1;
	return strcmp(p->lwr, q->lwr);
}

void tolwr(char *p)
{
	for (; *p; p++)
		*p = tolower(*p);
}

int main()
{
	static char s1[4096], s2[4096], s3[4096];
	int i, m, n, t, x, y, gx, gy;

	while (gets(s1) && sscanf(s1, "%d", &t) != 1);

	while (t-- > 0 && gets(s1)) {
		printf("%s\n", s1);

		while (gets(s1) && sscanf(s1, "%d", &n) != 1);

		memset(teams, 0, sizeof(teams));
		for (i = 0; i < n; i++) {
			gets(teams[i].name);

			strcpy(teams[i].lwr, teams[i].name);
			tolwr(teams[i].lwr);
		}

		while (gets(s1) && sscanf(s1, "%d", &m) != 1);

		while (m-- > 0 && fgets(s1,sizeof(s1),stdin) != NULL) {
			sscanf(s1, "%[^#]#%d@%d#%[^#\r\n]", s2, &gx, &gy, s3);

			for (x = 0; x < n && strcmp(teams[x].name, s2) != 0; x++);
			if (x >= n) {
				tolwr(s2);
				for (x = 0; x < n && strcmp(teams[x].lwr, s2) != 0; x++);
			}

			for (y = 0; y < n && strcmp(teams[y].name, s3) != 0; y++);
			if (y >= n) {
				tolwr(s3);
				for (y = 0; y < n && strcmp(teams[y].lwr, s3) != 0; y++);
			}

			teams[x].gs += gx;
			teams[x].ga += gy;

			teams[y].gs += gy;
			teams[y].ga += gx;

			teams[x].gm++;
			teams[y].gm++;

			if (gx > gy) {
				teams[x].won++;
				teams[y].lost++;
			} else if (gx == gy) {
				teams[x].draw++;
				teams[y].draw++;
			} else {
				teams[x].lost++;
				teams[y].won++;
			}
		}

		for (i = 0; i < n; i++)
			teams[i].pt = 3 * teams[i].won + teams[i].draw;

		for (i = 0; i < n; i++)
			teams[i].gdiff = teams[i].gs - teams[i].ga;

		qsort(teams, n, sizeof(teams[0]), &compare);

		for (i = 0; i < n; i++) {
			printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
				i + 1, teams[i].name, teams[i].pt,
				teams[i].gm, teams[i].won, teams[i].draw,
				teams[i].lost, teams[i].gdiff,
				teams[i].gs, teams[i].ga);
		}

		if (t > 0)
			printf("\n");
	}

	return 0;
}
