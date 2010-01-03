#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;


int main()
{
	int T;
	scanf("%d", &T);

	for (int cs = 1; cs <= T; cs++) {
		int N, who;
		scanf("%d %d",&N, &who);
		printf(who == 0 ? "Airborne wins.\n" : "Pagfloyd wins.\n");
	}
}
