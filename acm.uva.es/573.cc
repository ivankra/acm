#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	int H, U, D, F;
	while (scanf("%d %d %d %d", &H, &U, &D, &F) == 4 && H > 0) {
		for (int day = 1, now = 0;; day++) {
			now += max(0, U * (100 - F*(day-1)));
			if (now > H*100) {
				printf("success on day %d\n", day);
				break;
			}
			now -= D*100;
			if (now < 0) {
				printf("failure on day %d\n", day);
				break;
			}
		}
	}
}
