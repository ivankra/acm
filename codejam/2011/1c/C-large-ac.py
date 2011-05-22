#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, gmpy, os

def readline():
    return sys.stdin.readline()

def factorize(n):
    if n <= 100000:
        res = []
        x = 2
        while x*x <= n:
            while n % x == 0:
                res.append(x)
                n /= x
            x += 1
        if n > 1:
            res.append(n)
        return res
    else:
        res = os.popen('./factorize %d' % n, 'r').read()  # demos/factorize.c program from ftp://ftp.gmplib.org/pub/gmp-5.0.2/gmp-5.0.2.tar.bz2
        return map(int, res.split())

def divisors(n):
    factors = sorted(factorize(n))
    mult = dict()
    for f in factors:
        mult[f] = mult.get(f, 0) + 1
    keys = sorted(set(factors))
    result = []

    def recurse(i, x):
        if i == len(keys):
            result.append(x)
        else:
            k = keys[i]
            for t in xrange(1 + mult[k]):
                recurse(i + 1, x)
                x *= k

    recurse(0, 1)
    return sorted(result)

# find min x in [low, high] such that l|x, x|g
def solve1(low, high, l, g):
    if low > high:
        return

    if g % l != 0:
        return

    if l > 1:
        x = solve1(low=(low+l-1)//l, high=high//l, l=1, g=g//l)
        return None if x is None else (x * l)

    #for x in xrange(low, high+1):
    #    if g % x == 0:
    #        print ' ; solve1([%d, %d], g=%d) => %d' % (low, high, g, x)
    #        return x

    factors = sorted(factorize(g))
    mult = dict()
    for f in factors:
        mult[f] = mult.get(f, 0) + 1
    keys = sorted(set(factors))
    result = [ None ]

    def recurse(i, x):
        if i == len(keys):
            if low <= x <= high:
                if result[0] is None or x < result[0]:
                    result[0] = x
        else:
            k = keys[i]
            for t in xrange(1 + mult[k]):
                recurse(i + 1, x)
                x *= k
                if x > high:
                    return

    recurse(0, 1)
    #print 'solve1([%d, %d], g=%d) => %s' % (low, high, g, result[0])
    return result[0]

def solve(A, low, high):
    A = sorted(set(A))
    N = len(A)

    G = [0] * N
    G[-1] = A[-1]
    for i in reversed(range(N-1)):
        G[i] = int(gmpy.gcd(G[i+1], A[i]))

    #print
    #print 'A:', A, ' low=%d high=%d' % (low, high)
    #print 'G:', G

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

    #print 'lcm:', lcm
    if lcm <= high:
        if low <= lcm:
            return lcm
        x = low - low % lcm
        if low <= x <= high:
            return x
        x += lcm
        if low <= x <= high:
            return x

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
        ans = solve(A, low, high)
        print 'Case #%d: %s' % (cs, ans)
        #if ans != solve_brute(A, low, high):
        #    print '***INCORRECT*** brute force: %d\n' % solve_brute(A, low, high)
        #    return

if __name__ == '__main__':
    main()
