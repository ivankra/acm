#include <cstdio>
#include <cstring>

#define MAX 1000010
int a[MAX+10], semi[MAX+10];

int main() {
	memset(a, 0, sizeof(a));
	for (int i = 5; i*i <= MAX; i += 4) {
		if (a[i] == 0) {
			for (int j = i+i; j <= MAX; j += i)
				a[j] = i;
		}
	}

	// a[i] = 0, if i is prime; else a[i] is some prime divisor of i.

	memset(semi, 0, sizeof(semi));
	for (int i = 5; i <= MAX; i += 4) {
		semi[i] = semi[i-4];
		if (a[i] != 0 && a[i/a[i]] == 0)
			semi[i]++;
	}

	int h;
	while (scanf("%d", &h) == 1 && h > 0)
		printf("%d %d\n", h, semi[h]);
}
