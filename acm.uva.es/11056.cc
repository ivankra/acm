#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;

struct Pl {
	char name[200], low[200];
	long long t;
	bool operator <(const Pl &b) const {
		if (t != b.t) return t < b.t;
		return strcmp(low, b.low) < 0;
	}
} a[500];

void lwr(char *s) {
	int n = strlen(s);
	for (int i = 0; i < n; i++)
		s[i] = tolower(s[i]);
}

int main() {
	int N;

	for (int cs = 1; scanf("%d", &N) == 1 && N != 0; cs++) {
		assert(1 <= N && N <= 500);

		for (int i = 0; i < N; i++) {
			long long x,y,z;
			scanf(" %s ", a[i].name);

			strcpy(a[i].low, a[i].name);
			lwr(a[i].low);

			scanf(" %*[^0-9] "); scanf(" %lld ", &x);
			scanf(" %*[^0-9] "); scanf(" %lld ", &y);
			scanf(" %*[^0-9] "); scanf(" %lld ", &z); scanf(" ms ");
			a[i].t = (x*60LL+y)*1000LL+z;
		}

		sort(a, a+N);

		for (int i = 0, row = 1; i < N; i += 2, row++) {
			printf("Row %d\n", row);
			for (int j = 0; j < 2 && i+j < N; j++)
				printf("%s\n", a[i+j].name);
		}
		printf("\n");
	}
}
