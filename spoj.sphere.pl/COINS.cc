#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <map>
using namespace std;

map<int, long long> memo;

long long f(int n) {
	if (n <= 11) return n;

	if (memo.count(n) == 0)
		memo[n] = f(n/2) + f(n/3) + f(n/4);

	return memo[n];
}

int main()
{
	int n;
	memo.clear();
	while (scanf("%d", &n) == 1)
		printf("%lld\n", f(n));
}
