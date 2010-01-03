#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

struct Person {
	int id, t;
	bool operator <(const Person &b) const { return t < b.t; }
} p[1024];

int f[1024], N;

void main2() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &p[i].t);
		p[i].id = p[i].t;
	}
	sort(p, p+N);

	int a = p[0].t, b = p[1].t;
	f[0] = 0; f[1] = a; f[2] = b;

	for (int m = 3; m <= N; m++) {
		f[m] = p[m-1].t + a + f[m-1];
		if (m >= 4)
			f[m] = min(f[m], p[m-1].t + a + 2*b + f[m-2]);
	}

	printf("%d\n", f[N]);

	while (N >= 3) {
		if (f[N] == p[N-1].t + a + f[N-1]) {
			printf("%d %d\n%d\n", p[0].id, p[N-1].id, p[0].id);
			N--;
		} else {
			printf("%d %d\n%d\n", p[0].id, p[1].id, p[0].id);
			printf("%d %d\n%d\n", p[N-2].id, p[N-1].id, p[1].id);
			N -= 2;
		}
	}

	if (N == 2)
		printf("%d %d\n", p[0].id, p[1].id);
	else if (N == 1)
		printf("%d\n", p[0].id);
}

int main() {
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		main2();
		if (cs < T) printf("\n");
	}
}
