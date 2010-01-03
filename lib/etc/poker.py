#!/usr/bin/python

def evalhand(hand):
    SUITS = 'CDHS'
    VALS = '23456789TJQKA'

    def cval(s): return s[0]
    def cvalrank(s): return 2 + VALS.index(s[0])
    def csuit(s): return s[1]

    def kinds(wanted):
        cnt = {}
        for c in hand:
            cnt[cval(c)] = cnt.get(cval(c), 0) + 1
        z = list(reversed(sorted(cnt.values())))
        z = filter(lambda x: x > 1, z)
        if z == wanted:
            x = map(cvalrank, filter(lambda c: cnt[cval(c)] == wanted[0], hand))
            x = list(reversed(sorted(x)))
            wanted = list(reversed(sorted(set(wanted))))
            if len(wanted) == 1:
                return x
            else:
                y = map(cvalrank, filter(lambda c: cnt[cval(c)] == wanted[1], hand))
                y = list(reversed(sorted(y)))
                return x + y

    def z_royal_flush():
        for s in SUITS:
            if all(v+s in hand for v in 'TJQKA'):
                return cvalrank('A')

    def y_straight_flush():
        if v_flush() is not None:
            return u_straight()

    def x_four_of_a_kind(): return kinds([4])
    def w_full_house(): return kinds([3, 2])

    def v_flush():
        if all(csuit(hand[0]) == csuit(h) for h in hand):
            return max(map(cvalrank, hand))

    def u_straight():
        z = list(sorted(set(map(cvalrank, hand))))
        if len(z) == 5:
            if max(z) - min(z) == 4: return max(z)
            #if z == [2,3,4,5,14]: return 5

    def t_three_of_a_kind(): return kinds([3])
    def s_two_pairs(): return kinds([2, 2])

    def r_pair():
        for v in VALS:
            x = filter(lambda c: cval(c) == v, hand)
            y = filter(lambda c: cval(c) != v, hand)
            if len(x) == 2:
                return [cvalrank(v)] + list(reversed(sorted(y)))

    def q_high_card(): return max(map(cvalrank, hand))

    assert len(sorted(hand)) == 5
    for fn in [z_royal_flush, y_straight_flush, x_four_of_a_kind,
            w_full_house, v_flush, u_straight, t_three_of_a_kind,
            s_two_pairs, r_pair, q_high_card]:
        res = fn()
        if res is not None:
            return [fn.__name__, res] + list(reversed(sorted(map(cvalrank, hand))))

answer = 0
for line in open('poker.txt', 'r'):
    cards = line.strip().split()
    x = evalhand(cards[:5])
    y = evalhand(cards[5:])
    assert x != y
    print x, y, ' => ',
    if x > y:
        print 'Player 1'
        answer += 1
    else:
        print 'Player 2'
print answer


print evalhand('2C 3C 4C 6C 5C'.split())
