#include <stdio.h>
#include <string.h>

int pal[1024], npal[1024];

int main()
{
	int A, B, L, T;

	memset(pal, 0, sizeof(pal));
	pal[0] = 1;
	for (int i = 1; i <= 9; i++) pal[i] = pal[i*10+i] = 1;
	for (int i = 1; i <= 9; i++)
		for (int j = 0; j <= 9; j++)
			pal[i*100+j*10+i] = 1;

	npal[0] = 0;
	for (int i = 0; i <= 1001; i++)
		npal[i+1] = npal[i] + pal[i];

	for (scanf("%d", &T); T-- > 0 && scanf("%d %d %d", &A, &B, &L) == 3;) {
		int S, E, bS, bE, bR=0;
		bS = bE = A;
		for (S = A; S <= B; S++) {
			for (E = S; E <= B && (E-S+1) <= L; E++) {
				int R = npal[E+1] - npal[S];
				if (R < bR) continue;
				if (R == bR) {
					if (bE-bS < E-S) continue;
					if (bE-bS == E-S) {
						if (bS <= S) continue;
					}
				}
				bS = S; bE = E; bR= R;
			}
		}	

		if (bR == 0)
			printf("Barren Land.\n");
		else	
			printf("%d %d\n", bS, bE, bR);
	}

	return 0;
}
