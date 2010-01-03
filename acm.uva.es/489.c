#include <stdio.h>
#include <ctype.h>

int main()
{
	static char s[65536], t[65536];
	char *p;
	int a[32], b[32], i, c, w, r, m;

	while (scanf("%d%*1[\n]%[^\n]%*1[\n]%[^\n]", &r, s, t) == 3 && r != -1) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));

		for (i = 0; s[i]; i++)
			s[i] = tolower(s[i]);

		for (i = 0; t[i]; i++)
			t[i] = tolower(t[i]);

		for (i = m = 0; s[i]; i++) {
			if (isalpha(s[i])) {
				a[s[i] - 'a']++;
				m++;
			}
		}

		for (p = t, w = 0; m > 0 && w < 7 && *p; p++) {
			if (!isalpha(*p) || b[*p - 'a'])
				continue;

			b[*p - 'a'] = 1;

			if (a[*p - 'a'] == 0) {
				w++;
			} else {
				m -= a[*p - 'a'];
				a[*p - 'a'] = 0;
			}
		}

		printf("Round %d\n", r);

		if (w >= 7)
			printf("You lose.\n");
		else if (m > 0)
			printf("You chickened out.\n");
		else
			printf("You win.\n");
	}

	return 0;
}
