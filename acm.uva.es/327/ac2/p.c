#include <stdio.h>

static char *tokp;
static int tok, var, alpha[256], used[32];

static int next(void)
{
	for (;;) {
		if (*tokp == '\0') return (tok = 0);

		if (*tokp == '+') {
			if (*++tokp != '+') return (tok = '+');
			tokp++;
			return (tok = 'i');
		}

		if (*tokp == '-') {
			if (*++tokp != '-') return (tok = '-');
			tokp++;
			return (tok = 'd');
		}

		if (alpha[*tokp]) {
			used[var = *tokp++ - 'a'] = 1;
			return (tok = 'v');
		}

		tokp++;
	}
}

int main()
{
	static int val[32];
	static char buf[4096];
	register int i, r, sign;

	for (i = 0; i < 256; i++)
		alpha[i] = (i >= 'a' && i <= 'z');

	while (gets(buf)) {
		tokp = buf;

		for (i = 0; i < 26; i++) val[i] = i + 1;
		for (i = 0; i < 26; i++) used[i] = 0;

		next();

		for (sign = 1, r = 0;;) {
			if (tok == 'i') {
				next();
				r += sign * ++val[var];
				next();
			} else if (tok == 'd') {
				next();
				r += sign * --val[var];
				next();
			} else if (tok == 'v') {
				r += sign * val[var];

				if (next() == 'i') {
					val[var]++;
					next();
				} else if (tok == 'd') {
					val[var]--;
					next();
				}
			} else {
				break;
			}

			if (tok == '+') {
				sign = 1;
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
