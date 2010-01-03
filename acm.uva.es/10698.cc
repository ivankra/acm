#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <algorithm>
using namespace std;

struct team {
	char name[80];
	int id, pt, goals, suf, gm, dif;
} a[32];
int T, G;

int strccmp(char *p, char *q)
{
	while (*p && tolower(*p) == tolower(*q)) p++, q++;
	if (*p == *q) return 0;
	return tolower(*p) - tolower(*q);
}

int idcmp;

int cmp(const void *pp, const void *qq)
{
	team *p=(team *)pp, *q=(team *)qq;

	if (p->pt != q->pt) { return q->pt - p->pt; }
	if (p->dif != q->dif) { return q->dif - p->dif; }
	if (p->goals != q->goals) { return q->goals - p->goals; }

	if (idcmp) return strccmp(p->name, q->name);

	return 0;
}

int get(char *s)
{
	for (int i = 0; i < T; i++)
		if (strcmp(a[i].name, s) == 0) return i;
	assert(1==0);
	return -1;
}

void readgame()
{
	char buf1[256], buf2[256];
	int g1, t1, g2, t2;

	scanf(" %s %d - %d %s", buf1, &g1, &g2, buf2);
	t1 = get(buf1); t2 = get(buf2);

	if (g1 < g2) { swap(g1,g2); swap(t1,t2); }

	a[t1].gm++;
	if (t1!=t2) a[t2].gm++;

	a[t1].goals += g1; a[t1].suf += g2;
	a[t2].goals += g2; a[t2].suf += g1;

	if (g1 == g2) {
		a[t1].pt++; a[t2].pt++;
	} else {
		a[t1].pt+=3;
	}
}

int main()
{
	char buf[1024];
	int t;

	for (t = 0;;) {
		for (;;) {
			if (gets(buf) == NULL) return 0;
			if (sscanf(buf, "%d %d", &T, &G) == 2) break;
		}
		if (T == 0 && G == 0) break;

		memset(a, 0, sizeof(a));
		for (int i = 0; i < T; i++) { a[i].id=i; scanf(" %s", a[i].name); }
		for (int i = 0; i < G; i++) readgame();
		for (int i = 0; i < T; i++) a[i].dif = a[i].goals-a[i].suf;

		idcmp=1;
		qsort(a, T, sizeof(a[0]), &cmp);
		idcmp=0;

		if (t++) printf("\n");
		for (int i = 0; i < T; i++) {
			if (i == 0 || cmp(&a[i-1], &a[i]) != 0)
				printf("%2d. ", i+1);
			else
				printf("    ");
			printf("%15s %3d %3d %3d %3d %3d ", a[i].name, a[i].pt, a[i].gm,
				a[i].goals, a[i].suf, a[i].goals-a[i].suf);
			if (a[i].gm == 0) printf("%6s\n", "N/A");
			else printf("%6.2f\n", (a[i].pt) * 100. / (3.*a[i].gm) + 1e-9);
		}
//		printf("\n");
	}

	return 0;
}
