#include <cstdio>
#include <algorithm>
using namespace std;

long long a, b, c, d;
long double delta;

void find_c()
{
	c = (long long)( (a * (long double)d + delta * b * d) / b - 5 );
	while (c*b <= a*d) c++;
}

int main()
{
	while (scanf("%lld %lld %Lf", &a, &b, &delta) == 3) {
		{ long long g = __gcd(a, b); a /= g; b /= g; }

		for (d = 1;; d++) {
			find_c();
			if (c*b - a*d < delta*b*d+1e-15L) break;
		}
		printf("%lld %lld\n", c, d);
	}
}
