#include <cstdio>
#include <cstring>

char ima[256][256];
int K;

void put(int c) {
	if (K == 50) { printf("\n"); K=0; }
	putchar(c);
	K++;
}

int get() {
	int c;
	while ((c = getchar()) != EOF)
		if (c == 'D' || c == '0' || c == '1') return c;
	return c;
}

void pack(int r, int c, int nr, int nc) {
	if (nr <= 0 || nc <= 0) return;

	int a = ima[r][c];
	for (int i = 0; i < nr; i++)
	for (int j = 0; j < nc; j++)
		if (ima[r+i][c+j] != a) goto split;
	put(a);
	return;

split:
	int cr = (nr + 1) >> 1;
	int cc = (nc + 1) >> 1;

	put('D');
	pack(r, c, cr, cc);
	pack(r, c+cc, cr, nc-cc);
	pack(r+cr, c, nr-cr, cc);
	pack(r+cr, c+cc, nr-cr, nc-cc);
}

void unpack(int r, int c, int nr, int nc) {
	if (nr <= 0 || nc <= 0) return;

	int a = get();
	if (a != 'D') {
		for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			ima[r+i][c+j] = a;
		return;
	}

	int cr = (nr + 1) >> 1;
	int cc = (nc + 1) >> 1;

	unpack(r, c, cr, cc);
	unpack(r, c+cc, cr, nc-cc);
	unpack(r+cr, c, nr-cr, cc);
	unpack(r+cr, c+cc, nr-cr, nc-cc);
}

int main()
{
	char op;
	int nrows, ncols;
	while (scanf(" %c %d %d", &op, &nrows, &ncols) == 3 && (op=='B'||op=='D')) {
		if (op == 'B') {
			for (int i = 0; i < nrows; i++)
			for (int j = 0; j < ncols; j++) {
				int c;
				while ((c = getchar()) != EOF) {
					if (c == '0' || c == '1') {
						ima[i][j] = c;
						break;
					}
				}
			}
			printf("D%4d%4d\n", nrows, ncols);
			K=0;
			pack(0,0,nrows,ncols);
			printf("\n");
		} else {
			unpack(0,0,nrows,ncols);
			printf("B%4d%4d\n", nrows, ncols);
			int k = 0;
			for (int i = 0; i < nrows; i++)
			for (int j = 0; j < ncols; j++) {
				if (k == 50) { printf("\n"); k=0; }
				putchar(ima[i][j]);
				k++;
			}
			printf("\n");
		}
	}
}
