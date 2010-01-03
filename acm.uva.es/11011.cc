#include <cstdio>
#include <cstring>
#include <stdarg.h>

int width[16], height[16];
char out[40][32768];

void put(int y, int x, char *s, ...) {
        static char buf[1024];
        va_list v;
        va_start(v, s);
        vsprintf(buf, s, v);
        for (char *p = buf; *p;) out[y][x++] = *p++;
        va_end(v);
}

void go(int y, int x, int a, int b) {
        int n = b-a;
        if (n == 1) {
                put(y,   x, "f(x..)-f(x..)");
                put(y+1, x+3, "%.2d.....%.2d", a, b);
                put(y+2, x, "_____________");
                put(y+3, x+3, "x..-x");
                put(y+4, x+4, "%.2d..%.2d", a, b);
                return;
        }

        int t = y + height[n] - 3;
        for (int i = 0, w = width[n]; i < w; i++) out[t][x+i] = '_';

        out[y+height[n]-6][x+width[n-1]] = '-';
        put(y+height[n]-2, x+width[n-1]-3, "x..-x");
        put(y+height[n]-1, x+width[n-1]-2, "%.2d..%.2d", a, b);

        go(y,x,a,b-1);
        go(y,x+width[n-1]+1,a+1,b);
}

int main() {
        width[1] = 13;
        height[1] = 5;
        for (int n = 2; n <= 12; n++) {
                width[n] = width[n-1] * 2 + 1;
                height[n] = height[n-1] + 3;
        }

        for (int cs = 1, n; scanf("%d", &n) == 1 && n > 0; cs++) {
                printf("Case %d:\n", cs);

                memset(out, '.', sizeof(out));
                go(0, 0, 0, n);

                for (int i = 0; i < height[n]; i++) {
                        out[i][width[n]] = '\n';
                        fwrite(out[i], 1, width[n]+1, stdout);
                }
                printf("\n");
        }
}
