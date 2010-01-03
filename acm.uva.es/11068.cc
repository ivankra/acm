#include <cstdio>
#include <cmath>

int main() {
	int a1, b1, c1;
	int a2, b2, c2;

	while (scanf("%d %d %d %d %d %d", &a1,&b1,&c1,&a2,&b2,&c2)==6) {
		if ((a1|b1|c1)==0 || (a2|b2|c2)==0) break;

		int det = a1*b2-a2*b1;
		if (det == 0) {
			printf("No fixed point exists.\n");
			continue;
		}

		double x = (c1*b2-c2*b1)/(double)det;
		double y = (a1*c2-a2*c1)/(double)det;
		printf("The fixed point is at %.2f %.2f.\n", x+1e-9, y+1e-9);
	}
}
