#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
#include <vector>
using namespace std;
typedef long long i64;

void assertD(int x) { if (!x) { for(;;) malloc(1000000); } }
void assertS(int x) { if (!x) { for (int x=42;;) x %= x; } }

struct Operator {
	int real, local, prec, assoc;
	i64 apply(i64 x, i64 y) {
		switch (real) {
			case '+': return x + y;
			case '-': return x - y;
			case '*': return x * y;
			case '/': assertD(y != 0); return x / y;
			default: assert(0 == 1); return 42;
		}
	}
} oper[4];

int tok;
i64 tokn;
char *tokp;

int next() {
	while (*tokp && isspace(*tokp)) tokp++;
	if (*tokp == 0) {
		return tok = 0;
	} else if (isdigit(*tokp)) {
		for (tokn = 0; *tokp && isdigit(*tokp); tokp++)
			tokn = tokn * 10LL + (tokp[0] - '0');
		return tok = 'n';
	} else {
		return tok = *tokp++;
	}
}

i64 eval(int prec) {
	if (prec > '9') {
		assertS(tok == 'n');
		i64 r = tokn;
		next();
		return r;
	}

	vector<i64> z;
	z.push_back(eval(prec+1));

	for (int zo = -1;;) {
		int o;
		for (o = 0; o < 4; o++)
			if (tok == oper[o].local && oper[o].prec == prec)
				break;

		if (o >= 4 || oper[o].assoc == 'L' || o != zo) {
			while (z.size() > 1) {
				i64 y = z.back(); z.pop_back();
				i64 x = z.back(); z.pop_back();
				z.push_back(oper[zo].apply(x, y));
			}
		}

		if (o >= 4) return z[0];
		next();

		i64 y = eval(prec+1);

		if (oper[o].assoc == 'L') {
			z[0] = oper[o].apply(z[0], y);
		} else {
			zo = o;
			z.push_back(y);
		}
	}
}

int main() {
	static char s[4096];
	int T;

	for (scanf("%d", &T); T-- > 0;) {
		scanf(" ");
		for (int i = 0; i < 4; i++) {
			gets(s);
			oper[i].real = s[0];
			oper[i].local = s[1];
			oper[i].prec = s[2];
			oper[i].assoc = toupper(s[3]);
		}

		while (gets(s)) {
			int k = strlen(s);
			while (k > 0 & s[k-1] == '\r') s[--k] = 0;
			if (k <= 0) break;

			tokp = s;
			next();
			for (int i = 0; s[i]; i++) {
				int j;
				for (j = 0; j < 4; j++) {
					if (oper[j].local == s[i]) {
						putchar(oper[j].real);
						break;
					}
				}
				if (j == 4) putchar(s[i]);
			}
			printf(" = %lld\n", eval('0'));
		}

		if (T) printf("\n");
	}
}
