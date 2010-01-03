#include <stdio.h>
#include <string.h>

int tok;

int next() {
	for (;;) {
		int c = getchar();
		if (c == EOF) return (tok = EOF);
		if ('a' <= c && c <= 'z') return (tok = c);
		if (strchr("+-*/^()", c) != NULL) return (tok = c);
	}
}

void go(int level) {
	if (level == 3) {
		if ('a' <= tok && tok <= 'z') {
			putchar(tok);
			next();
		} else if (tok == '(') {
			next();
			go(0);
			if (tok == ')') next();
		}
	} else {
		go(level+1);
		while (tok == "+*^"[level] || tok == "-/^"[level]) {
			int c = tok;
			next();
			go(level+1);
			putchar(c);
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t); next();
	while (t-- > 0) {
		go(0);
		printf("\n");
	}
	return 0;
}
