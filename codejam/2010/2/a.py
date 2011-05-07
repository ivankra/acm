#!/usr/bin/env python
import os, sys, re
stdin = sys.stdin

def main():
    num_cases = int(stdin.readline())

    for case_no in xrange(1, num_cases + 1):
        N = int(stdin.readline())

        def mp(ij):
            i, j = ij
            if i < N:
                row = i - j
                col = j
            else:
                row = N - 1 - j
                col = i - N + 1 + j
            return (row, col)

        A = dict()
        for i in range(2*N-1):
            line = stdin.readline()
            for j in range(len(line)):
                if line[j].isdigit():
                    A[i, j] = line[j]

        best = 999999999

        for rrow in range(2*N-1):
            for rcol in range(2*N-1):
                B = dict()
                bad = 0
                for y0, x0 in A.iterkeys():
                    y1 = rrow + (rrow - y0)
                    x1 = x0
                    if (y1, x1) in A and A[y1, x1] != A[y0, x0]:
                        bad = 1
                        break

                    y2 = y0
                    x2 = rcol + (rcol - x0)
                    if (y2, x2) in A and A[y2, x2] != A[y0, x0]:
                        bad = 1
                        break
                    
                    y3 = rrow + (rrow - y0)
                    x3 = rcol + (rcol - x0)
                    if (y3, x3) in A and A[y3, x3] != A[y0, x0]:
                        bad = 1
                        break

                    B[y0, x0] = A[y0, x0]
                    B[y1, x1] = A[y0, x0]
                    B[y2, x2] = A[y0, x0]
                    B[y3, x3] = A[y0, x0]

                if bad:
                    continue

                NN1 = max(rrow, 2*N-2-rrow) + 1
                NN2 = max(rcol, 2*N-2-rcol) + 1

                NN1 = max(N, NN1)
                NN2 = max(N, NN2)

                NN = max(N, NN1 + (NN2-N), NN2 + (NN1-N))

                """print 'rrow=%d rcol=%d => %d (NN1=%d NN2=%d)' % (rrow, rcol, NN, NN1, NN2)
                for i in range(-10, 10):
                    for j in range(-10, 10):
                        sys.stdout.write(B.get((i, j), ' '))
                    sys.stdout.write('\n')
                print"""

                best = min(best, NN*NN - N*N)

        print 'Case #%d: %d' % (case_no, best)



if __name__ == '__main__':
    main()
