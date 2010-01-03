#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
#define SIZE(x) int((x).size())
#define FOREACH(it, x) for(__typeof((x).begin())it=(x).begin();it!=(x).end();++it)
typedef long long LL;

LL a[3];

char *decide()
{
	sort(a, a + 3);
	if (a[2] > a[0] + a[1]) return "IMPOSSIBLE";
	if (a[2] == a[0] + a[1]) return "SINGULAR";
	if (a[0] * a[0] + a[1] * a[1] == a[2] * a[2]) return "RIGHT";
	if (a[0] * a[0] + a[1] * a[1] - a[2] * a[2] > 0) return "ACUTE";
	return "OBTUSE";
}

int main()
{
	cin >> a[0] >> a[1] >> a[2];
	printf("%s\n", decide());
}
