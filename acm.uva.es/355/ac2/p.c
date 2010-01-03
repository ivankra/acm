#include <stdio.h>

int main()
{
	static char s[256], t[256], u[256];
	static int dig[256], a, b;
	long long x;
	register int i, j;

	for (i = 0; i < 256; i++)
		dig[i] = ((i >= '0' && i <= '9') ? (i - '0') :
			  ((i >= 'A' && i <= 'Z') ? (i - 'A' + 10) :
			   ((i >= 'a' && i <= 'z') ? (i - 'a' + 10) : 255)));

	while (scanf(" %d %d %[0-9A-Za-z]", &a, &b, s) == 3) {
		for (x = 0, i = 0; s[i]; i++) {
			if (dig[s[i]] >= a) break;
			x = x * a + dig[s[i]];
		}

		if (s[i]) {
			printf("%s is an illegal base %d number\n", s, a);
			continue;
		}

		for (i = 0; x > 0 || i == 0; x /= b)
			t[i++] = "0123456789ABCDEF"[x % b];

		for (j = 0; i-- > 0;)
			u[j++] = t[i];
		u[j] = '\0';

		printf("%s base %d = %s base %d\n", s, a, u, b);
	}

	return 0;
}
