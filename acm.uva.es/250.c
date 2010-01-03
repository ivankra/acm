#include <stdio.h>
#include <math.h>

int main()
{
	static double m[32][32], rsum[32], csum[32], s, mindiff;
	static int rows, cols, t, cr, cc;
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
		/* rsum[i]: cumulative sum of rows 0..i */

		for (i = 0, s = 0.; i < cols; i++) {
			for (j = 0; j < rows; j++)
				s += m[j][i];
			csum[i] = s;
		}
		/* csum[i]: cumulative sum of columns 0..i */

		/* select row */
		cr = 0;
		mindiff = rsum[rows - 1] - rsum[0];
		for (i = 1; i < rows; i++) {
			s = (rsum[rows - 1] - rsum[i]) - (rsum[i - 1]);
			if (s < 0) s = -s;
			if (s < mindiff || fabs(s - mindiff) < 0.000000001) {
				cr = i;
				mindiff = s;
			}
		}

		/* select column */
		cc = 0;
		mindiff = csum[cols - 1] - csum[0];
		for (i = 1; i < cols; i++) {
			s = (csum[cols - 1] - csum[i]) - (csum[i - 1]);
			if (s < 0) s = -s;
			if (s < mindiff || fabs(s - mindiff) < 0.000000001) {
				cc = i;
				mindiff = s;
			}
		}

		printf("Case %d: center at (%d, %d)\n", ++t, cr+1, cc+1);
	}

	return 0;
}
