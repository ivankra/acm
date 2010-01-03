#include <cstdio>
#include <cstring>

int expr[10000], st[10000], n=0, m, tok;

int eval(int x) {
	n = 0;
	for (int i = 0; expr[i] != 0; i++) {
		if (expr[i] < 0)
			st[n++] = (x >> (-expr[i] - 1)) & 1;
		else if (expr[i] == '&')
			n--, st[n-1] &= st[n];
		else if (expr[i] == '|')
			n--, st[n-1] |= st[n];
		else if (expr[i] == '!')
			st[n-1] ^= 1;
	}
	return st[n-1];
}

int next() {
	for (;;) {
		int c = getchar();
		if (c == EOF || strchr("!&|()", c) != NULL) return tok = c;
		if (c == 'x' || c == 'X') {
			int x;
			scanf(" %d", &x);
			return tok = -x;
		}
	}
}

void g_or();

void g_sub() {
	if (tok == '(') { next(); g_or(); if (tok==')') next(); }
	else if (tok == '!') { next(); g_sub(); expr[n++] = '!'; }
	else if (tok < 0) { expr[n++] = tok; next(); }
}

void g_and() { for (g_sub(); tok == '&';) { next(); g_sub(); expr[n++] = '&'; } }
void g_or() { for (g_and(); tok == '|';) { next(); g_and(); expr[n++] = '|'; } }

int main() {
	scanf("%d ", &m);
	next(); g_or(); expr[n++] = 0;

	for (int x = 0; x < (1 << m); x++) {
		if (!eval(x)) {
			printf("NO\n");
			for (int i = 0; i < m; i++)
				printf(i==0 ? "%d" : " %d", (x >> i) & 1);
			printf("\n");
			return 0;
		}
	}

	printf("YES\n");
	return 0;
}
