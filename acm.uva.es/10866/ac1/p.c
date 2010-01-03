#include <stdio.h>
#include <string.h>

int write(int, char *, int);

int main()
{
	static char s[1048576];
	unsigned i, p;
	unsigned long long t, q;

	memset(s, '\0', sizeof(s));

	while (scanf("%u", &p) == 1 && p > 0) {
		if (p <= 2) {
			write(1, "Impossible\n", 11);
			continue;
		}

		memset(s, '1', p);

		if (p < 65536) {
			for (i = 1; i < p; i++)
				s[(i * i - 1) % p] = '0';
		} else {
			for (i = 1; i < 65536; i++)
				s[(i * i - 1) % p] = '0';

			q = (unsigned long long)p;

			for (t = i + 1; t < q; t++)
				s[(unsigned)((t * t - 1) % q)] = '0';
		}

		s[p - 1] = '\n';
		write(1, s, p);
	}

	return 0;
}
