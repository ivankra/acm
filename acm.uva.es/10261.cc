#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct State {
	int L, R;
	unsigned char bit[32];
};

int main()
{
	int T, x, m, n, seen[20000];

	scanf("%d", &T);
	while (T-- > 0 && scanf("%d", &m) == 1) {
		vector<State> A(1);
		memset(&A[0], 0, sizeof(State));

		memset(seen, 0xff, sizeof(seen));
		m *= 100;
		for (n = 0; scanf("%d", &x) == 1 && x != 0; n++) {
			vector<State> B;
			for (; A.size() > 0; A.pop_back()) {
				State &s = A.back();
				for (int k = 0; k < 2; k++) {
					State t = s;
					if (k == 0) {
						if (t.L + x > m) continue;
						t.L += x;
					} else {
						if (t.R + x > m) continue;
						t.R += x;
						t.bit[n>>3] |= 1 << (n&7);
					}

					if (seen[t.L] == n) continue;
					seen[t.L] = n;

					B.push_back(t);
				}
			}

			if (B.size() == 0) {
				while (scanf("%d", &x) == 1 && x != 0);
				break;
			}

			A = B;
		}

		printf("%d\n", n);
		State s = A[0];
		for (int i = 0; i < n; i++)
			printf((s.bit[i>>3] & (1<<(i&7))) ? "port\n" : "starboard\n");

		if (T) printf("\n");
	}
}
