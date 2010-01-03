#include <stdio.h>
#include <math.h>

int main()
{
	int T, x0, y0, x1, y1, x2, y2;
	char buf[256];
	
	for (scanf("%d", &T); T-- > 0 && scanf("%d %d", &x0, &y0) == 2;) {
		double d = 0;
		gets(buf);
		while (gets(buf) && sscanf(buf, "%d %d %d %d", &x1, &y1, &x2, &y2) == 4)
			d += sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

		int s = (int)(d * 36 / 100 + 30 + 1e-9);
		printf("%d:%.2d\n", s / 3600, (s / 60) % 60);
		if (T) printf("\n");
	}

	return 0;
}
