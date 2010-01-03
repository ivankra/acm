#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 0x3fffffff

int M, K, H[1024], L[1024][20], best[1024];

bool can_jump(int tree, int y1, int y2) {
	int x1 = L[tree][y1], x2 = M-L[tree+1][y2];
	if ((y1-y2)*(y1-y2) + (x1-x2)*(x1-x2) > K*K) return false;

	for (int y = min(y1,y2)+1; y < max(y1,y2); y++) {
		long long xp = x1*(y2-y1)+(y-y1)*(x2-x1), xq = y2-y1;
		if (xq < 0) { xp = -xp; xq = -xq; }

		if (xp <= L[tree][y]*xq) return false;
		if (xp >= (M-L[tree+1][y])*xq) return false;
	}

	return true;
}

int main() {
	int N, T;
	scanf("%d", &T);

	while (T-- > 0) {
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < N; i++) {
			scanf("%d", &H[i]);
			for (int j = 0; j < H[i]; j++) scanf("%d", &L[i][j]);
			for (int j = H[i]; j < 20; j++) L[i][j] = 0;
		}

		best[N-1] = 0;
		for (int i = N-2; i >= 0; i--) {
			best[i] = M + best[i+1];
			for (int j = 0; j < H[i]; j++) {
				for (int k = 0; k < H[i+1]; k++) {
					int t = L[i][j] + L[i+1][k] + best[i+1];
					if (t < best[i] && can_jump(i,j,k))
						best[i] = t;
				}
			}
		}

		printf("%d\n", best[0]);
	}
}
