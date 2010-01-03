#include <cstdio>
#include <cstdlib>
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
	int N, K;
	cin >> N >> K;

	unsigned long long a[32][32];
	memset(a, 0, sizeof(a));
	a[2][1] = a[3][1] = 1;

	for (int n = 4; n <= N; n++) {
		a[n][1] = 1;
		for (int k = 2; k <= K; k++) {
			a[n][k] = 2 * a[n-1][k-1] + a[n-1][k];
			for (int s = 3; s <= n-2; s++)
				for (int l = 1; l <= k-1; l++)
					a[n][k] += (a[s][l-1] + a[s][l]) * a[n-s+1][k-l];
		}
	}

	cout << a[N][K] << endl;
}
