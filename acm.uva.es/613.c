#include <stdio.h>
#include <string.h>

void apply(char *t, char *s)
{
	int c[16], i;

	for (i = 0; i < 10; i++)
		c[i] = 0;

	for (; *s; s++)
		c[*s - '0']++;

	for (i = 0; i < 10; i++) {
		if (c[i] != 0) {
			sprintf(t, "%u%d", c[i], i);
			while (*t) t++;
		}
	}
}

void solve(char *s0)
{
	static char s[20][1024];
	int i, k;

	strcpy(s[0], s0);

	for (k = 1; k <= 15; k++) {
		apply(s[k], s[k - 1]);

		if (strcmp(s[k], s[k - 1]) == 0) {
			if (k == 1)
				printf("%s is self-inventorying\n", s0);
			else
				printf("%s is self-inventorying after %d steps\n",
					s0, k - 1);
			return;
		}

		for (i = k - 1; i >= 0; i--) {
			if (strcmp(s[k], s[i]) != 0) continue;
			printf("%s enters an inventory loop of length %d\n",
				s0, k - i);
			return;
		}
	}

	printf("%s can not be classified after 15 iterations\n", s0);
}

int main()
{
	static char s[1024];

	while (scanf(" %[0-9]", s) == 1)
		solve(s);

	return 0;
}
