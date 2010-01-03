#include <cstdio>

int main()
{
	int r, z=0;
	scanf(" %*d %*d %d", &r);
	for (int y = 0, x = r; y <= r; y++) {
		while (x*x+y*y > r*r) x--;
		z += x;
	}
	printf("%d\n", 4*z+1);
}
