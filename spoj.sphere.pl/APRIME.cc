#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int N, M, D;
int seq[2000], used[2000];

bool isPrime[50000];

int rec(int pos) {
	if (pos == M-N+1)
		return 1;

	for (int x = N; x <= M; x++) {
		if (used[x]) continue;

		if (pos >= 1) {
			int s = x;
			for (int k = 2; k <= D; k++) {
				s += seq[pos-k+1];
				if (isPrime[s]) goto bad;
			}
		}

		seq[pos] = x;
		used[x] = 1;
		if (rec(pos+1)) return 1;
		used[x] = 0;

bad:;
	}

	return 0;
}

int main()
{
	for (int n = 0; n < 50000; n++)
		isPrime[n] = true;
	isPrime[0] = isPrime[1] = false;

	for (int i = 2; i * i < 50000; i++) {
		if (isPrime[i]) {
			for (int j = i * i; j < 50000; j += i)
				isPrime[j] = false;
		}
	}

	while (scanf("%d %d %d", &N, &M, &D) == 3 && N > 0) {
		memset(used, 0, sizeof(used));
		if (rec(0)) {
			for (int i = 0; i < M-N+1; i++)
				printf(i == 0 ? "%d" : ",%d", seq[i]);
			printf("\n");
		} else {
			printf("No anti-prime sequence exists.\n");
		}
	}
}
