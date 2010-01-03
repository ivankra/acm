#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXN 65536
#define MAXM 131072

struct {
	char *s;
	int adj;
} auth[MAXN];

char namebuf[1048576], *nameptr;
int ref[MAXM], next[MAXM], freelist, nrauth;

int get(char *s)
{
	int i;

	for (i = 0; i < nrauth; i++)
		if (strcmp(auth[i].s, s) == 0) return i;

	auth[nrauth].s = nameptr;
	do { *nameptr++ = *s; } while (*s++ != '\0');

	auth[nrauth].adj = 0;
	return nrauth++;
}

int insert(int list, int r)
{
	int t;

	t = freelist;
	freelist = next[freelist];

	next[t] = list;
	ref[t] = r;

	return t;
}

void release(int list)
{
	int t;

	while (list != 0) {
		t = next[list];
		next[list] = freelist;
		freelist = list;
		list = t;
	}
}

void parse(char *s)
{
	static char nam[65536];
	static int a[1024];
	char *p;
	int i, j, k;

	for (k = 0;;) {
		while (*s && (isspace(*s) || *s == ',')) s++;

		if (*s == '\0' || *s == ':')
			break;

		for (p = nam; *s && *s != ',' && *s != ':';)
			*p++ = *s++;

		if (*s == ',') {
			for (*p++ = *s++; *s && *s != ',' && *s != ':';)
				*p++ = *s++;
		}
		*p = '\0';

		a[k++] = get(nam);
	}

	for (i = 0; i < k; i++) {
		for (j = 0; j < k; j++) {
			if (a[i] == a[j]) continue;
			auth[a[i]].adj = insert(auth[a[i]].adj, a[j]);
		}
	}
}

int search(int a, int b)
{
	static int q[MAXN], d[MAXN], *qt, *qh;
	int i, k;

	qh = qt = q;
	*qt++ = a;

	for (i = 0; i < nrauth; i++)
		d[i] = 0;
	d[a] = 1;

	while (qh < qt && *qh != b) {
		k = *qh++;

		for (i = auth[k].adj; i != 0; i = next[i]) {
			if (d[ref[i]] == 0) {
				d[ref[i]] = d[k] + 1;
				*qt++ = ref[i];
			}
		}
	}

	return (*qh == b) ? (d[b] - 1) : -1;
}

int main()
{
	static char buf[65536];
	char *s;
	int i, p, q, r, t;

	for (freelist = i = 1; i < MAXM; i++)
		next[i] = i + 1;
	next[MAXM - 1] = 0;

	for (scanf("%d", &r), t = 1; t <= r; t++) {
		while (gets(buf) && sscanf(buf, "%d %d", &p, &q) != 2);

		nameptr = namebuf;
		nrauth = 0;

		while (p-- > 0 && gets(buf))
			parse(buf);

		printf("Scenario %d\n", t);

		p = get("Erdos, P.");
		while (q-- > 0 && gets(buf)) {
			for (s = buf; *s && isspace(*s); s++);

			i = search(get(s), p);
			printf((i < 0) ? "%s infinity\n" : "%s %d\n", s, i);
		}

		for (i = 0; i < nrauth; i++)
			release(auth[i].adj);
	}

	return 0;
}
