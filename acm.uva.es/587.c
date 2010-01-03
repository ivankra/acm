#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main()
{
	char buf[1024], *s;
	double m, x, y, sqrt2;
	int t, i;

	sqrt2 = sqrt(2.);

	for (t = 1; scanf(" %[^\n]", buf) == 1 && buf[0] != 'E'; t++) {
		for (s = buf; *s; s++)
			*s = toupper(*s);

		for (s = buf, x = 0., y = 0.; *s;) {
			while (*s && !isdigit(*s)) s++;
			if (*s == '\0') break;

			for (i = 0; *s >= '0' && *s <= '9'; s++)
				i = i * 10 + *s - '0';
			m = (double)i;

			while (*s && !isalpha(*s)) s++;
			if (*s == '\0') break;

			if (s[0] == 'N') {
				if (s[1] == 'E') {
					m /= sqrt2;
					x += m;
				} else if (s[1] == 'W') {
					m /= sqrt2;
					x -= m;
				}
				y += m;
			} else if (s[0] == 'S') {
				if (s[1] == 'E') {
					m /= sqrt2;
					x += m;
				} else if (s[1] == 'W') {
					m /= sqrt2;
					x -= m;
				}
				y -= m;
			} else if (s[0] == 'W') {
				x -= m;
			} else if (s[0] == 'E') {
				x += m;
			}
		}

		printf("Map #%d\nThe treasure is located at (%.3f,%.3f).\n"
		       "The distance to the treasure is %.3f.\n\n",
		       t, x, y, sqrt(x * x + y * y));		
	}

	return 0;
}
