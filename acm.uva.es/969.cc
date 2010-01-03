/* Solution: by applying Laws 1 and 2, any expression can be transformed to
   one without the 'i' and 'k' operators.  This program does it simultaneously
   with parsing.  What remains is just to compare the resulting expressions.
   
   The program below implements a linear-time algorithm.
   Parsed expressions are internally stored as a binary tree.
   0-th node represents "0", all other nodes represent operator "t". */
#include <cstdio>
#include <cassert>
#include <cctype>

#define NODES 2001000     // more than enough for strings of size up to 1000000

int left[NODES], right[NODES], N;
int t(int l, int r) { N++; left[N] = l; right[N] = r; return N; }

// reads next non-whitespace character
int next(int expect = -1) {
	for (;;) {
		int c = getchar();
		assert(c != EOF);
		if (!isspace(c)) {
			if (expect != -1) assert(c == expect);
			return c;
		}
	}
}

// reads an expression and transforms it to a form with only 0's and t's
int read() {
	int c = next();
	if (c == '0') return 0;

	int res;

	next('(');
	if (c == 'i') {
		res = read();
	} else if (c == 't') {
		int x = read();
		next(',');
		int y = read();
		res = t(x, y);
	} else {
		assert(c == 'k');
		int x = read();
		next(',');
		int y = read();
		res = t(y, t(x, 0));
	}
	next(')');
	return res;
}

// compares two expression trees
int eq(int x, int y) {
	if (x == 0 || y == 0)
		return x == 0 && y == 0;
	else
		return eq(left[x], left[y]) && eq(right[x], right[y]);
}

int main() {
	int T;
	for (scanf("%d", &T); T-- > 0;) {
		N = 0;
		printf(eq(read(), read()) ? "true" : "false");
	}
}
