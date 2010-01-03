#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

void pos_of(int &x, int &y, int n)
{
	n--;

	int left = 1, right = 50000;
	while (right - left > 1) {
		long long m = (left + right) / 2;
		long long t = 4 * m * (m - 1) - 2 * (m - 1);
		if (t <= n)
			left = m;
		else
			right = m;
	}

	int m = left, t;
	y = m-1; x = -(m-1);
	n -= 4*m*(m-1)-2*(m-1);
	m = 2 * m - 1;

	t = min(m, n); x += t; n -= t;
	t = min(m, n); y -= t; n -= t;
	m++;
	t = min(m, n); x -= t; n -= t;
	t = min(m, n); y += t; n -= t;
}

int num_at(int x0, int y0)
{
	if (x0 == 0 && y0 == 0) return 1;

	long long r = max(abs(x0), abs(y0));
	long long n = (2*r-1)*(2*r-1)+1;
	long long x = r, y = r-1;
	r = 2*r-1;

	for (int i = 0; i < 4; i++) {
		long long dx = "1012"[i] - '1';
		long long dy = "0121"[i] - '1';

		long long k = 0;
		if (dx != 0) k = (x0 - x) / dx;
		if (dy != 0) k = (y0 - y) / dy;

		if (x + dx * k == x0 && y + dy * k == y0 && 0 <= k && k < r) {
			return n + k;
		}

		x += dx * r;
		y += dy * r;
		n += r;

		if (i == 0 || i == 2) r++;
	}

	return -1;
}

int main()
{
	int n;

	while (scanf("%d", &n) == 1 && n > 0) {
		int x, y;
		pos_of(x, y, n);

		for (int dy = -1; dy <= 1; dy++) {
			for (int dx = -1; dx <= 1; dx++)
				printf("%d;", num_at(x+dx, y-dy));
			printf("\n");
		}
	}

	return 0;
}
