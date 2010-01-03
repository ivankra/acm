#include <cstdio>
#include <cstring>
#include <cctype>

int main()
{
	char s[1024];
	int i, n;
	while (scanf(" %s %d", s, &n) == 2) {
		n--;
		if (n < 0) {
			for (i = 0; s[i] && s[i] != '.';) putchar(s[i++]);
			putchar('\n');
			continue;
		}
		if (n >= strlen(s)) { printf("%s\n", s); continue; }
		if (n == 0) { printf("\n"); continue; }

		int up = 0;
		for (int j = n; s[j]; j++)
			if (isdigit(s[j])) {
				up = ('5' <= s[j] && s[j] <= '9');
				break;
			}
		if (!up) { s[n] = 0; printf("%s\n", s); continue; }

		s[n] = 0;
		int c = 1;
		for (i = n-1; c && i >= 0 && s[i]!='-'; i--) {
			if (!isdigit(s[i])) continue;
			if (s[i] == '9') { s[i]='0'; continue; }
			s[i]++;
			c = 0;
		}

		if (!c) { printf("%s\n", s); continue; }
		s[n-1] = 0;
		for (c = 0; c <= i; c++) putchar(s[c]);
		printf("1%s\n", s+c);
	}
}
