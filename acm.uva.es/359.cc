#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

#define MAX 65536

int p[MAX][2], s[MAX], n, ok;
VVI H;

void col(int x) {
	if (s[x] == 0) s[x] = 1;
	for (int i = 0; ok && i < (int)H[x].size(); i++) {
		int y = H[x][i];
		if (s[y] == 0) {
			s[y] = 3 - s[x];
			col(y);
		} else if (s[y] != 3 - s[x]) {
			ok = 0;
		}		
	}
}

void acyc(int x) {
	if (s[x]) {
		ok &= (s[x] == 1);
	} else if (ok) {
		s[x] = 2;
		for (int i = 0; i < 2 && p[x][i] > 0; i++)
			acyc(p[x][i]);
		s[x] = 1;
	}
}

int main()
{
	for (int cs=1,m,x,y; scanf("%d %d", &n, &m) == 2; cs++) {
		assert(0 <= n && n <= MAX-10);
		ok = 1;
		for (int i = 1; i <= n; i++) p[i][0]=p[i][1]=0;

		while (m-- > 0 && scanf("%d %d", &x, &y) == 2) {
			assert(1<=x&&x<=n && 1<=y&&y<=n);
			if (x == y) { ok=0; continue; }
			if (p[y][0] == x || p[y][1] == x) {
				ok=0;          /*????*/
				continue;
			}

			if (p[y][0] == 0) p[y][0] = x;
			else if (p[y][1] == 0) p[y][1] = x;
			else ok = 0;	
		}

		memset(s, 0, sizeof(int)*(n+1));
		for (int i = 1; ok && i <= n; i++)
			acyc(i);

		if (ok) {
			H = VVI(n+1, VI());
			for (int i = 1; i <= n; i++)
				if (p[i][0] > 0 && p[i][1] > 0) {
					H[p[i][0]].push_back(p[i][1]);
					H[p[i][1]].push_back(p[i][0]);
				}

			memset(s, 0, sizeof(int)*(n+1));
			for (int i = 1; ok && i <= n; i++)
				col(i);
		}

		printf("Graph number %d is %ssexy\n", cs, ok?"":"not ");
	}
}
