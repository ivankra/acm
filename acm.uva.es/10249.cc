#include <cstdio>
#include <algorithm>
using namespace std;

struct Pair {
	int x, y;
	bool operator <(const Pair &p) const { return x < p.x; }
};

int main() {
	Pair a[100], b[100];
	int out[100][100], cnt[100], m, n;

	while (scanf("%d %d", &m, &n) == 2 && m > 0 && n > 0) {
		for (int i = 0; i < m; i++) {
			scanf("%d", &a[i].x);
			a[i].y = i;
			cnt[i] = a[i].x;
		}

		for (int i = 0; i < n; i++) {
			scanf("%d", &b[i].x);
			b[i].y = i+1;
		}

		sort(a, a+m);

		for (int i = m-1; i >= 0; i--) {
			sort(b, b+n);
			int k = 0, j;
			for (j = n-1; j >= 0 && b[j].x > 0 && k < a[i].x; j--, k++) {
				b[j].x--;
				out[a[i].y][k] = b[j].y;
			}
			if (k < a[i].x && (j < 0 || b[j].x == 0)) goto fail;
		}

		printf("1\n");
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < cnt[i]; j++)
				printf(j ? " %d" : "%d", out[i][j]);
			printf("\n");
		}
		continue;

fail:		printf("0\n");
	}
}
