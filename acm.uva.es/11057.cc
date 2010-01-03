#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int a[20000], N, M;

int main() {
	for (int cs = 1; scanf("%d", &N) == 1; cs++) {
		set<int> s;
		for (int i = 0; i < N; i++) {
			scanf("%d", &a[i]);
			s.insert(a[i]);
		}
		sort(a, a+N);

		scanf("%d", &M);

		int best = 0;
		for (int i = 0; i < N; i++)
			if (M-a[i] >= a[i] && s.count(M-a[i]) > 0)
				best = a[i];
		printf("Peter should buy books whose prices are %d and %d.\n\n", best, M-best);
	}

	return 0;
}
