#include <cstdio>

int main() {
	double S, Vjohn, Vmary, Vdog;
	scanf("%lf %lf %lf %lf", &S, &Vjohn, &Vmary, &Vdog);
	printf("%.4f\n", (Vdog * S) / (Vjohn + Vmary));
}
