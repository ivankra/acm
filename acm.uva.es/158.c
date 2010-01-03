#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _list {
	struct _list *next, *last;
	char s[1];
} list_t;

int year, no_of_days, day_date[512], day_mon[512];
list_t *ev[512][8], *ev2[512];

void add(list_t **l, char *s)
{
	list_t *p;

	while (*s == ' ') s++;

	p = (list_t *)malloc(sizeof(list_t) + strlen(s));
	p->last = p;
	strcpy(p->s, s);

	if ((*l) == NULL) {
		p->next = NULL;
		(*l) = p;
	} else {
		((*l)->last)->next = p;
		p->next = NULL;
		(*l)->last = p;
	}
}

int day_of_year(int m, int d)
{
	int i, r, s[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	s[2] = ((year % 4) == 0) ? 29 : 28;
	if (d > s[m]) return 500;
	for (r = d, i = 1; i < m; i++) r += s[i];
	return r;
}

void process(int p)
{
	int i, j, k, q, sh;
	list_t *l;

	printf("Today is:%3d%3d\n", day_date[p], day_mon[p]);

	for (l = ev2[p]; l; l = l->next)
		printf("%3d%3d *TODAY* %s\n", day_date[p], day_mon[p], l->s);

	for (sh = 1; sh <= 7; sh++) {
		for (i = 7; i >= sh; i--) {
			q = ((p + sh - 1) % no_of_days) + 1;
			for (l = ev[q][i]; l; l = l->next) {
				printf("%3d%3d ", day_date[q], day_mon[q]);

				if (sh == 0) {
					printf("*TODAY*");
				} else {
					for (j = i - sh + 1, k = 0; k < j; k++)
						printf("*");
					while (k++ < 7) printf(" ");
				}

				printf(" %s\n", l->s);
			}
		}
	}
}

int main()
{
	static char s[1024], c;
	int d, m, p, t;

	scanf("%d", &year);
	memset(ev, 0, sizeof(ev));
	memset(ev2, 0, sizeof(ev2));
	no_of_days = ((year % 4) == 0) ? 366 : 365;

	for (m = 1; m <= 12; m++) {
		for (d = 1; d <= 31; d++) {
			day_mon[day_of_year(m, d)] = m;
			day_date[day_of_year(m, d)] = d;
		}
	}

	for (t = 0; scanf(" %c", &c) == 1 && c != '#';) {
		if (c == 'A' || c == 'a') {
			scanf(" %d %d %d", &d, &m, &p);
			gets(s);
			add(&ev[day_of_year(m, d)][p], s);
			add(&ev2[day_of_year(m, d)], s);
		} else if (c == 'D' || c == 'd') {
			if (t++) printf("\n");
			scanf("%d %d", &d, &m);
			process(day_of_year(m, d));
		}
	}

	return 0;
}
