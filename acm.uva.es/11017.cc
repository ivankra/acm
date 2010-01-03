#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

long long abs(long long x) { return x < 0 ? -x : x; }
void trans(long long &x, long long &y) { long long t=x-y; y=x+y; x=t; }

// I = (2A - B + 2) / 2
long long greenA, greenB, redA, redB;

void edge(long long x1, long long y1, long long x2, long long y2) {
	greenA += x1 * y2 - x2 * y1;
	greenB += __gcd(abs(x2-x1), abs(y2-y1));

	trans(x1, y1);
	trans(x2, y2);

	redA += x1 * y2 - x2 * y1;
	redB += __gcd(abs(x2-x1), abs(y2-y1));
}

int main() {
	int N, d, theta;
	int x0, y0, x1, y1, x2, y2;

	while (scanf("%d %d %d", &d, &theta, &N) == 3 && d > 0) {
		assert(N >= 3);

		greenA = greenB = redA = redB = 0;

		scanf(" %d %d", &x0, &y0);
		x1 = x0; y1 = y0;
		for (int i = 1; i < N; i++) {
			scanf(" %d %d", &x2, &y2);
			edge(x1, y1, x2, y2);
			x1 = x2; y1 = y2;
		}
		edge(x1, y1, x0, y0);

		long long greenI = (abs(greenA) - greenB + 2) / 2;
		long long redI = (abs(redA) - redB + 2) / 2;
		//printf("green=%lld  red+green=%lld\n", greenI, redI);

		double area = abs(greenA) / 2.0 * d * d * sin(theta*2*acos(0.0)/180.0);
		if (fabs(area - floor(area)) < fabs(area - ceil(area)))
			area = floor(area);
		else
			area = ceil(area);
		printf("%lld %.0f\n", redI - greenI, area);
	}
}
