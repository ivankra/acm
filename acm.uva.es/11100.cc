#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int a[10010], N, K;
vector<int> bag[10010];

int main() {
	for (int cs = 1; scanf("%d", &N) == 1 && N > 0; cs++) {
		for (int i = 0; i < N; i++) scanf("%d", &a[i]);
		sort(a, a+N);

		K = 0;
		for (int i = 1, c = 1; i < N; i++) {
			c = (a[i] == a[i-1] ? c+1 : 1);
			K = max(K, c);
		}

		for (int i = 0; i < K; i++)
			bag[i].clear();

		for (int i = 0, j = 0; i < N; i++) {
			bag[j].push_back(a[i]);
			if (++j == K) j = 0;
		}

		if (cs > 1) printf("\n");
		printf("%d\n", K);
		for (int i = 0; i < K; i++) {
			for (int j = 0; j < (int)bag[i].size(); j++)
				printf(j==0 ? "%d" : " %d", bag[i][j]);
			printf("\n");
		}
	}
}
