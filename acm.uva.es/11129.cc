// Main idea: generate permutations of the form: even numbers, 0, odd numbers.
// Recursively generate the even and odd numbers parts by generating
// a smaller antiarithmetic permutation and then replacing each
// term x by 2x+1 or 2x+2.
#include <cstdio>

// Generates an antiarithmetic permutation of {0,1,...,2^level-1},
// then replaces each term x by a*x+b and outputs those terms,
// which are not grater than lim.
void gen(int a, int b, int lim, int level) {
	if (level > 0) gen(2*a, 2*a+b, lim, level-1);
	if (b < lim) printf(" %d", b);
	if (level > 0) gen(2*a, a+b, lim, level-1);
}

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n > 0) {
		printf("%d:", n);
		gen(1,0,n,15);
		printf("\n");
	}
}
