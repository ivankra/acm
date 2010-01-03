#include <stdio.h>
#include <string.h>

int main()
{
	static char s[1024], t[1024];
	int r[16], a, f, n, i;

	for (;;) {
		memset(r, 0, sizeof(r));

		for (n = f = 0; scanf("%d %[a-z] %[a-z]", &a, s, t) == 3 && a > 0;) {
			n++;

			if (s[0] == 'r') {
				break;
			} else if (t[0] == 'l') {
				if (r[a] == 'h')
					f = 1;
				else
					r[a] = 'l';
			} else if (t[0] == 'h') {
				if (r[a] == 'l')
					f = 1;
				else
					r[a] = 'h';
			}
		}

		if (n == 0 || a == 0)
			break;

		for (i = 1; i <= 10; i++)
			if ((r[i] == 'l' && i >= a) ||
			    (r[i] == 'h' && i <= a))
				f = 1;

		printf(f ? "Stan is dishonest\n" : "Stan may be honest\n");
	}

	return 0;
}
