/*
ID: infnty1
PROB: msquare
LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

int ten[10]={1};

int Get(int x, int n) { return (x / ten[7-n]) % 10; }
int Set(int n, int x) { return x * ten[7-n]; }

int main() {
	for (int i = 1; i < 10; i++) ten[i] = ten[i-1] * 10;

	freopen("msquare.in", "r", stdin);
	freopen("msquare.out", "w", stdout);

	int goal = 0, start = 0;
	for (int i = 0; i < 8; i++) {
		int x;
		scanf("%d", &x);
		goal += Set(i, x);
		start += Set(i, i+1);
	}

	int s[] = { 87654321, 41236785, 17245368 };

	map<int, int> dist, prev, prev_c;
	int q[50000], *qh = q, *qt = q;
	dist[*qt++ = start] = 0;
        while (qh < qt) {
        	int x = *qh++;
        	for (int i = 0; i < 3; i++) {
        		int y = 0;
        		for (int j = 0; j < 8; j++)
        			y += Set(j, Get(x, Get(s[i],j)-1));
			if (dist.count(y) > 0) continue;
			dist[y] = dist[x] + 1;
			prev[y] = x;
			prev_c[y] = 'A'+i;
                        *qt++ = y;
		}
	}

	if (dist.count(goal) == 0) {
		printf("impossible\n");
		return 0;
	}

	char path[50000];
	int n = 0;

	for (int x = goal; x != start; x = prev[x])
		path[n++] = prev_c[x];
	reverse(path, path+n);
	path[n] = 0;

	printf("%d\n", n);
	for (int k = 0; k < n; k += 60)
		printf("%.60s\n", path+k);
	if(n==0)printf("\n");
}
