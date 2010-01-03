#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef long long num;

char name[64][64];
num L[64], R[64];
int op[64], n;

void prn(int x)
{
	if (x < 0) x = -x;
	assert(1 <= x && x <= n);

	if (L[x] >= 0 && R[x] >= 0) {
		printf("%lld%c%lld", L[x], op[x], R[x]);
	} else if (L[x] >= 0) {
		if (op[x] == '+' && op[-R[x]] == '*')
			printf("%lld%c", L[x], op[x]), prn(R[x]);
		else
			printf("%lld%c(", L[x], op[x]), prn(R[x]), printf(")");
	} else {
		if (op[x] == '*' && op[-L[x]] == '+')
			printf("("), prn(L[x]), printf(")");
		else
			prn(L[x]);

		if (R[x] >= 0)
			printf("%c%lld", op[x], R[x]);
		else if (op[x] == '+' && op[-R[x]] == '*')
			printf("%c", op[x]), prn(R[x]);
		else
			printf("%c(", op[x]), prn(R[x]), printf(")");
	}
}

num get(char *s)
{
	int i;
	num r;

	assert(strlen(s) <= 10);

	if ('0' <= s[0] && s[0] <= '9') {
		for (r = 0; '0' <= s[0] && s[0] <= '9'; s++)
			r = r * 10 + (s[0] - '0');
		return r;
	}

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
