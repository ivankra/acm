import java.util.*;

public class CircleTangents {
    /**
     *  Finds tangent segments between two given circles.
     *
     *  Returns an empty, or 2x4, or 4x4 array of doubles representing
     *  the two exterior and two interior tangent segments (in that order).
     *  If some tangents don't exist, they aren't present in the output.
     *  Each segment is represent by a 4-tuple x1,y1,x2,y2.
     * 
     *  Exteriour tangents exist iff one of the circles doesn't contain
     *  the other. Interior tangents exists iff circles don't intersect.
     *
     *  In the limiting case when circles touch from outside/inside, there are
     *  no interiour/exterior tangents, respectively, but just one common
     *  tangent line (which isn't returned at all, or returned as two very
     *  close or equal points by this code, depending on roundoff -- sorry!)
     */
    public static double[][] getTangents(double x1, double y1, double r1, double x2, double y2, double r2) {
        double d_sq = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        if (d_sq <= (r1-r2)*(r1-r2)) return new double[0][4];

        double d = Math.sqrt(d_sq);
        double vx = (x2 - x1) / d;
        double vy = (y2 - y1) / d;

        double[][] res = new double[4][4];
        int i = 0;

        // Let A, B be the centers, and C, D be points at which the tangent
        // touches first and second circle, and n be the normal vector to it.
        //
        // We have the system:
        //   n * n = 1          (n is a unit vector)          
        //   C = A + r1 * n
        //   D = B +/- r2 * n
        //   n * CD = 0         (common orthogonality)
        //
        // n * CD = n * (AB +/- r2*n - r1*n) = AB*n - (r1 -/+ r2) = 0,  <=>
        // AB * n = (r1 -/+ r2), <=>
        // v * n = (r1 -/+ r2) / d,  where v = AB/|AB| = AB/d
        // This is a linear equation in unknown vector n.

        for (int sign1 = +1; sign1 >= -1; sign1 -= 2) {
            double c = (r1 - sign1 * r2) / d;

            // Now we're just intersecting a line with a circle: v*n=c, n*n=1

            if (c*c > 1.0) continue;
            double h = Math.sqrt(Math.max(0.0, 1.0 - c*c));

            for (int sign2 = +1; sign2 >= -1; sign2 -= 2) {
                double nx = vx * c - sign2 * h * vy;
                double ny = vy * c + sign2 * h * vx;

                double[] a = res[i++];
                a[0] = x1 + r1 * nx;
                a[1] = y1 + r1 * ny;
                a[2] = x2 + sign1 * r2 * nx;
                a[3] = y2 + sign1 * r2 * ny;
            }
        }
        
        return Arrays.copyOf(res, i);
    }
}
