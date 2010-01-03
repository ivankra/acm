#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
using namespace std;

int solve(int N) {
	int res = N;

	while (N >= 3) {
		int t = N / 3;
		N = N - 2*t;
		res += t;
	}

	if (N == 2) res++;

	return res;
}

int main()
{
	int N;
	while (scanf("%d", &N) == 1 && N > 0)
		printf("%d\n", solve(N));
}
