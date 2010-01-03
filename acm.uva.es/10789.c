#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sieve[2048], a[256];
char s[2048];

int main()
{
	int i, j, c, t;

	memset(sieve, 0, sizeof(sieve));
	for (sieve[0] = sieve[1] = 1, i = 2; i < 46; i++)
		if (!sieve[i]) for (j = i * i; j < 2048; j += i) sieve[j] = 1;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	for (c = 1; c <= t && gets(s); c++) {
		memset(a, 0, sizeof(a));
		for (i = 0; s[i]; i++)
			a[(unsigned)s[i]]++;

		printf("Case %d: ", c);
		for (i = 1, j = 0; i < 128; i++)
			if (isalnum(i) && sieve[a[i]] == 0) j++, putchar(i);
		printf(j ? "\n" : "empty\n");
	}

	return 0;
}
