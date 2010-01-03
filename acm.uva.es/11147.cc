#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long A[10000], S[10000];
int N;

void rec(int a, int b) {
	if (a > b) return;

	if (a == b) {
		printf("%lld", A[a]);
		return;
	}

	int best = a;
	long long bestDiff = 1<<30, bestLeft = 0;

	for (int r = a; r <= b; r++) {
		if (r < b && A[r+1] == A[r]) continue;
		long long L = S[r] - S[a], R = S[b+1] - S[r+1];
		long long diff = L-R;
		if (diff < 0) diff = -diff;
		if (diff < bestDiff || (diff == bestDiff && L > bestLeft)) {
			best = r;
			bestDiff = diff;
			bestLeft = L;
		}
	}

	printf("%lld(", A[best]);
	rec(a, best-1);
	if (a != best && best != b)
		printf(",");
	rec(best+1, b);
	printf(")");
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) scanf("%lld", &A[i]);

		sort(A, A+N);

		S[0] = 0;
		for (int i = 1; i <= N; i++)
			S[i] = S[i-1] + A[i-1];

		printf("Case #%d: ", cs);
		rec(0, N-1);
		printf("\n");
	}
}
