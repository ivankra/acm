#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<long long> a;
	int n, x;

	scanf("%d", &n);
	for (int i = 0; i < n && scanf("%d", &x) == 1; i++) a.push_back(x);
	sort(a.begin(), a.end());
	if (n > 6) a.erase(a.begin()+3, a.end()-3);
	n = a.size();

	long long best = a[0] * a[1] * a[2], p;
	for (int pass = 0;; pass++)
	for (int i = 0; i < n; i++)
	for (int j = i+1; j < n; j++)
	for (int k = j+1; k < n; k++) {
		p = a[i] * a[j] * a[k];
		if (pass && best == p) {
			printf("%lld %lld %lld\n", a[i], a[j], a[k]);
			return 0;
		} else {
			best >?= p;
		}
	}
}
