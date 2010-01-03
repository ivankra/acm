from math import sqrt

def golden_section_search(f, a, b, eps):
    """Finds minimum of a unimodal function f on interval [a, b]"""

    phi = (1 + sqrt(5)) / 2;
    x1 = a + (b - a) / (1 + phi);
    x2 = b - (b - a) / (1 + phi);
    y1 = f(x1);
    y2 = f(x2);

    while b - a > eps:
        if y1 < y2:
            b = x2;
            x2 = x1;
            y2 = y1;
            x1 = a + b - x2;
            y1 = f(x1);
        else:
            a = x1;
            x1 = x2;
            y1 = y2;
            x2 = a + b - x1;
            y2 = f(x2);

    return (x1 + x2) / 2.0;


def ternary_search(f, a, b, eps):
    while b - a > eps:
        u = (2 * a + b) / 3.0
        v = (a + 2 * b) / 3.0
        if f(u) > f(v):
            a = u
        else:
            b = v
    return (a + b) / 2.0


print golden_section_search(lambda x: (x-1.234)*(x-1.234)+5, -10, 10, 1e-9)
print ternary_search(lambda x: (x-1.234)*(x-1.234)+5, -10, 10, 1e-9)
