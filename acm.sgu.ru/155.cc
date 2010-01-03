#include <cstdio>
#include <algorithm>
using namespace std;

struct Pair {
	int key, aux, id, left, right, up;
	bool operator <(const Pair &p) const { return key < p.key; }
};

Pair a[50010];

int main() {
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a[i].key, &a[i].aux);
		a[i].id = i;
		a[i].left = a[i].right = a[i].up = 0;
	}
	sort(a+1, a+n+1);

	for (int i = 2; i <= n; i++) {
		for (int z = i-1;;) {
			if (a[z].aux < a[i].aux) {
				a[i].left = a[z].right;
				a[a[i].left].up = i;
				a[z].right = i;
				a[i].up = z;
				break;
			}
			if (a[z].up == 0) {
				a[i].left = z;
				a[z].up = i;
				break;
			}
			z = a[z].up;
		}
	}

	int old[50010];
	for (int i = 1; i <= n; i++)
		old[a[i].id] = i;

	printf("YES\n");
	for (int i = 1; i <= n; i++) {
		int j = old[i];
		printf("%d %d %d\n", a[a[j].up].id, a[a[j].left].id, a[a[j].right].id);
	}
}
