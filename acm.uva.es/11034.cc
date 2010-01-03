#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int T, L, N;
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &L, &N) == 2;) {
		L *= 100;

		vector<int> v(N+1, 0);
		char s[100];
		for (int i = 0, x; i < N && scanf("%d %s", &x, s); i++)
			v[i] = (s[0] == 'l') ? x : -x;

		int where=0, left=0, right=0, fit=0, res=0;

		for (;;) {
			while (left < N && v[left] < 0) left++;
			while (right < N && v[right] > 0) right++;

			if (left >= N && right >= N && fit == 0) break;

			if (where == 0 && left < N && fit + v[left] <= L) {
				fit += v[left++];
				continue;
			}

			if (where == 1 && right < N && fit - v[right] <= L) {
				fit -= v[right++];
				continue;
			}

			res++;
			where ^= 1;
			fit = 0;
		}

		printf("%d\n", res);
	}
}
