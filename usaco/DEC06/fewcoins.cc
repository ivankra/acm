/*
ID: infnty1
LANG: C++
TASK: fewcoins
*/
#define TASK "fewcoins"
#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

#define MONEY 30000
#define INF (1 << 30)

int N, T, V[128], C[128];
int shop[MONEY+1], john[MONEY+1];

int main()
{
	freopen(TASK ".in", "r", stdin);
	freopen(TASK ".out", "w", stdout);

	scanf("%d %d", &N, &T);
	for (int i = 0; i < N; i++) scanf("%d", &V[i]);
	for (int i = 0; i < N; i++) scanf("%d", &C[i]);

	shop[0] = 0;
	for (int n = 1; n <= MONEY; n++) {
		shop[n] = INF;
	}


}
