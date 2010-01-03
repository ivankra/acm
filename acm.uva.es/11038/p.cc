/* C++ solution for problem 11038 - "How Many 0's" */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

// Returns the number of zeroes in decimal representation of 0, 1, ..., b.
// Complexity: linear in the number of decimal digits of b.
long long solve(long long b) {
	if (b < 0) return 0;

	// Compute decimal representation of b
	char s[20];
	sprintf(s, "%lld", b);
	int n = strlen(s);

	// Compute powers of 10
	long long ten[20] = { 1 };
	for (int n = 1; n < 20; n++)
		ten[n] = ten[n-1] * 10;

	// Compute suffixes of b.  suf[k] = atoll(s+k).
	long long suf[20];
	suf[n] = 0;
	for (int i = n-1; i >= 0; i--)
		suf[i] = suf[i+1] + (s[i] - '0') * ten[n-i-1];

	long long res = 1, pref = 0;
	for (int k = 1; k < n; k++) {
		pref = pref * 10 + (s[k-1] - '0');
		// pref is equal to integer, formed by first k digits of b.

		if (s[k] != '0')
			res += pref * ten[n-k-1];
		else
			res += (pref - 1) * ten[n-k-1] + suf[k+1] + 1;
	}
	return res;
}

int main() {
	long long m, n;
	while (scanf("%lld %lld", &m, &n) == 2 && m >= 0 && n >= 0) 
		printf("%lld\n", solve(max(m,n)) - solve(min(m,n)-1));
}
