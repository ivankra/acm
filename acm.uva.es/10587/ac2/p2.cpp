#include <stdio.h>
#include <stdlib.h>
#include <set>
using namespace std;

#define N 16384
int L[N], R[N], A[N], n, m;
struct { int x, p; } ev[2*N];

int cmp(const void *p, const void *q) { return *(int *)p - *(int *)q; }

int main()
{
	int i, j, t;	
	set<int, greater<int> > S;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (m = 0, i = 1; i <= n && scanf("%d %d", &L[i],&R[i]) == 2; i++) {
			A[i] = 0; ev[m].x=L[i]; ev[m++].p=i;
			ev[m].x=R[i]+1; ev[m++].p=-i;
		}
		qsort(ev, m, sizeof(ev[0]), &cmp);
		S.clear();
		for (i = 0; i < m; i++) {
			if (ev[i].p>0) S.insert(ev[i].p); else S.erase(-ev[i].p);
			if (!S.empty() && (i==m-1 || ev[i+1].x!=ev[i].x)) A[*(S.begin())] = 1;
		}
		for (m = 0, i = 1; i <= n; i++) m += A[i];
		printf("%d\n", m);
	}
	return 0;
}
