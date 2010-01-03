#include <cstdio>
#include <algorithm>
using namespace std;

int N, P[400], T[400][512], F[400], P[400], o[400];
bool cmp(int a, int b) { return P[a] < P[b]; }

int main()
{
	freopen("cfair.in", "r", stdin);
	freopen("cfair.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", &P[i]);
	for (int i = 0; i < N*N; i++) scanf("%d", &T[i/N][i%N]);
	for (int i = 0; i < N; i++) { o[i] = i; F[i] = (T[0][i] <= P[i]); }
	sort(o, o+N, cmp);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < i; j++)
			if (F[o[j]] > 0 && P[o[j]] + T[o[j]][o[i]] <= P[o[i]])
				F[o[i]] >?= F[o[j]] + 1;
	printf("%d\n", *max_element(F, F+N));
	return 0;
}
