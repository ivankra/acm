#include <cstdio>

int main()
{
	int n, m, p;
	scanf("%d %d %d", &n, &m, &p);
	printf("%d\n", p*(n-(n/m)));
}
