#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;

int perm[200100], rev[200100], ans[200100], tmp[600000], N, S;

int sum(int b) {
	if (b < 0) return 0;

	int res = tmp[b+S];
	for (b += S; b >= 1; b /= 2)
		if (b & 1) res += tmp[b-1];
	return res;
}

void erase(int x) {
	x += S;
	tmp[x] = 0;
	while (x > 1) { x /= 2; tmp[x] = tmp[2*x] + tmp[2*x+1]; }
}

int main() {
	while (scanf("%d", &N) == 1 && N > 0) {
		memset(perm, 0, sizeof(perm));
		for (int i = 0; i < N; i++) { scanf("%d", &tmp[i]); tmp[i]--;}
		for (int i = 0; i < N; i++) { int x; scanf("%d", &x); perm[tmp[i]] = x-1; }
		for (int i = 0; i < N; i++) rev[perm[i]] = i;

		for (S = 1; S < N+10; S *= 2);
		memset(tmp, 0, sizeof(int)*(S+S+10));
		for (int i = 0; i < N; i++) tmp[S+i] = 1;
		for (int i = S-1; i >= 1; i--) tmp[i] = tmp[2*i] + tmp[2*i+1];

		int left = 0;
		for (int k = N-1; k > 0; k--) {
			int pos = rev[k];
			int val = (left + sum(pos-1)) % (k+1);

			ans[k] = (k-val) % (k+1);
			if (ans[k] < 0) ans[k] += k+1;

			//printf("k=%d: left=%d pos=%d val=%d  ans=%d\n", k, left, pos, val, ans[k]);

			erase(pos);

			left = (left + ans[k]) % (k+1);
			if (left == k) left = 0;
		}

		printf("0");
		for (int i = 1; i < N; i++) printf(" %d", ans[i]);
		printf("\n");
	}
}
