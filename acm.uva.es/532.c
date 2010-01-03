#include <stdio.h>
#include <string.h>

int main()
{
	static char m[32][32][32], buf[1024];
	static int s[32768], d[32768], l, r, c, endp;
	int z, y, x, k, p, t;

#define ENCODE(z,y,x) (((z) << 10) | ((y) << 5) | (x))

	while (scanf("%d%d%d\n", &l, &r, &c) == 3 && l > 0) {
		memset(m, 0, sizeof(m));

		for (t = 0, z = 1; z <= l; z++) {
			for (y = 1; y <= r; y++) {
				scanf(" %[#.SsEe]\n", buf);
				for (x = 1, p = 0; x <= c; x++, p++) {
					if (buf[p] == '#') {
						m[z][y][x] = 0;
					} else if (buf[p] == '.') {
						m[z][y][x] = 1;
					} else if ((buf[p] | 0x20) == 's') {
						m[z][y][x] = 0;
						s[t] = ENCODE(z,y,x);
						d[s[t++]] = 0;
					} else if ((buf[p] | 0x20) == 'e') {
						m[z][y][x] = 1;
						endp = ENCODE(z,y,x);
					}
				}
			}
		}

		for (d[endp] = -1, p = 0; p < t && d[endp] < 0; p++) {
			x = s[p] & 0x1F;
			y = (s[p] >> 5) & 0x1F;
			z = (s[p] >> 10) & 0x1F;
			k = d[s[p]] + 1;

#define GO(Z,Y,X,D) if (m[Z][Y][X]) {m[Z][Y][X]=0;d[s[t++]=ENCODE(Z,Y,X)]=(D);}

			GO(z, y, x - 1, k);
			GO(z, y, x + 1, k);
			GO(z, y - 1, x, k);
			GO(z, y + 1, x, k);
			GO(z - 1, y, x, k);
			GO(z + 1, y, x, k);
		}

		if (d[endp] < 0)
			printf("Trapped!\n");
		else
			printf("Escaped in %d minute(s).\n", d[endp]);
	}

	return 0;
}
