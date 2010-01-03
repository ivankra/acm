#include <stdio.h>
#include <string.h>
#include <math.h>

double lot_area, roof_area, floor_area, pi;
double total_roof = 0., total_floor = 0., total_area = 0.;
int nlots;

void take()
{
	double a, b, d, r;
	int c;

	for (roof_area = floor_area = 0;;) {
		while ((c = getchar()) != EOF && !strchr("0123456789-.\n", c));

		if (c == '\n') {
			while ((c = getchar()) != EOF && !strchr("0123456789-.\n", c));
			if (c == '\n') return;
		}

		if (c == EOF)
			return;

		ungetc(c, stdin);
		if (scanf("%lf %lf %lf %lf", &b, &r, &d, &a) != 4)
			return;

		roof_area += (b + r) * d / 2.;
		floor_area += (b + r) * d * cos(a * pi / 180.) / 2.;
	}
}

int main()
{
	printf("Roof Area     Floor Area     %% Covered\n");
	printf("---------     ----------     ---------\n");

	pi = 2. * acos(0.);

	for (nlots = 0; scanf("%lf", &lot_area) == 1; nlots++) {
		take();
		printf("%9.2f%15.2f%13.2f%%\n", roof_area, floor_area, floor_area * 100. / lot_area);

		total_area += lot_area;
		total_roof += roof_area;
		total_floor += floor_area;
	}


	printf(
		"\n"
		"Total surface area of roofs %11.2f\n"
		"Total area covered by roofs %11.2f\n"
		"Percentage of total area covered by roofs %7.2f%%\n"
		"Average roof surface area per lot %15.2f\n"
		"Average floor space covered per lot %13.2f\n",
		total_roof, total_floor,
		total_floor * 100. / total_area,
		total_roof / (double)nlots,
		total_floor / (double)nlots
	);

	return 0;
}
