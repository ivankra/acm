#include <cstdio>

void A(int a, int b) {
	printf("sin(%d",a);
	if (a != b) { putchar((a&1)?'-':'+'); A(a+1,b); }
	putchar(')');
}

void S(int a, int b) {
	if (a > 1) { putchar('('); S(a-1,b+1); putchar(')'); }
	A(1,a); printf("+%d", b);
}

int main(int n) { scanf("%d",&n); S(n,1); printf("\n"); }
