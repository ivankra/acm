#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
#define FOR(i,a,b) for(int i=(a),__FOR_B=(b);i<=__FOR_B;i++)
#define REP(i,n) FOR(i,0,(int)(n)-1)

void egcd(int a, int b, int &g, int &x, int &y) {
//	ax + by = g

	if (a < 0) { egcd(-a, b, g, x, y); x = -x; return; }
	if (b < 0) { egcd(a, -b, g, x, y); y = -y; return; }
	if (a < b) { egcd(b, a, g, y, x); return; }
	if (b == 0) { g = a; x = 1; y = 0; return; }

	egcd(b, a%b, g, y, x);
	y -= (a/b) * x;
}

int N, M, C[20], L[20], P[20];

int mod(int x, int m) {
	x %= m;
	return x<0 ? x+m : x;
}

bool ok() {
	for (int i = 0; i < N; i++) {
		for (int j = i+1; j < N; j++) {
			int a=mod(P[i]-P[j],M), b=mod(C[j]-C[i],M), g, x, y;
			if (b==0) return false;
			if (a==0) continue;
			egcd(a,M,g,x,y);
			if (mod(b, g) != 0) continue;
			x = mod(x*b/g, M/g);
			if (x <= L[i] && x <= L[j]) return false;

		}
	}
	return true;
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		REP(i,N) { scanf("%d %d %d", &C[i], &P[i], &L[i]); C[i]--; }
		M = 1 + *max_element(C, C+N);
		while (!ok()) M++;
		printf("%d\n", M);
	}
}
