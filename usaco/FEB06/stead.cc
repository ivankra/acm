/*
ID: infnty1
TASK: stead
LANG: C++
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

int N, B, barn[20], pref[1024][20], pref_low, pref_high;
int used[20], lused[20][1024], seen[1024], seen_id;

int aug(int cow) {
	if (seen[cow] == seen_id) return 0;
	seen[cow] = seen_id;

	for (int p = pref_low; p <= pref_high; p++) {
		int y = pref[cow][p];

		if (used[y] < barn[y]) {
			lused[y][used[y]++] = cow;
			return 1;
		}

		for (int yp = 0; yp < used[y]; yp++) {
			if (aug(lused[y][yp])) {
				lused[y][yp] = cow;
				return 1;
			}
		}
	}

	return 0;
}

int main()
{
	freopen("stead.in", "r", stdin);
	freopen("stead.out", "w", stdout);

	scanf("%d %d", &N, &B);
	assert(1 <= N && N <= 1000 && 1 <= B && B <= 20);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < B; j++) {
			scanf("%d", &pref[i][j]);
			pref[i][j]--;
		}
	}

	for (int i = 0; i < B; i++)
		scanf("%d", &barn[i]);

	memset(seen, 0, sizeof(seen));
	seen_id = 42;

	int diff;
	for (diff = 1; diff < B; diff++) {
		for (pref_low = 0; pref_low + diff <= B; pref_low++) {
			pref_high = pref_low + diff - 1;
			memset(used, 0, sizeof(used));
			for (int c = 0;; c++) {
				if (c >= N) goto done;
				seen_id++;
				if (!aug(c)) break;
			}
		}
	}
done:
	printf("%d\n", diff);

	return 0;
}
