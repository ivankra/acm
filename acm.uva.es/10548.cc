#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef long long L;

void gcdext(L &d, L &x, L &y, L a, L b) {
	if (a < 0) { gcdext(d, x, y, -a, b); x = -x; }
	else if (b < 0) { gcdext(d, x, y, a, -b); y = -y; }
	else if (a < b) { gcdext(d, y, x, b, a); }
	else if (b == 0) { d = a; x = 1; y = 0; }
	else { gcdext(d, y, x, b, a%b); y -= (a/b)*x; }
	assert(a*x + b*y == d);
}

L Floor(L x, L y) {
	if (y < 0) { x = -x; y = -y; }
	if (x >= 0) return x / y;
	return -((-x + y - 1) / y);
}

L Ceil(L x, L y) {
	if (y < 0) { x = -x; y = -y; }
	if (x >= 0) return (x + y - 1) / y;
	return -((-x) / y);
}

L solve(L a, L b, L c) {
	L d, x, y;
	gcdext(d, x, y, a, b);
	
	if ((c % d) != 0) return 0;
	x *= c/d;
	y *= c/d;

	L dx = b / d;
	L dy = -a / d;
	if (dx < 0) { dx = -dx; dy = -dy; }
	assert(dx > 0);

	if (dy > 0) return -1;

	a = Ceil(-x, dx);
	b = Floor(-y, dy);
	if (a > b) return 0;
	return b - a + 1;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		L a, b, c;
		scanf("%lld %lld %lld", &a, &b, &c);

		L res = solve(a, b, c);
		if (res > 0) printf("%lld\n", res);
		else if (res == 0) printf("Impossible\n");
		else printf("Infinitely many solutions\n");
	}
}
