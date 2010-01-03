#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);
	if (n <= 1) { printf("0\n"); return 0; }

	for (int k = 1;; k++)
		if ((1<<(k+1))*(k+1)-1 >= n) { printf("%d\n", k); return 0; }
}
