#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

long long ten[20], suf[16];
char bound[16];

long long solve(long long n) {
	if (n < 0) return 0;
	if (n == 0) return 1;

	sprintf(bound, "%lld", n);
	int len = strlen(bound);

	suf[len] = 0;
	for (int i = len-1; i >= 0; i--)
		suf[i] = suf[i+1] + (bound[i] - '0') * ten[len-i-1];

	long long ret = 1, z = bound[0] - '0';
	for (int pos = 1; pos < len; pos++) {
		if (bound[pos] != '0')
			ret += z * ten[len-pos-1];
		else
			ret += (z-1) * ten[len-pos-1] + suf[pos+1] + 1;
		z = z * 10 + bound[pos] - '0';
	}
	return ret;
}

int main() {
	ten[0] = 1;
	for (int i = 1; i < 20; i++) ten[i] = ten[i-1] * 10LL;

	long long m, n;
	while (scanf("%lld %lld", &m, &n) == 2 && m >= 0 && n >= 0) 
		printf("%lld\n", solve(max(m,n)) - solve(min(m,n)-1));
}
