#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, gmpy

def readline():
    return sys.stdin.readline()

# find min x in [low, high] such that l|x, x|g
def solve1(low, high, l, g):
    if low > high:
        return

    print 'solve1([%d, %d], l=%d, g=%d)' % (low, high, l, g)

    for x in xrange(low, high+1):
        if x % l == 0 and g % x == 0:
            return x

def solve(A, low, high):
    A = sorted(set(A))
    N = len(A)

    G = [0] * N
    G[-1] = A[-1]
    for i in reversed(range(N-1)):
        G[i] = int(gmpy.gcd(G[i+1], A[i]))

    print 'A:', A, ' low=%d high=%d' % (low, high)
    print 'G:', G

    if low <= A[0]:
        x = solve1(low, A[0], 1, G[0])
        if x is not None:
            return x

    lcm = A[0]
    for i in xrange(N-1):
        x = solve1(max(low, A[i]), min(high, A[i+1]), lcm, G[i+1])
        if x is not None:
            return x
        lcm = int(gmpy.lcm(lcm, A[i+1]))
        if lcm > high:
            break

    if low <= lcm <= high:
        return lcm

    return 'NO'

def solve_brute(A, low, high):
    A = sorted(set(A))
    N = len(A)

    for x in xrange(low, high+1):
        if all(x % a == 0 or a % x == 0 for a in A):
            return x
    return 'NO'

def main():
    T = int(readline())
    for cs in xrange(1, T+1):
        N, low, high = map(int, readline().split())
        A = map(int, readline().split())
        print 'Case #%d: %s' % (cs, solve_brute(A, low, high))


if __name__ == '__main__':
    main()
