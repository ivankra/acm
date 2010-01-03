#include <stdio.h>
#include <assert.h>

/*
 *  w, h: dimensions of the rectangle
 *  l, r: positions of left/right turtle
 *  sl, sr: signs of increments to left/right
 */
int count(int l, int r, int w, int h, int sl, int sr)
{
	int x, y, z;

/*printf("count(l=%d, r=%d, w=%d, h=%d, sl=%d, sr=%d)\n",l,r,w,h,sl,sr);*/

	assert(0 <= l && l <= w && 0 <= r && r <= w);
	assert(h >= 0);

	if (l >= r)
		return 0;

	if (l == 0 && sl < 0) sl = 1;
	if (r == w && sr > 0) sr = -1;

	if (h == 0) {
/*z=(sl>0&&sr<0)?1:0;printf("count(l=%d, r=%d, w=%d, h=%d, sl=%d, sr=%d) = %d\n",l,r,w,h,sl,sr,z);*/
		return (sl > 0 && sr < 0) ? 1 : 0;
	}

	z = 0;
	for (x = l; 0 <= x && x < r; x += sl)
		for (y = r; x < y && l < y && y <= w; y += sr)
			z += count(x, y, w, h - 1, sl, sr);

/*printf("count(l=%d, r=%d, w=%d, h=%d, sl=%d, sr=%d) = %d\n",l,r,w,h,sl,sr,z);*/

	return z;
}

int count_rect(int w, int h)
{
	int x, y, z;

	assert(w > 0 && h > 0);

printf("%dx%d => ",w,h);

	for (z = 0, x = 0; x <= w; x++)
		for (y = x + 1; y <= w; y++) {
			printf(" [x=%d,y=%d,w=%d,h=%d]",x,y,w,h-1);
			z += count(x, y, w, h - 1, -1, +1);
			printf("(%d)",count(x, y, w, h - 1, -1, +1));
		}

printf(" = %d\n",z);
	return z;
}

int solve(int n)
{
	int a, b, r;

	if ((n & 1) != 0)
		return 0;

	for (a = 1, r = 0; a <= n; a++) {
		b = n / 2 - a;
		if (b < 1) continue;

		assert(2 * (a + b) == n);

		r += count_rect(a, b);
	}

	return r;
}

int main()
{
	int n;

	while (scanf("%d", &n) == 1)
		printf("%d\n", solve(n));

	return 0;
}
