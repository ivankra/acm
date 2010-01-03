#include <stdio.h>
#include <math.h>

#define LESSEQ(a, b) ((a) < ((b) + 0.00000001))

int main()
{
	double m[32][32], rsum[32], csum[32], s, d;
	int rows, cols, t, cr, cc;
	int i, j;

	for (t=0; scanf("%d %d", &rows, &cols) == 2 && rows > 0 && cols > 0;) {
		for (i = 0; i < rows; i++)
			for (j = 0; j < cols; j++)
				scanf("%lf", &m[i][j]);

		for (i = 0, s = 0.; i < rows; i++) {
			for (j = 0; j < cols; j++)
				s += m[i][j];
			rsum[i] = s;
		}

		for (i = 0, s = 0.; i < cols; i++) {
			for (j = 0; j < rows; j++)
				s += m[j][i];
			csum[i] = s;
		}

		cr = 0;
		d = rsum[rows - 1] - rsum[0];
		for (i = 1; i < rows; i++) {
			s = (rsum[rows - 1] - rsum[i]) - (rsum[i - 1]);
			if (s < 0) s = -s;
			if (LESSEQ(s, d)) {
				cr = i;
				d = s;
			}
		}

		cc = 0;
		d = csum[cols - 1] - csum[0];
		for (i = 1; i < cols; i++) {
			s = (csum[cols - 1] - csum[i]) - (csum[i - 1]);
			if (s < 0) s = -s;
			if (LESSEQ(s, d)) {
				cc = i;
				d = s;
			}
		}

		printf("Case %d: center at (%d, %d)\n", ++t, cr+1, cc+1);
	}

	return 0;
}
