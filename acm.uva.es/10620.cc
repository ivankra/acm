#include <cstdio>
#include <cstring>

unsigned seen[1<<18];

int main()
{
	int s, x, y, dx, dy;
	while (scanf("%d %d %d %d %d", &s, &x, &y, &dx, &dy) == 5 && s > 0) {
		memset(seen, 0, sizeof(seen));
		int moves = 0;
		for (;; moves++, x += dx, y += dy) {
			int xs=x%s, ys=y%s;
			if (xs != 0 && ys != 0 && ((x/s+y/s)&1)==1) {
				printf("After %d jumps the flea lands at (%d, %d).\n",
					moves, x, y);
				break;
			}

			int k = ((x%(2*s))<<11) | (y%(2*s));
			if ((seen[k>>5] >> (k&31)) & 1) {
				printf("The flea cannot escape from black squares.\n");
				break;
			}
			seen[k>>5] |= 1U << (k&31);
		}
	}
}
