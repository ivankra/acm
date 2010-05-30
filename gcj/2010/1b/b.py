#!/usr/bin/env python
import os, sys

def main():
    num_tests = int(sys.stdin.readline())
    for case_no in range(1, num_tests + 1):
        N, K, B, T = map(int, sys.stdin.readline().split())
        X = map(int, sys.stdin.readline().split())
        V = map(int, sys.stdin.readline().split())

        bad = [(B - X[i] > T * V[i]) for i in range(N)]

        costs = []
        for i in range(N):
            if bad[i]:
                continue

            cost = 0
            for j in range(N):
                if bad[j] and V[j] < V[i] and X[j] > X[i]:
                    cost += 1
            costs.append(cost)

        costs.sort()

        if len(costs) < K:
            ans = 'IMPOSSIBLE'
        else:
            ans = sum(costs[:K])

        print 'Case #%d: %s' % (case_no, ans)

if __name__ == '__main__':
    main()
    
