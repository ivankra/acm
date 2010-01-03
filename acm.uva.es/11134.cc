#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Rook {
	int a, b, x, id;

	bool operator <(const Rook &other) const {
		return b < other.b;
	}
};

bool solve(Rook R[], int N) {
	sort(R, R+N);

	int used[5010];
	memset(used, 0, sizeof(used));

	for (int i = 0; i < N; i++) {
		R[i].x = 0;
		for (int x = R[i].a; x <= R[i].b; x++) {
			if (!used[x]) {
				R[i].x = x;
				used[x] = 1;
				break;
			}
		}

		if (R[i].x == 0) return false;
	}

	return true;
}

int main() {
	Rook X[5010], Y[5010];
	int N;

	while (scanf("%d", &N) == 1 && N > 0) {
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &X[i].a, &Y[i].a);
			scanf("%d %d", &X[i].b, &Y[i].b);
			if (X[i].a > X[i].b) swap(X[i].a, X[i].b);
			if (Y[i].a > Y[i].b) swap(Y[i].a, Y[i].b);
			X[i].id = Y[i].id = i;
			X[i].x = Y[i].x = 0;
		}
		
		if (!solve(X, N) || !solve(Y, N)) {
			printf("IMPOSSIBLE\n");
		} else {
			int x[5010], y[5010];

			for (int i = 0; i < N; i++) {
				x[X[i].id] = X[i].x;
				y[Y[i].id] = Y[i].x;
			}

			for (int i = 0; i < N; i++)
				printf("%d %d\n", x[i], y[i]);
		}
	}
}
