#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Box {
	ll a[3], b[3];

	ll volume() {
		return (b[0]-a[0]) * (b[1]-a[1]) * (b[2]-a[2]);
	}
};

Box isect(Box A, Box B)
{
	Box C = A;
	Box zero = { {0,0,0}, {0,0,0} };
	for (int i = 0; i < 3; i++) {
		C.a[i] = max(A.a[i], B.a[i]);
		C.b[i] = min(A.b[i], B.b[i]);
		if (C.a[i] >= C.b[i]) return zero;
	}
	return C;
}

int main()
{
	static ll sign[65536];
	Box box[20];
	int n;

	while (scanf("%d", &n) == 1 && n > 0) {
		for (int i = 0; i < n; i++) {
			scanf("%lld %lld %lld", &box[i].a[0], &box[i].a[1], &box[i].a[2]);
			scanf("%lld %lld %lld", &box[i].b[0], &box[i].b[1], &box[i].b[2]);
		}

		sign[0] = 1;
		for (int mask = 1; mask < (1 << n); mask++) {
			int i, j;
			sign[mask] = 0;

			for (i = 0; (mask & (1 << i)) == 0; i++);

			for (j = i+1; j < n; j++) {
				if (mask & (1 << j)) {
					sign[mask] -= sign[mask ^ (1 << i)];
					sign[mask] -= sign[mask ^ (1 << i) ^ (1 << j)];
				}
			}
		}


		long long res = 0;
		for (int mask = 1; mask < (1 << n); mask++) {
			Box b;
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				if (mask & (1 << i)) {
					b = (cnt == 0 ? box[i] : isect(b, box[i]));
					cnt++;
				}
			}

			res += sign[mask] * b.volume();
		}

		if (res < 0) res = -res;
		printf("%lld\n", res);
	}

	return 0;
}
