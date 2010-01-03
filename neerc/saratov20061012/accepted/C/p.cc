#include <cstdio>
#include <cstring>

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int N, M;
	int hp[50], score[50];

	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++) {
		hp[i] = 100;
		score[i] = 0;
	}

	for (int i = 0; i < M; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (hp[x] <= 0) continue;

		if (hp[y] > 0) score[x] += 3;
		hp[y] -= 8;
	}

	for (int i = 1; i <= N; i++) {
		if (hp[i] > 0) score[i] += hp[i] / 2;
	}

	for (int i = 1; i <= N; i++)
		printf("%d %d\n", hp[i], score[i]);

	return 0;
}