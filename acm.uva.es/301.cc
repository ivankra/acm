#include <cstdio>
#include <cstring>

int N, best, use[50], sum[50];
struct Order { int a, b, c; } ord[50];

void doit(int k, int earn) {
	best >?= earn;
	if (k < 0 || earn + sum[k+1] <= best) return;

	doit(k-1, earn);

	int A=ord[k].a, B=ord[k].b, C=ord[k].c;
	for (int i = A; i < B; i++)
		if (use[i] + C > N) return;

	for (int i = A; i < B; i++) use[i] += C;
	doit(k-1, earn + (B-A)*C);
	for (int i = A; i < B; i++) use[i] -= C;
}

int main() {
	int M, K;
	while (scanf("%d %d %d", &N, &M, &K) == 3) {
		if ((N|M|K)==0) break;

		for (int i = 0; i < K; i++)
			scanf("%d %d %d", &ord[i].a, &ord[i].b, &ord[i].c);

		sum[0] = 0;
		for (int i = 0; i < K; i++)
			sum[i+1] = sum[i] + (ord[i].b - ord[i].a) * ord[i].c;

		best = 0;
		memset(use, 0, sizeof(use));
		doit(K-1, 0);

		printf("%d\n", best);
	}
}
