#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int N, K;
int dist[1000];

bool check(int m)
{
	int k = 0;

	for (int i = 0, d = 0; i <= N; i++) {
		if (dist[i] > m)
			return false;

		if (d + dist[i] > m) {
			k++;
			d = 0;
		}

		d += dist[i];
	}

	return k <= K;
}

int main()
{
	while (scanf("%d %d", &N, &K) == 2 && N > 0) {
		for (int i = 0; i <= N; i++) scanf("%d", &dist[i]);

		int left = 0, right = 0;
		for (int i = 0; i <= N; i++) right += dist[i];

		while (right - left > 1) {
			int m = (left + right) / 2;
			if (check(m))
				right = m;
			else
				left = m;
		}

		printf("%d\n", right);
	}

	return 0;
}
