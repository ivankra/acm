/*
ID: mjf28791
PROG: fence8
LANG: C
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define HDIV	196597
#define HSIZE	131072

int nboards, nrails, zlimit, znext;
int length[64], left[64], rail[2048], which[2048];

unsigned crctab[256];
int htab[HDIV], hnext[HSIZE], hfree;
unsigned char hdata[HSIZE][50];

int check()
{
	static unsigned char c1[256], c2[256];
	unsigned i, j, h;

	for (i = 0; i <= 128; i++)
		c1[i] = 0;

	for (i = 0; i < nboards; i++)
		c1[left[i]]++;

	for (h = 0, i = 0, j = 0; i <= 128; i++) {
		h = (h << 8) ^ crctab[h >> 24] ^ c1[i];
		for (; c1[i] > 0; c1[i]--) c2[j++] = i;
	}

	h %= HDIV;

	for (i = htab[h]; i != 0; i = hnext[i])
		if (memcmp(hdata[i], c2, nboards) == 0) return 1;

	if (hfree < (HSIZE - 4)) {
		i = hfree++;
		memcpy(hdata[i], c2, nboards);
		hnext[i] = htab[h];
		htab[h] = i;
	}

	return 0;
}

void mkcrc()
{
	unsigned i, j, r;

	for (i = 0; i < 0x100; i++) {
		for (r = i << 24, j = 8; j--;)
			r = (r << 1) ^ ((r & 0x80000000) ? 0xEDB88320 : 0);
		crctab[i] = r;
	}
}

int find(int s)
{
	int i, j, k, t;

	if (s >= zlimit)
		return 1;

	for (i = 0, t = s; i < nboards; i++) {
		for (j = s, k = left[i]; j < nrails && k >= rail[j]; j++)
			k -= rail[j];
		t += j - s;
	}

	for (i = 0, j = 0; i < nboards; i++) j += left[i];
	rail[nrails] = 0x7FFFFFFF;
	for (i = s; j >= rail[i]; i++) j -= rail[i];

	if (i < t) t = i; 

	if (t < zlimit) {
		if (t > znext) znext = t;
		return 0;
	}

	if (check())
		return 0;

	if (s > 0 && rail[s - 1] == rail[s])
		k = which[s - 1];
	else
		k = 0;

	for (i = k; i < nboards; i++) {
		if ((left[i] - rail[s]) >= rail[s] &&
		    (i > 0 || left[i - 1] != left[i])) {
			left[i] -= rail[s];
			which[s] = i;
			if (find(s + 1)) return 1;
			left[i] += rail[s];
		}
	}

	for (i = k; i < nboards; i++) {
		if (left[i] >= rail[s] &&
		    (left[i] - rail[s]) < rail[s] &&
		    (i > 0 || left[i - 1] != left[i])) {
			left[i] -= rail[s];
			which[s] = i;
			if (find(s + 1)) return 1;
			left[i] += rail[s];
		}
	}

	return 0;
}

int cmpa(const void *p, const void *q)
{
	return *(int *)p - *(int *)q;
}

int cmpd(const void *p, const void *q)
{
	return *(int *)q - *(int *)p;
}

int main()
{
	int i;

	freopen("fence8.in", "r", stdin);
	freopen("fence8.out", "w", stdout);

	scanf("%d", &nboards);
	for (i = 0; i < nboards; i++)
		scanf("%d", &length[i]);

	scanf("%d", &nrails);
	for (i = 0; i < nrails; i++)
		scanf("%d", &rail[i]);

	qsort(length, nboards, sizeof(length[0]), &cmpd);
	qsort(rail, nrails, sizeof(rail[0]), &cmpa);

	mkcrc();

	for (zlimit = nrails;; zlimit = znext) {
		znext = -1;

		for (i = 0; i < nboards; i++)
			left[i] = length[i];

		memset(htab, 0, sizeof(htab));
		hfree = 1;

		if (find(0)) break;
		if (znext < 0) break;
	}

	printf("%d\n", zlimit);

	return 0;
}
