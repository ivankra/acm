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
	char s[1000];
	int a[1000], N, T;

	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf(" %d %s", &N, s);
		a[0] = 0;
		for (int n = 1; n <= N; n++) {
			a[n] = a[n-1];
			int sweet = 0;
			for (int m = 1; m <= n; m++) {
				sweet += (s[n-m] - '0');
				if (2*sweet > m) {
					a[n] = max(a[n], m + a[n-m]);
				}
			}
		}

		printf("%d\n", a[N]);
	}
}
