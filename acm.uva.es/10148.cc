#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

struct Segment {
	int a, b;

	bool operator <(const Segment &other) const {
		if (b != other.b) return b < other.b;
		return a < other.a;
	}
};

int N, K, out[20100];
Segment S[1024];

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		scanf("%d %d", &K, &N);
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &S[i].a, &S[i].b);
			if (S[i].a > S[i].b)
				swap(S[i].a, S[i].b);
			S[i].a += 10005;
			S[i].b += 10005;
			assert(1 <= S[i].a && S[i].b <= 20005);
		}

		vector<int> res;
		memset(out, 0, sizeof(out));
		sort(S, S+N);

		for (int i = 0; i < N; i++) {
			int a = S[i].a, b = S[i].b;

			int c = min(K, b-a+1);
			for (int x = a; x <= b; x++)
				if (out[x]) c--;

			for (a = b; c > 0; a--) {
				if (out[a] == 0) {
					c--;
					res.push_back(a);
					out[a] = 1;
				}
			}
		}

		sort(res.begin(), res.end());

		printf("%d\n", res.size());
		for (int i = 0; i < (int)res.size(); i++)
			printf("%d\n", res[i] - 10005);
		if (cs != T) printf("\n");
	}
}
