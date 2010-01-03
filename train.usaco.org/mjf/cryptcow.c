/*
ID: mjf28791
PROG: cryptcow
LANG: C
*/
#include <stdio.h>
#include <string.h>

#define PDIV 65271
#define HDIV 393209

int plen[PDIV], htab[HDIV], hlen[HDIV], hnext[HDIV], hfree, is_cow[256];
char *pptr[PDIV], *hptr[HDIV], hdata[8 * 1048576];

int check(char *s, int n)
{
	unsigned h;
	int i;

	for (h = 0, i = 0; i < n; i++)
		h = h * 61 + s[i] - 'A';
	h %= HDIV;

	for (i = htab[h]; i != 0; i = hnext[i])
		if (hlen[i] == n && memcmp(hptr[i], s, n) == 0) return 1;

	for (i = 0; i < n; i++)
		hptr[hfree][i] = s[i];
	hptr[hfree + 1] = hptr[hfree] + n;

	hlen[hfree] = n;
	hnext[hfree] = htab[h];
	htab[h] = hfree++;
	return 0;
}

int decode(char *s, int n, char *z, int m)
{
	unsigned i, j, c, o, w;
	char t[76];

	if (n == m) {
		while (n > 0 && *s == *z)
			s++, z++, n--;
		return (n == 0);
	}

	while (*s == *z)
		s++, z++, n--, m--;

	if (*s != 'C')
		return 0;

	while (s[n - 1] == z[m - 1])
		n--, m--;

	if (s[n - 1] != 'W')
		return 0;

	for (i = j = c = 0; i < n; i++) {
		if (is_cow[s[i]]) {
			c %= PDIV;
			if (plen[c] != j || memcmp(pptr[c], s + i - j, j) != 0)
				return 0;
			j = c = 0;
		} else {
			c = c * 31 + s[i];
			j++;
		}
	}

	if (j != 0) {
		c %= PDIV;
		if (plen[c] != j || memcmp(pptr[c], s + i - j, j) != 0)
			return 0;
	}

	if (check(s, n))
		return 0;

	for (c = 0; c < n; t[c] = s[c], c++) {
		if (s[c] != 'C') continue;
		for (o = c + 1; o < n; o++) {
			if (s[o] != 'O') continue;
			for (w = n - 1; w > o; w--) {
				if (s[w] != 'W') continue;

				for (i = c, j = o + 1; j < w;)
					t[i++] = s[j++];

				for (j = c + 1; j < o;)
					t[i++] = s[j++];

				for (j = w + 1; j < n;)
					t[i++] = s[j++];

				if (decode(t, i, z, m))
					return 1;
			}
		}
	}

	return 0;
}

int main()
{
	char s[256], z[] = "Begin the Escape execution at the Break of Dawn";
	int a[256], sn, zn, m, i, j, k;
	unsigned h;

	freopen("cryptcow.in", "r", stdin);
	freopen("cryptcow.out", "w", stdout);

	memset(s, 0, sizeof(s));
	fgets(s, sizeof(s), stdin);

	for (i = 0; s[i] && s[i] != '\r' && s[i] != '\n'; i++);
	s[i] = 0;

	sn = strlen(s);
	zn = strlen(z);

	memset(a, 0, sizeof(a));
	for (i = 0; i < sn; i++)
		a[(unsigned)s[i]]++;

	for (i = 0; i < zn; i++)
		a[(unsigned)z[i]]--;

	if (a['C'] != a['O'] || a['O'] != a['W'] || (zn + 3 * a['C']) != sn) {
		printf("0 0\n");
		return 0;
	}

	m = a['C'];
	a['C'] = a['O'] = a['W'] = 0;

	for (i = 0; i < 256 && a[i] == 0; i++);
	if (i < 256) {
		printf("0 0\n");
		return 0;
	}

	memset(plen, 0, sizeof(plen));
	for (i = 0; i < zn; i++) {
		for (h = 0, j = i; j < zn; j++) {
			h = h * 31 + z[j];
			k = (h % PDIV);
			plen[k] = j - i + 1;
			pptr[k] = z + i;
		}
	}

	memset(is_cow, 0, sizeof(is_cow));
	is_cow['C'] = 1;
	is_cow['O'] = 1;
	is_cow['W'] = 1;

	memset(htab, 0, sizeof(htab));
	hptr[hfree = 1] = hdata;

	if (decode(s, sn, z, zn))
		printf("1 %d\n", m);
	else
		printf("0 0\n");

	return 0;
}
