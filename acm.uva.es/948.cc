#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	int T;
	scanf("%d", &T);

	long long F[100]={1,1};
	for (int i = 2; i < 100; i++) F[i] = F[i-1] + F[i-2];

	for (int cs = 1; cs <= T; cs++) {
		int N;
		scanf("%d", &N);

		printf("%d = ", N);
		int i;
		for (i = 1; F[i] <= N; i++);
		i--;

		for (; i >= 1; i--) {
			if (N >= F[i]) { putchar('1'); N -= F[i]; } else { putchar('0'); }
		}
		printf(" (fib)\n");
	}
}
