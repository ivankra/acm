#include <stdio.h>

static char p[1024];

int main(void)
{
	int n, c, s, w;

	scanf("%d\n", &n);
	while (n-- > 0) {
		for (s = 0, w = 0;;) {
			c = getchar();
			if (c == EOF || c == '\n') break;

			if (c == '(' || c == '[') {
				p[s++] = c;
				continue;
			}

			if (c == ')') {
				if (s == 0)
					w++;
				else if (p[--s] != '(')
					w++;
			}

			if (c == ']') {
				if (s == 0)
					w++;
				else if (p[--s] != '[')
					w++;
			}
		}
		if (s != 0) w++;

		printf(w ? "No\n" : "Yes\n");
	}

	return 0;
}
