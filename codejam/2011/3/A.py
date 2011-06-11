#!/usr/bin/env python
import os, sys, math

def readline():
    return sys.stdin.readline()

def solve():
    W, Ln, Un, G = map(int, readline().split())

    L = []
    for each in range(Ln):
        L.append(map(int, readline().split()))

    U = []
    for each in range(Un):
        U.append(map(int, readline().split()))

    def get_y(P, qx):
        i = 0
        while i + 2 < len(P) and P[i+1][0] <= qx:
            i += 1

        x0, y0 = P[i]
        x1, y1 = P[i+1]

        return y0 + (y1 - y0) * (qx - x0) / float(x1 - x0)

    def get_area(left, right):
        xs = [ x for (x, y) in L ]
        xs += [ x for (x, y) in U ]
        xs += [ left, right ]
        xs = sorted(set(xs))
        xs = [ x for x in xs if left - 1e-9 <= x <= right + 1e-9 ]

        res = 0
        for i in range(1, len(xs)):
            x0 = xs[i-1]
            x1 = xs[i]

            side0 = abs(get_y(L, x0) - get_y(U, x0))
            side1 = abs(get_y(L, x1) - get_y(U, x1))
            h = abs(x0 - x1)

            res += (side0 + side1) * h / 2.0

        return res

    total_area = get_area(0, W)
    slice_area = total_area / float(G)

    cuts = [ 0.0 ]
    while len(cuts) < G:
        low = cuts[-1]
        high = W

        for i in range(50):
            mid = (low + high) / 2
            if get_area(cuts[-1], mid) > slice_area:
                high = mid
            else:
                low = mid

        cuts.append(mid)
        print '%.10lg' % mid

def main():
    T = int(readline())

    for cs in range(T):
        print 'Case #%d:' % (cs+1)
        solve()

if __name__ == '__main__':
    main()
