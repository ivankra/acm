#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
	int T, N, sum;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		if (cs != 1) printf("\n");

		scanf("%d %d", &N, &sum);

		int X = N*(N-1) - 2*sum;
		if (X < 0 || X % 4 != 0 || X > 2*N*(N-1)) {
			printf("No\n");
			continue;
		}
		X /= 4;

		sum = 0;
		printf("0\n");
		for (int i = N-1; i >= 1; i--) {
			if (X >= i) {
				X -= i;
				sum--;
			} else {
				sum++;
			}
			printf("%d\n", sum);
		}
		assert(X == 0);
	}
}
