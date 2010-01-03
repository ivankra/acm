#include <cstdio>
#include <algorithm>
using namespace std;

struct Seg { int a, b, c; } S[1024];
int Z[65536], n;
bool operator <(const Seg &s, const Seg &t) { return s.b<t.b; }

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d %d", &S[i].a, &S[i].b, &S[i].c);
	sort(S, S+n);

	int ret = 0;
	for (int i = 0; i < n; i++) {
		int p = 0;
		for (int x = S[i].a; x <= S[i].b; x++)
			p += Z[x];
		for (int x = S[i].b; x >= S[i].a && p < S[i].c; x--)
			if (!Z[x]) { Z[x] = 1; p++; ret++; }
	}

	printf("%d\n", ret);
}
