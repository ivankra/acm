#include <stdio.h>

static char *tokp;
static int tok;

static int next()
{
	for (;;) {
		if (*tokp == '\0') return (tok = 0);

		if (*tokp == '+') {
			if (*++tokp != '+') return (tok = '+');
			tokp++;
			return (tok = 'I');
		}

		if (*tokp == '-') {
			if (*++tokp != '-') return (tok = '-');
			tokp++;
			return (tok = 'D');
		}

		if (*tokp >= 'a' && *tokp <= 'z')
			return (tok = *tokp++);

		if (*tokp >= 'A' && *tokp <= 'Z')
			 return (tok = *tokp++ - 'A' + 'a');

		tokp++;
	}
}

int main()
{
	static int val[26], used[26], r, sign;
	static char buf[4096];
	register int i;

	while (gets(buf)) {
		tokp = buf;

		for (i = 0; i < 26; i++) {
			val[i] = i + 1;
			used[i] = 0;
		}

		next();

		for (sign = 1, r = 0;;) {
			if (tok == 'I') {
				r += sign * ++val[i = (next() - 'a')];
				used[i] = 1;
				next();
			} else if (tok == 'D') {
				r += sign * --val[i = (next() - 'a')];
				used[i] = 1;
				next();
			} else if (tok >= 'a' && tok <= 'z') {
				r += sign * val[i = (tok - 'a')];
				used[i] = 1;

				next();
				if (tok == 'I') {
					val[i]++;
					next();
				} else if (tok == 'D') {
					val[i]--;
					next();
				}
			} else {
				break;
			}

			sign = 1;
			if (tok == '+') {
				next();
			} else if (tok == '-') {
				sign = -1;
				next();
			} else {
				break;
			}
		}

		printf("Expression: %s\n    value = %d\n", buf, r);
		for (i = 0; i < 26; i++)
			if (used[i])
				printf("    %c = %d\n", i + 'a', val[i]);
	}

	return 0;
}
