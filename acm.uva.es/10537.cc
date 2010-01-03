#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <map>
using namespace std;

typedef long long L;
const L INF = 1LL << 62;

char name(int x) { return x < 26 ? 'A'+x : ('a'+x-26); }
int get() {
	char c;
	scanf(" %c", &c);
	if (isupper(c)) return c-'A';
	return c-'a'+26;
}

int main()
{
	int adj[52][52], nroads;
	for (int cs = 1; scanf("%d", &nroads) == 1 && nroads >= 0; cs++) {
		 memset(adj, 0, sizeof(adj));
		 for (int i = 0; i < nroads; i++) {
			 int x = get(), y = get();
			 adj[x][y] = adj[y][x] = 1;
		 }

		 L cost_dst;
		 scanf("%lld", &cost_dst);

		 int src = get();
		 int dst = get();

		 L cost[52];
		 for (int i = 0; i < 52; i++) cost[i] = INF;
		 cost[dst] = cost_dst;

		 bool seen[52];
		 for (int i = 0; i < 52; i++) seen[i] = false;

		 for (;;) {
			 int x = -1;
			 for (int i = 0; i < 52; i++)
				 if (!seen[i] && (x < 0 || cost[i] < cost[x])) x = i;
			 if (x < 0 || cost[x] == INF) break;

			 seen[x] = true;

			 for (int y = 0; y < 52; y++) {
				 if (!adj[x][y]) continue;
				 L c = cost[x];
				 if (x < 26) c = (20*c + 18) / 19; else c++;
				 if (c < cost[y]) cost[y] = c;
			 }
		 }

		 printf("Case %d:\n", cs);
		 printf("%lld\n", cost[src]);

		 L have = cost[src];
		 while (src != dst) {
			 printf("%c-", name(src));

			 for (int y = 0; y < 52; y++) {
				 if (!adj[src][y]) continue;

				 L c = have;
				 if (y < 26) c -= (c+19)/20; else c--;

				 if (c >= cost[y]) {
					 have = c;
					 src = y;
					 break;
				 }
			 }
		 }
		 printf("%c\n", name(dst));
	}
}
