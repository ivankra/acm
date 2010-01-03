#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n;
        scanf("%d", &n);

	vector<int> q, r;
	vector<bool> v(n+100, false);

	q.push_back(n);
	for (int dist = 0;;) {
		if (q.empty()) { dist++; q.swap(r); }

		n = q.back(); q.pop_back();
		if (n == 0) { printf("%d\n", dist); break; }

		if (!v[n-1]) { v[n-1]=true; r.push_back(n-1); }
		if (!v[n+1]) { v[n+1]=true; r.push_back(n+1); }
		if ((n&1)==0 && !v[n/2]) { v[n/2]=true; r.push_back(n/2); }
	}
}
