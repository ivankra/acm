#include <cstdio>
#include <cstring>

char B[16][16];
int A[16][16];

bool valid(int r, int c) { return 1 <= r && r <= 8 && 1 <= c && c <= 8; }
void atk(int r, int c) { if (valid(r, c)) A[r][c] = 1; }

void ray(int r, int c, int dr, int dc) {
	if (dr==0 && dc==0) return;
	for (;;) {
		r += dr; c += dc;
		if (!valid(r, c)) break;
		atk(r, c);
		if (B[r][c] != ' ') break;
	}
}

void mark() {
	memset(A, 0, sizeof(A));
	for (int r = 1; r <= 8; r++)
	for (int c = 1; c <= 8; c++) {
		switch (B[r][c]) {
		case 'p':
			atk(r+1, c-1); atk(r+1, c+1); break;
		case 'r':
			ray(r,c,1,0); ray(r,c,-1,0);
			ray(r,c,0,1); ray(r,c,0,-1);
			break;
		case 'n':
			for (int i = 0; i < 8; i++)
				atk(r + "00113344"[i] - '2',
				    c + "13040413"[i] - '2');
			break;
		case 'b':
			ray(r,c,1,1); ray(r,c,1,-1);
			ray(r,c,-1,1); ray(r,c,-1,-1);
			break;
		case 'q':
			for (int R = -1; R <= 1; R++)
			for (int C = -1; C <= 1; C++)
				ray(r,c,R,C);
			break;
		case 'k':
			for (int R = -1; R <= 1; R++)
			for (int C = -1; C <= 1; C++)
				atk(r+R, c+C);
			break;			 
		}
	}
}

int main() {
	char buf[256];
	while (gets(buf)) {
		memset(B, ' ', sizeof(B));
		for (int i = 0; i < 64; i++) B[1+i/8][1+(i%8)] = buf[i];

		int r, c;
		for (r = 1; r <= 8; r++)
		for (c = 1; c <= 8; c++)
			if (B[r][c] == 'K') goto ok;
ok:
		mark();
		int attacked = A[r][c];

		int can_move = 0;
		for (int dr = -1; dr <= 1; dr++)
		for (int dc = -1; dc <= 1; dc++) {
			if (dr==0 && dc==0) continue;
			if (!valid(r+dr, c+dc)) continue;

			mark();
			if (A[r+dr][c+dc]) continue;

			int t = B[r+dr][c+dc];
			B[r][c] = ' ';
			B[r+dr][c+dc] = 'K';
			mark();
			if (!A[r+dr][c+dc]) can_move = 1;

			B[r][c] = 'K';
			B[r+dr][c+dc] = t;
		}

		char *s;
		if (can_move) s = "game is not over";
		else if (attacked) s = "checkmate";
		else s = "draw";

		printf("%s\n", s);
	}
}
