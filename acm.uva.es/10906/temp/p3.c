#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char name[64][64];
int L[64], R[64], op[64], n;

void prn(int x)
{
	if (x < 0) x = -x;
	assert(1 <= x && x <= n);

	if (L[x] >= 0 && R[x] >= 0) {
		printf("%d%c%d", L[x], op[x], R[x]);
	} else if (L[x] >= 0) {
		printf("%d%c(", L[x], op[x]); prn(R[x]); printf(")");
	} else {
		if (op[x] == '*' && op[-L[x]] == '+')
			printf("("), prn(L[x]), printf(")");
		else
			prn(L[x]);

		if (R[x] >= 0)
			printf("%c%d", op[x], R[x]);
		else if (op[x] == '+' && op[-L[x]] == '*')
			printf("%c", op[x]), prn(R[x]);
		else
			printf("%c(", op[x]), prn(R[x]), printf(")");
	}
}

int get(char *s)
{
	int i;

	if ('0' <= s[0] && s[0] <= '9')
		return atoi(s);

	for (i = 1; i <= n; i++)
		if (strcmp(name[i], s) == 0) return -i;

	assert(1 == 0);
	return 0;
}

int main()
{
	static char s[256], sl[64][64], sr[64][64];
	int i, j, t, T;

	for (scanf("%d", &T), t = 1; t <= T && scanf("%d", &n) == 1; t++) {
		assert(n <= 60);
		for (i = 1; i <= n; i++) {
			j = scanf(" %[A-Za-z] = %[A-Za-z0-9] %[+*] %[A-Za-z0-9]",
				  name[i], sl[i], s, sr[i]);
			assert(j == 4 && (s[0] == '+' || s[0] == '*'));
			op[i] = s[0];
		}

		for (i = 1; i <= n; i++)
			L[i] = get(sl[i]), R[i] = get(sr[i]);

		printf("Expression #%d: ", t); prn(n); printf("\n");
	}

	return 0;
}
