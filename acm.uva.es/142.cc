#include <stdio.h>

struct { int x1, y1, x2, y2; } reg[256];
struct { int x, y, v; } ico[256];
int nreg, nico;

int dist(int x, int y) { return x*x+y*y; }
void cmpchg(int *a, int *b) { if ((*a)>(*b)) { int t=*a;*a=*b;*b=t; } }

int main()
{
	char s[256];
	int i, k, x, y;

	for (nreg = nico = 0; scanf(" %s", s) == 1 && s[0] != '#';) {
		if (s[0] == 'R' || s[0] == 'r') {
			scanf("%d %d %d %d",
				&reg[nreg].x1, &reg[nreg].y1,
				&reg[nreg].x2, &reg[nreg].y2);
			cmpchg(&reg[nreg].x1, &reg[nreg].x2);
			cmpchg(&reg[nreg].y1, &reg[nreg].y2);
			nreg++;
			continue;
		}

		if (s[0] == 'I' || s[0] == 'i') {
			scanf("%d %d", &ico[nico].x, &ico[nico].y);
			ico[nico].v = -1;
			nico++;
			continue;
		}

		for (k = 0; k < nico; k++) {
			if (ico[k].v >= 0) continue;
			ico[k].v = 1;
			x = ico[k].x;
			y = ico[k].y;
			for (i = nreg - 1; i >= 0; i--)
				if (reg[i].x1 <= x && x <= reg[i].x2 &&
				    reg[i].y1 <= y && y <= reg[i].y2) {
				    	ico[k].v = 0;
					break;
				}	
		}	

		scanf("%d %d", &x, &y);

		for (i = nreg - 1; i >= 0; i--)
			if (reg[i].x1 <= x && x <= reg[i].x2 &&
			    reg[i].y1 <= y && y <= reg[i].y2)
				break;

		if (i >= 0) {
			printf("%c\n", i + 'A');
			continue;
		}

		for (k = 0x7FFFFFFF, i = 0; i < nico; i++)
			if (ico[i].v) k <?= dist(ico[i].x - x, ico[i].y - y);

		for (i = 0; i < nico; i++)
			if (ico[i].v && dist(ico[i].x - x, ico[i].y - y) == k)
				printf("%3d", i + 1);
		printf("\n");
	}

	return 0;
}
