#include <cstdio>
#include <cstring>
#include <cctype>

char *tokp;
int tok;
double tokv;

int next() {
	for (;;) {
		if (*tokp == 0) return tok = 0;
		if (strchr("+-*/", *tokp) != NULL) return tok = *tokp++;
		if (isdigit(*tokp) || *tokp=='.') {
			int m;
			sscanf(tokp, "%lf%n", &tokv, &m);
			tokp += m;
			return tok = 'n';
		}
		tokp++;
	}
}

double fact() {
	double sign = 1;
	for (;;) {
		if (tok == '+') { next(); }
		else if (tok == '-') { next(); sign *= -1; }
		else if (tok == 'n') { sign *= tokv; next(); return sign; }
		else if (tok == 0) return 0;
		else next();
	}
}

double term() {
	double a = fact();
	for (;;) {
		if (tok == '*') { next(); a *= fact(); }
		else if (tok == '/') { next(); a /= fact(); }
		else return a;
	}
}

double expr() {
	double a = term();
	for (;;) {
		if (tok == '+') { next(); a += term(); }
		else if (tok == '-') { next(); a -= term(); }
		else return a;
	}
}

int main() {
	static char buf[65536];
	while (gets(buf)) {
		tokp = buf;
		next();
		printf("%.3f\n", expr());
	}
}
