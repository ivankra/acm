#include <cstdio>
#include <set>
using namespace std;

int main()
{
	set<int> s;
	int n, x;
	for (scanf("%d", &n); n-- > 0 && scanf("%d", &x) == 1;)
		s.insert(x);
	for (scanf("%d", &n); n-- > 0 && scanf("%d", &x) == 1;)
		if (s.count(333333-x)>0) { printf("YES\n"); return 0; }
	printf("NO\n");
}
