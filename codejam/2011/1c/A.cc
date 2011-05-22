#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
    int T;
    scanf("%d", &T);

    int nrows, ncols;
    char a[64][64];

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d %d", &nrows, &ncols);
        memset(a, 0, sizeof(a));
        for (int i = 0; i < nrows; i++)
            scanf(" %s", a[i]);

        bool ok = true;
        for (int i = 0; i < nrows && ok; i++) {
            for (int j = 0; j < ncols; j++) {
                if (a[i][j] == '.' || a[i][j] == '/' || a[i][j] == '\\')
                    continue;

                if (a[i][j]=='#' && a[i][j+1]=='#' && a[i+1][j]=='#' && a[i+1][j+1]=='#') {
                    a[i][j] = '/';
                    a[i][j+1] = '\\';
                    a[i+1][j] = '\\';
                    a[i+1][j+1] = '/';
                    continue;
                }

                ok = false;
                break;
            }
        }

        printf("Case #%d:\n", cs);
        if (ok) {
            for (int i = 0; i < nrows; i++)
                printf("%s\n", a[i]);
        } else {
            printf("Impossible\n");
        }
    }
}
