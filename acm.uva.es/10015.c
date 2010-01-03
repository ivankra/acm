#include <stdio.h>
#include <string.h>

int prime[4096];

void sieve()
{
	static char s[32768];
	int i, j;

	memset(s, 0, sizeof(s));

	for (i = 2; i < 182; i++)
		if (s[i] == 0)
			for (j = i * i; j < 32768; j += i) s[j] = 1;

	for (i = 2, j = 0; i < 32768; i++)
		if (s[i] == 0) prime[j++] = i;
}

int survivor(int n)
{
	int i, s;

	for (s = 0, i = 1; i <= n; i++)
		s = (s + prime[n - i]) % i;

	return (s + 1);
}

int main()
{
	int n;

	sieve();
	while (scanf("%d", &n) == 1 && n != 0)
		printf("%d\n", survivor(n));

	return 0;
}
