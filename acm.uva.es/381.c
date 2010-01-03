#include <stdio.h>
#include <math.h>

#define EPS 1e-12

int tests[32][16], bonus[32], absc[32], grade[32], s, t;
double avg[32], mean, sd;

int main()
{
	int i, j, k, r;

	printf("MAKING THE GRADE OUTPUT\n");

	for (scanf("%d", &r); r-- > 0 && scanf("%d %d", &s, &t) == 2;) {
		for (i = 0; i < s; i++) {
			for (j = 0; j < t; j++)
				scanf("%d", &tests[i][j]);
			scanf("%d %d", &bonus[i], &absc[i]);
		}

		for (i = 0; i < s; i++) {
			for (avg[i] = 0, j = 0; j < t; j++)
				avg[i] += tests[i][j];

			if (t <= 2) {
				avg[i] /= (double)t;
			} else {
				for (k = tests[i][0], j = 1; j < t; j++)
					if (tests[i][j] < k) k = tests[i][j];

				avg[i] = (avg[i] - k) / (double)(t - 1);
			}
		}

		for (mean = 0., i = 0; i < s; i++)
			mean += avg[i];
		mean /= (double)s;

		for (sd = 0., i = 0; i < s; i++)
			sd += (avg[i] - mean) * (avg[i] - mean);
		sd = sqrt(sd / (double)s);
		if (sd < 1.) sd = 1.;

		for (i = 0; i < s; i++) {
			k = bonus[i] / 2;
			avg[i] += k * 3;
		}

		for (i = 0; i < s; i++) {
			if (avg[i] >= (mean + sd - EPS))
				grade[i] = 0;
			else if (avg[i] >= (mean - EPS))
				grade[i] = 1;
			else if (avg[i] >= (mean - sd - EPS))
				grade[i] = 2;
			else
				grade[i] = 3;
		}

		for (i = 0; i < s; i++) {
			if (absc[i] == 0) {
				if (grade[i] > 0) grade[i]--;
			} else {
				k = absc[i] / 4;
				grade[i] += k;
				if (grade[i] > 4) grade[i] = 4;
			}
		}

		for (i = 0, k = 0; i < s; i++)
			k += 4 - grade[i];
		printf("%.1f\n", k / (double)s);
	}

	printf("END OF OUTPUT\n");
	return 0;
}

