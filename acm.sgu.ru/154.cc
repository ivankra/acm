#include <cstdio>

int f(int n) {
	int res = 0;
	for (int i = 0; i < 20; i++)
		res += (n /= 5);
	return res;
}

int main()
{
	int q;
	scanf("%d", &q);

	int left = 1, right = 5*q+10;
	while (right > left) {
		int c = (left + right) / 2;
		if (f(c) < q)
			left = c+1;
		else
			right = c;
	}

	if (f(left) == q)
		printf("%d\n", left);
	else
		printf("No solution\n");

	return 0;
}
