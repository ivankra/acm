/*
ID: mjf28791
PROG: contact
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count[16][4096], a, b;

int compare(const void *p, const void *q)
{
	return *(int *)q - *(int *)p;
}

char *bin(int x, int n)
{
	static char s[1024];
	int i;

	for (s[n] = '\0', i = 0; i < n; i++)
		s[i] = ((x >> (n - i - 1)) & 1) + '0';

	return s;
}

void print(int f)
{
	int i, j, k;

	printf("%d", f);

	for (i = a, k = 0; i <= b; i++) {
		for (j = 0; (j >> i) == 0; j++) {
			if (count[i][j] == f) {
				printf(k ? " %s" : "\n%s", bin(j, i));
				k = (k + 1) % 6;
			}
		}
	}

	printf("\n");
}

int main()
{
	static int freq[65536], nfreq;
	int i, j, c, n, last;

	freopen("contact.in", "r", stdin);
	freopen("contact.out", "w", stdout);

	scanf("%d %d %d", &a, &b, &nfreq);

	memset(count, 0, sizeof(count));

	for (n = 0, last = 0; (c = getchar()) != EOF;) {
		if (c != '0' && c != '1')
			continue;

		last = (last << 1) | (c - '0');
		if (n < b) n++;

		for (i = a; i <= n; i++)
			count[i][last & ((1 << i) - 1)]++;
	}

	for (n = 0, i = a; i <= b; i++)
		for (j = (1 << i) - 1; j >= 0; j--)
			freq[n++] = count[i][j];

	qsort(freq, n, sizeof(freq[0]), &compare);

	if (n >= 1) {
		for (i = j = 1; i < n; i++)
			if (freq[i - 1] != freq[i]) freq[j++] = freq[i];
		n = j;
	}

	for (i = 0; i < nfreq && i < n && freq[i] > 0; i++)
		print(freq[i]);

	return 0;
}
