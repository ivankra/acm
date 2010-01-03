#include <stdio.h>
#include <string.h>

int xdig[256], isxdig[256];

int solve(char *s)
{
	int i, a, b, n;
	char *p;

	if (!isxdig[*s]) return 0;
	for (p = s; isxdig[*p]; p++);

	for (n = 0; *p; n++) {
		if (*p++ != '#') return 0;
		if (!isxdig[(int)*p]) return 0;
		while (isxdig[(int)*p]) p++;
		if (*p++ != '#') return 0;
	}

	if (n == 0) {
		for (p = s; *p; p++)
			if (!isxdig[*p] || xdig[*p] >= 10) return 0;
		return 1;
	}

	for (b = 0, p = s; *p && *p != '#'; p++) {
		if (!isxdig[*p] || xdig[*p] >= 10) return 0;
		b = b * 10 + xdig[*p];
		if (b > 100) return 0;
	}
	if (b < 2 || b > 16) return 0;

	while (n-- > 1) {
		if (*p++ != '#') return 0;

		for (a = 0; *p && *p != '#'; p++) {
			if (!isxdig[*p] || xdig[*p] >= b) return 0;
			a = a * b + xdig[*p];
			if (a > 100) return 0;
		}

		if (a < 2 || a > 16) return 0;
		if (*p++ != '#') return 0;
		b = a;
	}

	if (*p++ != '#') return 0;
	if (!isxdig[*p]) return 0;

	for (; *p && *p != '#'; p++)
		if (!isxdig[*p] || xdig[*p] >= b) return 0;

	if (*p++ != '#') return 0;
	return (*p == '\0');
}

int main()
{
	static char s[256];
	int i, t;

	while (gets(s) && sscanf(s, "%d", &t) != 1);

	memset(isxdig, 0, sizeof(isxdig));
	strcpy(s, "0123456789abcdef");
	for (i = 0; s[i]; i++) {
		isxdig[s[i]] = 1;
		xdig[s[i]] = i;
	}

	while (t-- > 0 && gets(s))
		printf(solve(s) ? "yes\n" : "no\n");

	return 0;
}
