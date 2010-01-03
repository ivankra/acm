#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <set>
using namespace std;

int main() {
	int a[1000], N;

	for (int cs = 1; scanf("%d", &N) == 1; cs++) {
		for (int i = 0; i < N; i++) scanf("%d", &a[i]);

		set<int> s;

		if (a[0] < 1) goto no;
		for (int i = 1; i < N; i++)if (a[i-1] >= a[i]) goto no;

		for (int i = 0; i < N; i++) {
			for (int j = i; j < N; j++) {
				if (s.count(a[i]+a[j]) > 0) goto no;
				s.insert(a[i]+a[j]);
			}
		}
				
		printf("Case #%d: It is a B2-Sequence.\n\n", cs);
		continue;
no:		printf("Case #%d: It is not a B2-Sequence.\n\n", cs);
		continue;
	}

	return 0;
}
