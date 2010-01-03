/*
ID: infnty1
PROB: fence9
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int gcd(int a, int b) { return __gcd(abs(a), abs(b)); }

int main() {
	freopen("fence9.in", "r", stdin);
	freopen("fence9.out", "w", stdout);

	int n, m, p;
	scanf("%d %d %d", &n, &m, &p);

	int AA = m*p;
	int B = gcd(n,m) + gcd(m,p-n) + p;

	// Pick's theorem: A(rea)=B(oundary)/2+I(nternal)-1;
	printf("%d\n", (AA-B)/2+1);
}
