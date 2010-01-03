#include <cstdio>
#include <cstring>
#include <cctype>

int main()
{
	char s[1024];
	int n = 0, c, m = 0;

	do {
		c = getchar();
		if (c != EOF && isalnum(c)) {
			s[n++] = c;
		} else if (n > 0) {
			s[n] = 0;

			int i = 0;
			if ((s[0] == '-' || s[0] == '+') && n > 1) i++;
			while (i < n && isdigit(s[i])) i++;
			if (i == n) m |= printf("%s\n", s);

			if (strcmp(s, "end") == 0) goto hell;

			n = 0;
		}
	} while (c != EOF);

hell:	if (m == 0) printf("nothing\n");
}
