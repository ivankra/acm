struct Point { double la, lo; };

double gcdist(const Point &a, const Point &b, double R) {
        double u = (1. - cos(b.la-a.la)) / 2.;
        double v = cos(a.la) * cos(b.la) * (1. - cos(b.lo-a.lo)) / 2.;
        return 2*R*atan2(sqrt(u+v), sqrt(1-u-v));
}
