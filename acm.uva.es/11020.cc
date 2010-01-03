#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

void relabel(int *x, int n) {
	vector<int> v(x, x+n);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	map<int, int> m;
	for (int i = 0; i < (int)v.size(); i++) m[v[i]] = i;
	for (int i = 0; i < n; i++) x[i] = m[x[i]];
}

struct Node {
	int a, b, c;
};

map<int, Node> S;
int total;

void prn() { return;
/*printf("set:");
for (map<int, Node>::iterator it = S.begin(); it != S.end(); it++)
  printf(" (a=%d,b=%d:%d)",it->second.a, it->second.b, it->second.c);
printf("\n");*/

}

void update(int new_a, int new_b) {
	if (S.count(new_a) > 0) {
		Node &r = S[new_a];
		if (new_b > r.b) return;
		if (new_b == r.b) { r.c++; total++; return; }
		total -= r.c;
		r.b = new_b;
		r.c = 1;
		total += r.c;
	} else {
		Node n = { new_a, new_b, 1 };
		S[new_a] = n;
		total++;
	}
prn();
	map<int, Node>::iterator i, j;

	for (i = S.find(new_a); i != S.end();) {
		j = i; j++;
		if (j == S.end()) break;
		if (i->second.b <= j->second.b) {
			total -= j->second.c;
			S.erase(j);
		} else {
			break;
		}
	}

	for (i = S.find(new_a); i != S.begin(); i = j) {
		j = i; j--;
		if (j->second.b <= i->second.b) {
			total -= i->second.c;
			S.erase(i);
		} else {
			break;
		}
	}
prn();
}

int main()
{
	int N, T, A[15010], B[15010];
	scanf("%d", &T);
	for (int cs = 1; cs <= T && scanf("%d", &N) == 1; cs++) {
		for (int i = 0; i < N; i++) scanf("%d %d", &A[i], &B[i]);
		relabel(A, N);
		relabel(B, N);

		printf("%sCase #%d:\n", cs==1?"":"\n", cs);

		S.clear();
		total = 0;

		for (int i = 0; i < N; i++) {
			update(A[i], B[i]);
			printf("%d\n", total);
		}
	}
}
