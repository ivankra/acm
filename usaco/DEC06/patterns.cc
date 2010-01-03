/*
ID: infnty1
LANG: C++
TASK: patterns
*/
#define TASK "patterns"
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

int A[20010], S[20010], H[20010], Pos[50010], L[20010], N;
int phase;

int maxRepeats(int len) {
	int res = 0;
	int m = 0;
	for (int i = 0; i <= N; i++) {
		m++;
		res >?= m;
		if (L[i] < len) m = 0;
	}
	return res;
}

bool cmp1(int i, int j) { return A[i] < A[j]; }
bool cmp2(int i, int j) { return Pos[i+phase] < Pos[j+phase]; }

int main()
{
	freopen(TASK ".in", "r", stdin);
	freopen(TASK ".out", "w", stdout);

	int K;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) scanf("%d", &A[i]);

	S[0] = N;
	for (int i = 0; i <= N; i++) { S[i+1] = i; H[i] = 0; }
	for (int i = 0; i < sizeof(Pos)/sizeof(Pos[0]); i++) Pos[i] = -1;

	sort(S+1, S+N+1, cmp1);
	Pos[N] = 0;
	H[0] = 1;
	for (int i = 1; i <= N;) {
		int j;
		for (j = i; j <= N && A[S[i]] == A[S[j]]; j++)
			Pos[S[j]] = i;
		H[i] = j - i;
		i = j;
	}

	for (phase = 1; phase < N; phase *= 2) {
		for (int i = 0; i <= N;) {
			int m = H[i];
			sort(S+i, S+i+m, cmp2);

			for (int j = i; j < i+m;) {
				int k;
				for (k = j; k < i+m && Pos[S[j]+phase] == Pos[S[k]+phase]; k++);
				H[j] = k-j;
				j = k;
			}

			i += m;
		}

		for (int i = 0; i <= N; i += H[i])
			for (int j = 0; j < H[i]; j++)
				Pos[S[i+j]] = i;
	}

	L[Pos[N]] = 0;
	for (int i = 0; i < N; i++) {
		int t = Pos[i];
		if (t >= N) { L[t] = 0; continue; }

		int l = (i == 0 ? 0 : L[Pos[i-1]]);
		if (l > 0) l--;

		while (A[S[t]+l] == A[S[t+1]+l]) l++;
		L[t] = l;
	}

	int left = 0, right = N-1;
	while (left < right) {
		int mid = (left + right + 1) / 2;
		if (maxRepeats(mid) >= K) left = mid; else right = mid - 1;
	}
	printf("%d\n", left);
}
