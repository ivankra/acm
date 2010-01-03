#include <cstdio>

int main() {
	int A, B, C, d;
	while (scanf("%d %d %d %d", &A, &B, &C, &d) == 4) {
		d += 12;

		for (int t1 = 0; t1 <= 1; t1++)
		for (int t2 = 0; t2 <= 1; t2++) 
		for (int t3 = 0; t3 <= 1; t3++) {
			int a=A+t1, b=B+t2, c=C+t3;
			if (a+b != c) continue;

			if ((a+c+d)%3 != 0) continue;
			int x = (a + c + d) / 3;
			int y = x - a;
			int z = y - b;

			if (x < y || y < z || x+y+z != d) continue;

			printf("%d %d %d\n", x, y, z);
			goto done;
		}
done:;
	}
}
