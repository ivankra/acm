/*
ID: mjf28791
PROG: calfflac
LANG: C
*/
#include <stdio.h>
#include <ctype.h>

char input[65536], s[65536], even[65536], odd[65536];
int tab[65536], p[65536], q[65536], n, np, nq;
int even_pos, even_len, odd_pos, odd_len;

void findodd()
{
	int i, j, c;

	for (i = 0; i < n; i++)
		p[i] = i;

	for (c = 1, np = n;; c += 2) {
		for (nq = 0, i = 0; i < np; i++) {
			if (p[i] == 0 || (p[i] + c) >= n)
				continue;

			if (s[p[i] - 1] == s[p[i] + c])
				q[nq++] = p[i] - 1;
		}

		if (nq == 0)
			break;

		np = nq;
		for (i = 0; i < nq; i++)
			p[i] = q[i];
	}

	odd_len = c;
	odd_pos = p[0];

	for (i = tab[p[0]], j = 0; c > 0; i++) {
		odd[j++] = input[i];
		if (isalpha(input[i])) c--;
	}
	odd[j] = '\0';
}

void findeven()
{
	int i, j, c;

	for (i = 0, np = 0; i < (n - 1); i++)
		if (s[i] == s[i + 1]) p[np++] = i;

	if (np == 0) {
		even_len = -1;
		return;
	}

	for (c = 2;; c += 2) {
		for (nq = 0, i = 0; i < np; i++) {
			if (p[i] == 0 || (p[i] + c) >= n)
				continue;

			if (s[p[i] - 1] == s[p[i] + c])
				q[nq++] = p[i] - 1;
		}

		if (nq == 0)
			break;

		np = nq;
		for (i = 0; i < nq; i++)
			p[i] = q[i];
	}

	even_len = c;
	even_pos = p[0];

	for (i = tab[p[0]], j = 0; c > 0; i++) {
		even[j++] = input[i];
		if (isalpha(input[i])) c--;
	}
	even[j] = '\0';
}

int main()
{
	int i, c;

	freopen("calfflac.in", "r", stdin);
	freopen("calfflac.out", "w", stdout);

	for (i = 0, n = 0; (c = getchar()) != EOF; i++) {
		input[i] = c;
		if (isalpha(c)) {
			tab[n] = i;
			s[n++] = tolower(c);
		}
	}

	if (n == 0) {
		printf("0\n");
		return 0;
	}

	findeven();
	findodd();

	if (even_len > odd_len || (even_len == odd_len && even_pos < odd_pos))
		printf("%d\n%s\n", even_len, even);
	else
		printf("%d\n%s\n", odd_len, odd);

	return 0;
}
