#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

struct triple {
	int a, b, k;
};

bool operator <(const triple &A, const triple &B) {
	if (A.a != B.a) return A.a<B.a;
	if (A.b != B.b) return A.b<B.b;
	return A.k<B.k;
}

map<triple, int> memo;

int can(int a, int b, int k) {
	while (k >= 2 && (a % k) != 0 && (b % k) != 0) k--;
	if (a < b) swap(a, b);

	triple T={a,b,k};
	if (memo.count(T)>0) return memo[T];
	int &ret = memo[T];

	if (k < 2) return ret = (a == 1 && b == 1);

	return ret = (can(a, b, k-1) ||
		      (a % k == 0 && can(a/k, b, k-1)) ||
		      (b % k == 0 && can(a, b/k, k-1)));
}

int main()
{
	int a, b;
	while (scanf("%d %d", &a, &b) == 2) {
		if (a < b) swap(a, b);

		if (can(a,b,100) || !can(1,b,100))
			printf("%d\n", a);
		else
			printf("%d\n", b);		
	}
	return 0;
}
