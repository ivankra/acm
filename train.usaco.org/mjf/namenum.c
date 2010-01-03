/*
ID: mjf28791
PROG: namenum
LANG: C
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int a[16], z[256], n, k;
char s[65536];

int main()
{
	int i, c;

	for (i = 0; i < 256; i++)
		z[i] = -1;

	for (i = 0; i < 24; i++)
		z["ABCDEFGHIJKLMNOPRSTUVWXY"[i]] = 2 + i / 3;

	freopen("namenum.in", "r", stdin);

	while ((c = getchar()) != EOF && !isdigit(c));
	for (n = 0; c != EOF && c != '\n'; c = getchar())
		if (isdigit(c)) a[n++] = c - '0';

	freopen("dict.txt", "r", stdin);
	freopen("namenum.out", "w", stdout);

	for (k = 0; scanf(" %[A-Z]", s) == 1;) {
		if (strlen(s) != n) continue;

		for (i = 0; i < n && a[i] == z[s[i]]; i++);
		if (i < n) continue;

		printf("%s\n", s);
		k++;
	}

	if (k == 0)
		printf("NONE\n");

	return 0;
}
