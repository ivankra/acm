#include <cstdio>
#include <cmath>
using namespace std;

bool check(long long N)
{
	long long x = 0;
	long long y = (int)(sqrt(N+1.0)+10);
	long long sum = x * x + y * y;

	while (x <= y) {
		if (sum == N)
			return true;
		else if (sum < N) {
			sum += x + x + 1;
			x++;
		} else {
			sum -= y + y - 1;
			y--;
		}
	}

	return false;
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		long long N;
		scanf("%lld", &N);
		printf(check(N) ? "Yes\n" : "No\n");
	}
}
