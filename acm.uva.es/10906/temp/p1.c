#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct { char name[32], sl[32], sr[32]; int L, R, op, f; } z[64];
char E[64][8192];
int n;

char *expand(int x)
{
	if (z[x].f) return E[x];
	z[x].f = 1;

	if (z[x].L >= 0 && z[x].R >= 0) {
		sprintf(E[x], "%d%c%d", z[x].L, z[x].op, z[x].R);
	} else if (z[x].L >= 0) {
		sprintf(E[x], "%d%c(%s)", z[x].L, z[x].op, expand(-z[x].R));
	} else {
		if (z[x].op == '*' && z[-z[x].L].op == '+')
			sprintf(E[x], "(%s)", expand(-z[x].L));
		else if (z[x].op == z[-z[x].L].op && z[-z[x].L].R < 0)
			sprintf(E[x], "(%s)", expand(-z[x].L));
		else
			sprintf(E[x], "%s", expand(-z[x].L));

		if (z[x].R >= 0)
			sprintf(E[x]+strlen(E[x]), "%c%d", z[x].op, z[x].R);
		else if (z[x].op == '+' && z[-z[x].L].op == '*')
			sprintf(E[x]+strlen(E[x]), "%c%s", z[x].op, expand(-z[x].R));
		else
			sprintf(E[x]+strlen(E[x]), "%c(%s)", z[x].op, expand(-z[x].R));
	}

	return E[x];
}

int get(char *s)
{
	int i;

	if ('0' <= s[0] && s[0] <= '9')
		return atoi(s);

	for (i = 1; i <= n; i++)
		if (strcmp(z[i].name, s) == 0) return -i;

	assert(1 == 0);
	return 0;
}

int main()
{
	static char s[256];
	int i, j, t, T;

	for (scanf("%d", &T), t = 1; t <= T && scanf("%d", &n) == 1; t++) {
		assert(n <= 60);
		for (i = 1; i <= n; i++) {
			j = scanf(" %[A-Za-z] = %[A-Za-z0-9] %[+*] %[A-Za-z0-9]",
				  z[i].name, z[i].sl, s, z[i].sr);
			assert(j == 4 && (s[0] == '+' || s[0] == '*'));
			z[i].op = s[0];
		}

		for (i = 1; i <= n; i++) {
			z[i].f = 0;
			z[i].L = get(z[i].sl);
			z[i].R = get(z[i].sr);
		}

		printf("Expression #%d: %s\n", t, expand(n));
	}

	return 0;
}
