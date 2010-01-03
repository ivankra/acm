#include <algorithm>
#include <vector>
#include <sstream>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

int A[4][8192], S[16001000], T[16001000], N, K;

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 4; j++)
			scanf("%d", &A[j][i]);

	for (int j = 0; j < 4; j++)
		sort(A[j], A[j]+N);

	K = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			S[++K] = A[0][i] + A[1][j];

	K = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			T[++K] = A[2][i] + A[3][j];

	sort(S+1, S+K+1);
	sort(T+1, T+K+1);

	// sentinels
	S[0] = T[0] = -0x7FFFFFFF;
	S[K+1] = T[K+1] = 0x7FFFFFFF;

	long long res = 0;
	for (int i = 1, j = K; i <= K;) {
		int x = S[i], c = 1;
		for (i++; S[i] == x; i++, c++);

		x = -x;
		while (T[j] > x) j--;

		if (T[j] == x) {
			int d = 1;
			for (j--; T[j] == x; j--, d++);

			res += c * (long long)d;
		}
	}

	printf("%lld\n", res);
}
