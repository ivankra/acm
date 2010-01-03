#include <cstdio>
#include <set>
using namespace std;

int main()
{
	long long T, N, X;
	scanf("%lld", &T);

	for (int cs = 1; cs <= T && scanf("%lld %lld", &N, &X) == 2; cs++) {
		set<long long> better;
		better.insert(X);
		long long worse = 0;
		for (long long r = 1, t = X; r <= N; r++) {
			t &= ~((1 << r) - 1);
			better.insert(t);
			if (t == X) {
				worse = (1LL << r) - 1;
			}
		}
		printf("%lld %lld\n", (long long)better.size(), (1LL<<N)-worse);
	}
}
