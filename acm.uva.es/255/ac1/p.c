#include <stdio.h>

static int between(int x, int a, int b)
{
	return ((a < b) ? (a < x && x < b) : (b < x && x < a));
}

int main()
{
	static int k, q, p;

	while (scanf("%d %d %d", &k, &q, &p) == 3) {
		if (k < 0 || k > 63 || q < 0 || q > 63 || k == q) {
			printf("Illegal state\n");
			continue;
		}

		if (p < 0 || p > 63 || p == k || p == q) {
			printf("Illegal move\n");
			continue;
		}

		if ((q / 8) == (p / 8)) {
			/* row move */
			if ((k / 8) == (p / 8) &&
			    between(k % 8, p % 8, q % 8)) {
				printf("Illegal move\n");
				continue;
			}
		} else if ((q % 8) == (p % 8)) {
			/* column move */
			if ((k % 8) == (p % 8) &&
			    between(k / 8, p / 8, q / 8)) {
				printf("Illegal move\n");
				continue;
			}
		} else {
			printf("Illegal move\n");
			continue;
		}

		if (((k % 8) != 7 && (k + 1) == p) ||
		    ((k % 8) != 0 && (k - 1) == p) ||
		    (k + 8) == p || (k - 8) == p) {
			printf("Move not allowed\n");
			continue;
		}

		if ((k ==  0 && p ==  9) || (k ==  7 && p == 14) ||
		    (k == 56 && p == 49) || (k == 63 && p == 54))
			printf("Stop\n");
		else
			printf("Continue\n");
	}

	return 0;
}
