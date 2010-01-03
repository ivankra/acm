#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int A[100010], N, K, P;

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d %d", &N, &K, &P);

		A[0] = 0;
		for (int i = 1; i <= N; i++) {
			scanf("%d", &A[i]);
			A[i] = (A[i-1] + A[i]) % P;
		}

		set<int> s;
		int best = P;
		for (int i = N; i >= 0; i--) {
			int x = A[i];
			set<int>::iterator it = s.lower_bound(x + K);
			if (it != s.end()) {
				int y = *it;
				best = min(best, y - x);
			}
			s.insert(x);
			s.insert(x + P);
		}
		printf("%d\n", best);
	}
}

