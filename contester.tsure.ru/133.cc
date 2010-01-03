#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>

struct Pos {
	int x, y;
	Pos(int x=0, int y=0) : x(x), y(y) {}
	Pos operator +(const Pos &p) const { return Pos(x+p.x, y+p.y); }
};

int A[16][16], B[16][16];

int valid(Pos p) { return 1 <= p.x && p.x <= 8 && 1 <= p.y && p.y <= 8; }
void atk(Pos p) { if (valid(p)) A[p.x][p.y]=1; }
void ray(Pos p, Pos d) {
	for (p=p+d; valid(p); p=p+d) { atk(p); if (B[p.x][p.y]) break; }
}

Pos get(char piece='?') {
	char s[8]; int y;
       	scanf(" %[a-zA-Z] %d", s, &y);
	Pos p(toupper(s[0])-'A'+1, y);
	B[p.x][p.y] = piece;
	return p;
}

int main()
{
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
	Pos w=get('K'); Pos bK=get('k'); Pos bR=get('r');
	Pos bB=get('b'); Pos bN=get('n');

	// King
	for (int i = -1; i <= 1; i++)
	for (int j = -1; j <= 1; j++)
		if (i != 0 || j != 0) atk(bK + Pos(i,j));

	// Rook
	ray(bR, Pos(0,1));
	ray(bR, Pos(0,-1));
	ray(bR, Pos(1,0));
	ray(bR, Pos(-1,0));

	// Bishop
	for (int i = -1; i <= 1; i += 2)
	for (int j = -1; j <= 1; j += 2)
		ray(bB, Pos(i,j));

	// Knight
	for (int i = -2; i <= 2; i++)
	for (int j = -2; j <= 2; j++)
		if ((abs(i)==1 && abs(j)==2) || (abs(i)==2 && abs(j)==1))
			atk(bN + Pos(i,j));

#if 0
	printf("  ABCDEFGH\n");
	for (int j = 1; j <= 8; j++) {
		printf("%c ",'0'+j);
		for (int i = 1; i <= 8; i++) {
			if(A[i][j])printf("\033[01;31m");
			if (B[i][j]) putchar(B[i][j]);
			else putchar(A[i][j]?'*':'.');
			if(A[i][j])printf("\033[m");
		}
		putchar('\n');
	}
#endif

	int e = 0;
	for (int i = -1; i <= 1; i++)
	for (int j = -1; j <= 1; j++)
		if (i != 0 || j != 0)
		if (valid(w+Pos(i,j)))
		if (!A[w.x+i][w.y+j])
			e = 1;

	if (A[w.x][w.y])
		printf(e ? "check\n" : "checkmate\n");
	else
		printf(e ? "usual position\n" : "stalemate\n");
}
