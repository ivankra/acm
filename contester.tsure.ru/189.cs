using System;

public class Program
{
    public static void Main(string[] args) {
        string s = Console.ReadLine();
        int n = int.Parse(Console.ReadLine());

        for (int i = s.Length - 1; i >= 0 && s[i] != '='; --i)
            if (s[i] == '1') n--;

        if (n == 0)
            Console.WriteLine("Congratulations, correct answer");
        else
            Console.WriteLine("Wrong answer, try again");
    }
}
