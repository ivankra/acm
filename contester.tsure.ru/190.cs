using System;

public class Program
{
    string input;
    int p;

    int Factorial(int n) {
        return n == 0 ? 1 : n * Factorial(n - 1);
    }

    int Factor() {
        int res = 0;
        if (input[p] == '1') {
            res = 1;
            p++;
        } else if (input[p] == '(') {
            p++;
            res = Expr();
            if (input[p] == ')') p++;
        }

        while (input[p] == '!') {
            p++;
            res = Factorial(res);
        }

        return res;
    }

    int Term() {
        int res = Factor();
        while (input[p] == '*') {
            p++;
            res *= Factor();
        }
        return res;
    }

    int Expr() {
        int res = Term();
        while (input[p] == '+') {
            p++;
            res += Term();
        }
        return res;
    }

    void Run()
    {
        input = Console.ReadLine() + "$";
        p = 0;
        Console.WriteLine(Expr());
    }

    public static void Main(string[] args) {
        new Program().Run();
    }
}
