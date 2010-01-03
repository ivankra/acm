#include <cstdio>
#include <cstring>
#include <cctype>

char ord[256], let[256];
int use[32], rel[32][32], n, nsol;

void tr(int k) {
	if (k == n) {
		for (int i = 0; i < n; i++)
			printf((i+1) >= n ? "%c\n" : "%c ", ord[i]);
		nsol++;
		return;
	}

	for (int a = 0; a < 26; a++) {
		if (use[a] || let['A'+a] == 0) continue;

		for (int b = 0; b < 26; b++)
			if (!use[b] && rel[b][a]) goto skip;

		ord[k] = 'A'+a;
		use[a] = 1;
		tr(k+1);
		use[a] = 0;
skip:;
	}
}

int main()
{
	char buf[4096];
	int T;

	gets(buf); sscanf(buf, "%d", &T);
	while (T-- > 0) {
		gets(buf);

		gets(buf);
		memset(let, 0, sizeof(let));
		for (int i = 0; buf[i]; i++)
			let[buf[i]] = 1;

		n = 0;
		for (int i = 'A'; i <= 'Z'; i++) n += let[i];

		gets(buf);
		memset(rel, 0, sizeof(rel));
		for (char *s = buf;;) {
			while (*s && !isalpha(*s)) s++;
			if (*s == '\0') break;

			int i = *s++ - 'A';

			while (*s && !isalpha(*s)) s++;
			if (*s == '\0') break;

			rel[i][*s++ - 'A'] = 1;
		}

		nsol = 0;
		memset(use, 0, sizeof(use));
		tr(0);

		if (nsol == 0)
			printf("NO\n");

		if (T != 0)
			printf("\n");
	}

	return 0;
}
