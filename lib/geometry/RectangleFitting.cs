using System;

public class Program {
    // Can an a-by-b rectangle fit in an A-by-B rectangle?
    bool fits(int a, int b, int A, int B) {
        if (a <= A && b <= B) return true;
        if (a <= B && b <= A) return true;

        if (a > b) { int t = a; a = b; b = t; }
        if (A < B) { int t = A; A = B; B = t; }

        double left = 0, right = 1;
        for (int k = 0; k < 80; k++) {
            double t = (left + right) / 2;
            double s = Math.Sqrt(1 - t * t);

            double W = a * t + b * s;
            double H = a * s + b * t;
            const double EPS = 1e-9;

            if (W < A + EPS && H < B + EPS) {
                // rotate rectangle clockwise by angle asin(t)
                return true;
            }

            if (H < B)
                // angle too small
                left = t;
            else
                // angle too big
                right = t;
        }

        return false;
    }
}
