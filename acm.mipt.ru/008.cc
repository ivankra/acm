#include <cstdio>

int main() {
	int n = 0, c;
	while ((c = getchar()) != EOF) {
		if (c == '(') n++;
		else if (c == ')' && --n < 0) { n=1; break; }
	}
	printf(n ? "NO\n" : "YES\n");
}
