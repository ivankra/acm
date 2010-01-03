#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS	1e-7
#define A(R,C)	a[(R)*2*n+(C)]

int main()
{
	double *a;
	int i, j, k, n;

	while (scanf("%d", &n) == 1 && n > 0) {
		a = (double *)malloc(2 * n * n * sizeof(double));
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				scanf("%lf", &A(i,j));
				A(i,n+j) = (i == j) ? 1. : 0.;
			}
		}

		for (k = 0; k < n; k++) {
			if (fabs(A(k,k)) < EPS) break;

			for (j = 0; j < k; j++) A(k,j) = 0.;
			for (j = k+1; j < 2*n; j++) A(k,j) /= A(k,k);
			A(k,k) = 1.;

			for (i = 0; i < n; i++) {
				if (i == k) continue;
				for (j = k+1; j < 2*n; j++)
					A(i,j) -= A(i,k) * A(k,j);
				A(i,k) = 0.;
			}
		}

		if (k < n) {
			printf("Not possible\n");
		} else {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++)
					printf(j ? " %.6f" : "%.6f", A(i,n+j));
				printf("\n");
			}
		}
		printf("\n");

		free(a);
	}

	return 0;
}
