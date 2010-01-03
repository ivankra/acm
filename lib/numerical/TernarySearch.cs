using System;

public class Program
{
    public delegate double Function(double x);

    // Finds maximum of f(x) on [a, b] with precision h.
    // The function f(x) must be continuous and unimodal on [a, b]
    // (i.e. increase on [a, x_max], then decrease on [x_max, b].)
    public static double TernarySearch(Function f, double a, double b, double h)
    {
        while (b - a > h) {
            double x1 = (2 * a + b) / 3;
            double x2 = (a + 2 * b) / 3;
            if (f(x1) < f(x2))
                a = x1;
            else
                b = x2;
        }
        return (a + b) / 2;
    }

    public static double f(double x)
    {
        double mid = Math.E + Math.PI;
        if (x < mid)
            return Math.Exp(x);
        else
            return Math.Exp(mid-(x-mid));
    }

    public static void Main(string[] args)
    {
        Console.WriteLine("{0}", TernarySearch(f, 0, 10, 1e-6));
    }
}
