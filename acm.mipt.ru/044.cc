#include <cstdio>

int ok(int x, int y, int a) {
	if (a <= 1) return 1;
	if (a > x || a > y) return 0;

	if ((2*x+2*y-4)%a != 0) return 0;

	if ((x-1)%a == 0) {
		if ((y-1)%a == 0) return 1;
		if (y%a == 0 && (y-2)%a == 0) return 1;
	} else if (x%a == 0) {
		if ((y-2)%a == 0) return 1;
		if ((x-2)%a == 0 && (y-1)%a == 0) return 1;
	} else if ((x-2)%a == 0) {
		if (y%a == 0) return 1;
	}

	return 0;

}

int main() {
	int x, y, a, n;
	scanf("%d %d %d", &x, &y, &n);
	while (n-- > 0 && scanf("%d", &a) == 1)
		printf((ok(x,y,a) || ok(y,x,a)) ? "YES\n" : "NO\n");
}