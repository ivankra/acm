/*
ID: infnty1
TASK: cfair
LANG: C++
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N, P[410], T[410][512], F[410], C[410];
bool cmp(int a, int b) { return P[a] < P[b]; }

int main()
{
	freopen("cfair.in", "r", stdin);
	freopen("cfair.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &P[i]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &T[i][j]);

	for (int i = 0; i < N; i++)
		F[i] = (T[0][i] <= P[i]) ? 1 : -999999;

	for (int i = 0; i < N; i++) C[i] = i;
	sort(C, C+N, cmp);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < i; j++) {
			if (F[C[j]] < 0) continue;
			if (P[C[j]] + T[C[j]][C[i]] <= P[C[i]])
				F[C[i]] >?= F[C[j]] + 1;
		}
	}

	int best = 0;
	for (int i = 0; i < N; i++)
		best >?= F[i];
	printf("%d\n", best);

	return 0;
}

