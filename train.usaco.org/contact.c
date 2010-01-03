/*
ID: infnty1
PROB: contact
LANG: C
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count[13][4096], freq[131072], a, b, n;

int cmp(const void *p, const void *q) { return *(int *)q - *(int *)p; }

char *bin(int n, int x)
{
	static char s[16];
	int i;

	for (s[n] = 0, i = n; i--;)
		s[n-1-i] = ((x >> i) & 1) + '0';
	return s;
}

void prn(int f)
{
	int i, j, k;

	for (k = 0, i = a; i <= b; i++)
		for (j = 0; j < (1 << i); j++) {
			if (count[i][j] != f) continue;
			printf(k ? " %s" : "%s", bin(i,j));
			if (k == 5) printf("\n"), k = 0; else k++;
		}
	if (k != 0) printf("\n");
}

int main()
{
	int i, j, k, c;

	freopen("contact.in", "r", stdin);
	freopen("contact.out", "w", stdout);

	scanf("%d %d %d", &a, &b, &n);
	memset(count, 0, sizeof(count));

	for (i = j = 0; (c = getchar()) != EOF;) {
		if (c != '0' && c != '1') continue;

		j = ((j << 1) | (c - '0')) & 0x0FFF;
		if (i < b) i++;

		for (k = a; k <= i; k++)
			count[k][j & ((1 << k) - 1)]++;
	}

	for (k = 0, i = a; i <= b; i++)
		for (j = 0; j < (1 << i); j++)
			freq[k++] = count[i][j];

	for (i = 0; i < 10; i++) freq[k++] = 0;

	qsort(freq, k, sizeof(freq[0]), &cmp);

	for (i = 1, j = 0; j < k; j++)
		if (freq[i-1] != freq[j]) freq[i++] = freq[j];
	k = i;

	for (i = 0; i < n && i < k && freq[i] > 0; i++) {
		printf("%d\n", freq[i]);
		prn(freq[i]);
	}

	return 0;
}
