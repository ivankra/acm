/*
ID: infnty1
PROB: ttwo
LANG: C++
*/
#include <stdio.h>

#define MAXSTEPS (10*10*4*10*10*4+1000)

struct pos { int y,x,d; };
bool operator != (pos &a, pos &b) { return a.x != b.x || a.y != b.y; }

struct state { pos c,f; };

int a[16][16], dx[]={0,1,0,-1}, dy[]={-1,0,1,0};

pos next(pos p)
{
	pos r = p;
	if (a[p.y+dy[p.d]][p.x+dx[p.d]] != '.')
		r.d = (r.d + 1) & 3;
	else
		r.y += dy[p.d], r.x += dx[p.d];
	return r;
}

state next(state s) { state t = {next(s.c),next(s.f)}; return t; }

int main()
{
	state S;

	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);

	for (int i = 0; i < 16; i++) for (int j = 0; j < 16; j++) a[i][j] = '*';
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10;) {
			int c = getchar();
			if (c == '*' || c == '.') a[i][j++] = c;
			else if (c == 'C') { S.c.y=i; S.c.x=j; a[i][j++]='.'; }
			else if (c == 'F') { S.f.y=i; S.f.x=j; a[i][j++]='.'; }
		}
	S.c.d = S.f.d = 0;

	int n;
	for (n = 0; n < MAXSTEPS && S.c != S.f; n++) S = next(S);

	printf("%d\n", (n < MAXSTEPS) ? n : 0);

	return 0;
}
