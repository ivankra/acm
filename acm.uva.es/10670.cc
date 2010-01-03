#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int a[100010];

int main()
{
	int T, cs=1, N, M, L, A, B;
	char name[256];
	for (scanf("%d", &T); cs <= T && scanf("%d %d %d", &N, &M, &L) == 3; cs++) {
		printf("Case %d\n", cs);
		vector<pair<int, string> > R;
		while (L-- && scanf(" %[A-Za-z] : %d , %d", name, &A, &B) == 3) {
			a[N] = a[M] = 0;
			for (int i = M+1; i <= N; i++) {
				a[i] = A + a[i-1];
				if ((i >> 1) >= M) a[i] <?= B + a[i >> 1];
			}
			R.push_back(pair<int, string>(a[N], string(name)));
		}
		sort(R.begin(), R.end());
		for (int i = 0; i < R.size(); i++)
			printf("%s %d\n", R[i].second.c_str(), R[i].first);
	}
	return 0;
}
