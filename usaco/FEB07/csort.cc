/*
TASK: csort
ID: infnty1
LANG: C++
*/
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

int A[10010], B[10010], src[100100], dst[100100], N;
bool mark[10010];
long long answer = 0;

void fix(int s, bool first) {
	vector<int> cycle;
	long long minim = A[s], sum = 0;
	for (int x = s; !mark[x]; x = dst[A[x]]) {
		mark[x] = true;
		cycle.push_back(A[x]);
		minim = min(minim, (long long)A[x]);
		sum += A[x];
	}

	int k = cycle.size();

	if (k <= 1) return;

	if (first) {
		answer += sum + (k-2)*minim;
	} else {
		long long g = B[0];
		long long way1 = sum + (k-2)*minim;
		long long way2 = (sum+g) + (k-1)*g + (minim+g);
		answer += min(way1, way2);
	}

	for (int i = 0; i < k; i++)
		A[dst[cycle[i]]] = cycle[i];
}

int main()
{
	freopen("csort.in", "r", stdin);
	freopen("csort.out", "w", stdout);

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);

	for (int i = 0; i < N; i++) B[i] = A[i];
	sort(B, B+N);
	for (int i = 0; i < N; i++) src[A[i]] = i;
	for (int i = 0; i < N; i++) dst[B[i]] = i;

	memset(mark, 0, sizeof(mark));

	for (int i = 0; i < N; i++)
		if (A[i] == B[0]) fix(i, true);

	for (int i = 0; i < N; i++)
		if (!mark[i]) fix(i, false);

	printf("%lld\n", answer);
}
