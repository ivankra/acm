#include <cstdio>
#include <cstring>

int goal, left[256], S[256], top, opleft;

int doit() {
	if (top > opleft+1) return 0;
	if (top == 1 && S[top] == goal) return 1;

	if (top >= 2) {
		int a = S[top--]; int b = S[top--];
#define X(c,op) \
	if (left[c] > 0) { \
		left[c]--; opleft--; S[++top] = a op b; \
		if (doit()) return 1; \
		top--; left[c]++; opleft++; \
	}
		X('+',+) X('-',-) X('x',*)
#undef X
		S[++top] = b; S[++top] = a;
	}

	for (int d = '0'; d <= '9'; d++) {
		if (left[d] == 0) continue;
		left[d]--; S[++top] = d-'0';
		if (doit()) return 1;
		top--; left[d]++;
	}

	return 0;
}

int main()
{
	char buf[256];
	while (scanf(" %s %d", buf, &goal) == 2) {
		memset(left, 0, sizeof(left));
		for (int i = 0; buf[i]; i++) left[buf[i]]++;
		opleft = left['+'] + left['-'] + left['x'];
		top = 0;
		printf(doit() ? "solution\n" : "no solution\n");
	}
}
