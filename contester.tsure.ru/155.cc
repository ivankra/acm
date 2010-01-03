#include <cstdio>
#include <cstring>
using namespace std;
typedef long long i64;

char expr[1024], *tok;
struct { int op, pos; i64 num; } pf[1024];
int pfn;
i64 goal, st[1024];

int doit(int p, int stn) {
	while (pf[p].op == 0)
		st[++stn] = pf[p++].num;

	if (p >= pfn) {
		if (stn != 1) return 0;
		return (st[1] == goal);
	}

	if (stn < 2 || stn > 11) return 0;

	i64 a = st[stn-1], b = st[stn];

	if (pf[p].op == '+') {
		st[stn-1] = a + b;
		if (doit(p+1, stn-1)) {
			expr[pf[p].pos] = '+';
			return 1;
		}
		st[stn-1] = a - b;
		if (doit(p+1, stn-1)) {
			expr[pf[p].pos] = '-';
			return 1;
		}
	} else {
		st[stn-1] = a * b;
		if (doit(p+1, stn-1)) {
			expr[pf[p].pos] = '*';
			return 1;
		}
		if (b != 0) {
			st[stn-1] = a / b;
			if (doit(p+1, stn-1)) {
				expr[pf[p].pos] = '/';
				return 1;
			}
		}
	}
	st[stn-1] = a;
	st[stn] = b;
	return 0;
}

void term();

void prim() {
	if (*tok == '(') {
		tok++;
		term();
		if (*tok == ')') tok++;
	} else {
		int m;
		sscanf(tok, "%lld%n", &pf[pfn].num, &m);
		tok += m;
		pf[pfn++].op = 0;
	}
}

void fact() {
	prim();
	while (*tok == '*') {
		char *s = tok++;
		prim();
		pf[pfn].op = *s;
		pf[pfn++].pos = s-expr;
	}	
}

void term() {
	fact();
	while (*tok == '+') {
		char *s = tok++;
		fact();
		pf[pfn].op = *s;
		pf[pfn++].pos = s-expr;
	}	
}

int main()
{
	gets(expr);
	sscanf(strchr(expr, '='), "=%lld", &goal);

	int n = 0;
	for (char *p = expr; *p && *p != '='; p++)
		n += (*p == '?');

	for (int m = 0; m < (1 << n); m++) {
		for (int i = 0, k = 0; expr[i] != '='; i++)
			if (strchr("+*-/?", expr[i]))
				expr[i] = "+*#"[(m >> k++) & 1];

		tok = expr;
		pfn = 0;
		term();
		pf[pfn].op = -1;

		if (doit(0, 0)) {
			printf("%s\n", expr);
			return 0;
		}
	}

	printf("No solution.\n");
}
