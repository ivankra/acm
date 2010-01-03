#include <stdio.h>
#include <stdlib.h>
#include <set>
using namespace std;

int cmp(const void *p, const void *q) { return *(int *)p-*(int *)q; }

#define N 10100
struct { int x, e; } ev[2*N];

int main()
{
	int l[N], r[N], a[N], i, t, n, m;
	set<int, greater<int> > S;

	for (scanf("%d", &t); t-- > 0 && scanf("%d", &n) == 1;) {
		for (m = 0, i = 1; i <= n && scanf("%d %d", &l[i], &r[i]) == 2; i++) {
			a[i]=0; ev[m].x=l[i]; ev[m++].e=i;
			ev[m].x=r[i]+1; ev[m++].e=-i;
		}
		qsort(ev, m, sizeof(ev[0]), &cmp); S.clear();
		for (i = 0; i < m; i++) {
			if (ev[i].e>0) S.insert(ev[i].e); else S.erase(-ev[i].e);
			if (!S.empty() && (i==m-1 || ev[i+1].x!=ev[i].x))
				a[*(S.begin())]=1;
		}
		for (m = 0, i = 1; i <= n; i++) m += a[i];
		printf("%d\n", m);
	}
	return 0;
}

