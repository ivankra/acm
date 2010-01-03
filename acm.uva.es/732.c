#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int stack[65536], top;
static char op[131072];

static void sol(char *p, char *q, int k)
{
	if (top == 0 && *q == '\0') {
		if (k == 0) { printf("\n"); return; }

		op[k - 1] = '\n';
		fwrite(op, 1, k, stdout);
		op[k - 1] = ' ';

		return;
	}

	if (*p != '\0') {
		stack[top++] = *p;
		op[k] = 'i';
		sol(p + 1, q, k + 2);
		top--;
	}

	if (top > 0 && stack[top - 1] == *q) {
		top--;
		op[k] = 'o';
		sol(p, q + 1, k + 2);
		stack[top++] = *q;
	}
}

void count(int r[], char *s)
{
	int i;

	for (i = 0; i < 26; i++)
		r[i] = 0;

	for (; *s; s++)
		if (isalpha(*s)) r[toupper(*s) - 'A']++;
}

int main()
{
	static char s1[65536], s2[65536];
	static int c1[32], c2[32];

	memset(op, ' ', sizeof(op));

	while (gets(s1) && gets(s2)) {
		count(c1, s1);
		count(c2, s2);

		if (memcmp(c1, c2, 26 * sizeof(int)) != 0) {
			printf("[\n]\n");
			continue;
		}

		printf("[\n");
		top = 0;
		sol(s1, s2, 0);
		printf("]\n");
	}

	return 0;
}
