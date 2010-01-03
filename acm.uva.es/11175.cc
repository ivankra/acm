#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int N, P, id[1024];

int ufind[1024];
int f(int x) {
	int z;
	for (z = x; ufind[z] != z; z = ufind[z]);
	while (x != z) { int y = ufind[x]; ufind[x] = z; x = y; }
	return z;
}

int main() {
	int T, P;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d %d", &N, &P) == 2; cs++) {
		N *= 2;
		for (int i = 0; i < N; i++) ufind[i] = i;

		int *edges0 = new int[P+10];

		for (int i = 0; i < P; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			edges0[i] = x * 65536 + y;
//printf("edge %d->%d [%d%d->%d%d] --> %d=%d\n", x,y, 2*x,2*x+1, 2*y,2*y+1, 2*x+1,2*y);
			x = 2 * x + 1;
			y = 2 * y;
			ufind[f(x)] = f(y);
		}

//		for (int i = 0; i < N; i += 2) printf("  %d: %d -> %d\n", i/2, f(i), f(i+1));

		int P1 = 0;
		int *edges1 = new int[P+10];

		for (int i = 0; i < N; i += 2) {
			for (int j = 0; j < N; j += 2) {
				if (f(i+1) != f(j)) continue;

				//printf("must exist edge %d->%d\n", i/2, j/2);
				edges1[P1++] = (i/2)*65536 + (j/2);
				if (P1 > P) goto stop;
			}
		}
stop:
		bool ans = true;
		if (P != P1) {
			ans = false;
		} else {
			sort(edges0, edges0+P);
			sort(edges1, edges1+P);
			if (memcmp(edges0, edges1, P*sizeof(int)) != 0) ans = false;
		}
		printf("Case #%d: %s\n", cs, ans ? "Yes" : "No");

		delete[] edges0;
		delete[] edges1;
	}
}
