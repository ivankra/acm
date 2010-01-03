#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 1000010
char sieve[MAX+10];
int next[MAX+10];

int main()
{
	memset(sieve, 0, sizeof(sieve));
	sieve[0] = sieve[1] = 1;
	for (int i = 2; i*i <= MAX; i++) {
		if (sieve[i] == 0) {
			for (int j = i*i; j <= MAX; j += i)
				sieve[j] = 1;
		}
	}

	next[MAX+1] = MAX+1;
	for (int i = MAX; i >= 0; i--)
		next[i] = (sieve[i] == 0 ? i : next[i+1]);

	int T;
	scanf("%d", &T);

	int low, up;
	while (T-- > 0 && scanf("%d %d", &low, &up) == 2) {
		vector<int> diff;
		for (int p = next[low], q;; p = q) {
			q = next[p+1];
			if (q > up) break;
			diff.push_back(q-p);
		}

		sort(diff.begin(), diff.end());

		int best = -1, best_cnt = 0;
		int i, j, m = diff.size();
		for (i = 0; i < m;) {
			for (j = i+1; j < m && diff[i] == diff[j]; j++);

			if (j-i > best_cnt) {
				best = diff[i];
				best_cnt = j-i;
			} else if (j-i == best_cnt) {
				best = -1;
			}

			i = j;
		}

		if (best < 0) {
			printf("No jumping champion\n");
		} else {
			printf("The jumping champion is %d\n", best);
		}
	}

	return 0;
}
