#include <cstdio>

int A[100], N, S;

int can(int i, int s) {
	if (s == S) return 1;
	if (i >= N) return 0;
	return can(i+1, s) || can(i+1, s+A[i]);
}

int main() {
	while (scanf("%d %d", &N, &S) == 2 && N > 0) {
		for (int i = 0; i < N; i++)
			scanf("%d", &A[i]);
		printf(can(0, 0) ? "Yes\n" : "No\n");
	}

}
