#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char m[1000010];

static int next(int n)
{
	register int s;

	for (s = n; n > 0; n /= 10)
		s += n % 10;

	return s;
}

int main()
{
	int i, j;

	memset(m, '\0', sizeof(m));

	for (i = 1; i <= 1000000; i++) {
		if (m[i])
			continue;

		printf("%d\n", i);

		for (j = i; j <= 1000000 && m[j] == 0; j = next(j))
			m[j] = 1;
	}

	return 0;
}
