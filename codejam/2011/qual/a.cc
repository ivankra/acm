#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>
using namespace std;

int N, P[1000], Next[1000];
char R[1000];

int solve()
{
    int pos[2] = { 1, 1 };
    int target[2] = { -1, -1 };

    for (int i = 0; i < N; i++) {
        if (target[R[i]] == -1)
            target[R[i]] = P[i];

        Next[i] = -1;
        for (int j = i + 1; j < N; j++) {
            if (R[i] == R[j]) {
                Next[i] = j;
                break;
            }
        }
    }

    int at = 0, time = 0;
    for (; at < N; time++) {
        int next_at = at;
        for (int i = 0; i < 2; i++) {
            if (target[i] != -1 && target[i] != pos[i]) {
                pos[i] += target[i] > pos[i] ? 1 : -1;
            } else if (target[i] == pos[i] && i == R[at]) {
                assert(pos[i] == P[at]);
                // push
                target[i] = P[Next[at]];
                //printf("at t=%d: %c push %d, start moving to %d\n", time, "OB"[i], pos[i], target[i]);
                next_at = at + 1;
            }
        }
        at = next_at;
    }

    return time;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int cs = 1; cs <= T; cs++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf(" %c %d", &R[i], &P[i]);
            R[i] = (R[i] == 'O') ? 0 : 1;
        }
        printf("Case #%d: %d\n", cs, solve());
    }
}
