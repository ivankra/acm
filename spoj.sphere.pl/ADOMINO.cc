#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
	static int x[100001];
	int T, N, D;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &N, &D);
		for (int i = 0; i < N; i++)
			scanf("%d", &x[i]);
		sort(x, x + N);

		int left = 0, right = x[N-1] - x[0] + 10;
		while (right - left > 1) {
			int mid = (left + right) / 2;
			int canPlace = 1, last = x[0];
			for (int i = 1; i < N; i++) {
				if (x[i] - last >= mid) {
					canPlace++;
					last = x[i];
				}
			}

			if (canPlace >= D)
				left = mid;
			else
				right = mid;
		}

		printf("%d\n", left);
	}
}
