#include <stdio.h>

int dig[256];

void mktab()
{
	char s[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;

	for (i = 0; i < 256; i++)
		dig[i] = 0;
	
	for (i = 0; s[i]; i++)
		dig[s[i]] = i;
}

long long get(char *s, int b)
{
	long long r;
	
	for (r = 0; *s; s++)
		r = r * (long long)b + (long long)dig[*s];

	return r;
}

int minbase(char *s)
{
	int b;

	for (b = 2; *s; s++)
		if (dig[*s] >= b) b = dig[*s] + 1;

	return b;
}

int main()
{
	static char s[1024], t[1024];
	long long x, y;
	int a, b, c, found;

	mktab();

	while (scanf(" %[0-9A-Z] %[0-9A-Z]", s, t) == 2) {
		a = minbase(s);
		c = minbase(t);

		for (found = 0; a <= 36; a++) {
			x = get(s, a);

			for (b = c; b <= 36; b++) {
				y = get(t, b);
				if (x == y) {
					found = 1;
					break;
				}
			}

			if (found)
				break;
		}

		if (found)
			printf("%s (base %d) = %s (base %d)\n",
			       s, a, t, b);
		else
			printf("%s is not equal to %s in any base 2..36\n",
			       s, t);
	}

	return 0;
}
