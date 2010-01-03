#include <stdio.h>
#include <string.h>

int main()
{
	static int s[32768], p[4096];
	int i, j, n, x;

	for (memset(s, 0, sizeof(s)), i = 2; i < 200; i++)
		if (s[i] == 0) for (j = i * i; j < 32768; j += i) s[j] = 1;
	for (i = 0, j = 2; j < 32768; j++) if (s[j] == 0) p[i++] = j;
	p[i] = 0x7fffffff;

	for (scanf("%d", &n); n-- > 0 && scanf("%d", &x) == 1;) {
		for (j = i = 0; p[i] < x; i++)
			if ((x % p[i]) == 0) { j=1; x/=p[i]; break; }
		if (j)
			for (i = 0; p[i] < x; i++)
				if ((x % p[i]) == 0) { j=0; break; }
		printf(j ? "Yes\n" : "No\n");
	}

	return 0;
}
