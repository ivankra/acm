#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> VI;  typedef vector<VI> VVI;

bool cmp(const VI &a, const VI &b) { return a.size() < b.size(); }

int main() {
	int a[2500], b[2500], u[2500], n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	memset(b, 0, sizeof(b));
	memset(u, 0, sizeof(u));

	VVI C;

	for (int i = 1; i <= n; i++) {
		if (u[i]) continue;
		C.push_back(VI());
		for (int j = i; u[j] == 0; j = a[j]) {
			u[j] = 1;
			C.back().push_back(j);
		}
	}

	sort(C.begin(), C.end(), cmp);

	for (int i = 0; i < (int)C.size();) {
		VI r;

		if (C[i].size() % 2 == 1) {
			VI c = C[i++];
			r = VI(c.size(), 0);
			for (int k = 0; k < (int)c.size(); k++)
				r[(2*k)%c.size()] = c[k];
		} else if (i+1 < (int)C.size() && C[i].size() == C[i+1].size()) {
			VI x = C[i++], y = C[i++];
			for (int k = 0; k < (int)x.size(); k++) {
				r.push_back(x[k]);
				r.push_back(y[k]);
			}
		} else {
			printf("0\n");
			return 0;
		}

		for (int j = 0; j < (int)r.size(); j++)
			b[r[j]-1] = r[(j+1)%r.size()];
	}

	for (int i = 0; i < n; i++)
		printf(i+1<n ? "%d " : "%d\n", b[i]);
}
