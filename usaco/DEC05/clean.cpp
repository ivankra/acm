/*
TASK: clean
ID: infnty1
LANG: C++
*/
/* Algorithm: dynamic programming
   Uses a binary tree (implemented by stl's set) to achieve O(E-M + N log N) time */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
#include <set>
using namespace std;
typedef long long i64;

struct thingy { i64 key; int id; };
bool operator <(const thingy &a, const thingy &b) {
	return (a.key < b.key) || (a.key == b.key && a.id < b.id);
}

struct job {
	int T1,T2;
	i64 S;
	int flag, next_t1, next_t2;  /*linked lists of jobs with same T1's and T2's*/
	set<thingy>::iterator it;
} J[16384];

int N, M, E, list_t1[100000], list_t2[100000];
i64 f[100000];
set<thingy> W;

int main()
{
	int i, j;

	freopen("clean.in", "r", stdin);
	freopen("clean.out", "w", stdout);

	scanf("%d %d %d", &N, &M, &E);
	assert(1<=N&&N<=10000 && 0 <= M && M <= E && E <= 86399);
	for (i = 1; i <= N; i++) {
		scanf("%d %d %lld", &J[i].T1, &J[i].T2, &J[i].S);
		assert(M <= J[i].T1 && J[i].T1 <= J[i].T2 && J[i].T2 <= E);
	}

	memset(list_t1, 0, sizeof(list_t1));
	memset(list_t2, 0, sizeof(list_t2));
	for (i = 1; i <= N; i++) {
		J[i].next_t1 = list_t1[J[i].T1]; list_t1[J[i].T1] = i;
		J[i].next_t2 = list_t2[J[i].T2]; list_t2[J[i].T2] = i;
	}

	f[E+1] = 0;

	for (i = 1; i <= N; i++) J[i].flag = 0;

	W.clear();
	for (i = E; i >= M; i--) {
		for (j = list_t2[i]; j != 0; j = J[j].next_t2) {
			thingy x={J[j].S+f[i+1], j};
			J[j].flag = 1;
			J[j].it = W.insert(x).first;
		}

		if (W.size() == 0) break;

		f[i] = W.begin()->key;

		for (j = list_t1[i]; j != 0; j = J[j].next_t1)
			if (J[j].flag) { W.erase(J[j].it); J[j].flag=0; }
	}

	if (i >= M)
		printf("-1\n");
	else
		printf("%lld\n", f[M]);

	return 0;
}
