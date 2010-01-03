#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[1024];

int check()
{
	static struct Pal { int o, l; } p[2048];
	int n = strlen(s), m = 0;

	for (int i = 0; i+3 <= n; i++) {
		if (s[i]==s[i+2]) { p[m].o=i; p[m++].l=3; }
		if (s[i]==s[i+3] && s[i+1]==s[i+2]) { p[m].o=i; p[m++].l=4; }
	}

	for (int i = 0; i < m; i++)
		for (int j = i+1; j < m; j++) {
			int a = (p[i].l <= p[j].l) ? i : j;
			int b = (a == i) ? j : i;

			if (p[a].l == p[b].l) {
				if (memcmp(s+p[a].o, s+p[b].o, p[a].l) != 0)
					return 1;
				continue;
			}

			if (memcmp(s+p[a].o, s+p[b].o, 3) == 0) continue;
			if (memcmp(s+p[a].o, s+p[b].o+1, 3) == 0) continue;
			return 1;
		}

	return 0;
}

int main()
{
	while (scanf(" %[A-Z]", s) == 1)
		if (check()) printf("%s\n", s);
	return 0;
}
