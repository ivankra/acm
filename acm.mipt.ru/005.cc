#include <cstdio>
#include <cctype>

double tree() {
	int c;
	double x;

	while ((c = getchar()) != EOF) {
		if (c == '(') return (tree() + tree()) / 2.0;
		if (isdigit(c) || c == '-') {
			ungetc(c, stdin);
			scanf("%lf", &x);
			return x;
		}
	}
	return 0;
}

int main() {
	printf("%.2f\n", tree());
}
