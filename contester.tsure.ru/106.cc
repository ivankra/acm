#include <cstdio>

int main()
{
	int x, y;
	scanf("%d %d", &x, &y);
	for (int b = 2; b <= 1000000; b++) {
		int xx=x, yy=y;
		for (; xx > 0; xx /= b)
			if ((xx % b) == (yy % b)) yy /= b;
		if (yy == 0) { printf("%d\n", b); return 0; }
	}
	printf("No solution\n");
}
