#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cassert>
#include <set>
using namespace std;

int main()
{
	int N;
	scanf("%d", &N);

	char g;
	if (N < 72)
		g = "011203110332240522330113021104527401120311033224455233011302110453748112"[N];
	else
		g = "0311033224455933011302110453748112"[(N-72)%34];

	printf(g == '0' ? "Black\n" : "White\n");

/*
	const int MaxN = 1000;
	int g[MaxN+1];

	g[0] = 0;
	g[1] = 1;

	for (int N = 2; N <= MaxN; N++) {
		set<int> s;
		s.insert(g[N-2]);
		for (int a = 0; a <= N-3; a++)
			s.insert(g[a] ^ g[N-3-a]);

		g[N] = 0;
		while (s.count(g[N]) > 0) g[N]++;
	}

	for (int N = 0; N <= MaxN; N++)
		printf("%d", g[N]);
*/
}
