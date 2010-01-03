#include <cstdio>
#include <cassert>

int main() {
	int N, S=0;
	scanf("%d", &N);

	int *a = new int[N];
	for (int i = 0; i < N; i++) {
		scanf("%d", &a[i]);
		S += a[i];
	}

	bool *can = new bool[S+1];

	for (int i = 0; i <= S; i++) can[i] = false;
	can[0] = true;

	for (int i = 0; i < N; i++)
		for (int w = S; w >= a[i]; w--)
			can[w] |= can[w - a[i]];

	int best = S;
	for (int w = 0; w <= S && w <= S-w; w++)
		if (can[w]) best <?= S-2*w;
	printf("%d\n", best);

	return 0;
}
