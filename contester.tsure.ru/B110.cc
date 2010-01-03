#include <cstdio>
#include <cstring>

char s1[65536], s2[65536];

int G(char *s) {
	memset(s, 0, 65536);
	gets(s);
	int n = strlen(s);
	while (n > 0 && (s[n-1]=='\r' || s[n-1]=='\n'))
		s[--n] = 0;
	return n;
}

int main() {
	int n = G(s1);
	int m = G(s2);

	if (m == 0) { printf("%s\n", s1); return 0; }

	char *p, *q;
	while ((p = strstr(s1, s2)) != NULL) {
		for (q = p+m; *q;) *p++ = *q++;
                *p = 0;
	}

	printf("%s\n", s1);
}
