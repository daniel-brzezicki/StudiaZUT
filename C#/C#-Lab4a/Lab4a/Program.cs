using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Lab4a
{
    class Program
    {

        static double Pole(double x1, double x2,double a, double b,double c, double n)
        {
            double x = (x2 - x1) / (double)n; //pierwszy bok
            double sumaPol = 0.0;
            double srodek = x1 + (x2 - x1) / (2.0 * n); //środek pierwszego boku

            for (int i = 0; i < n; i++)
            {
                sumaPol += f(srodek,a,b,c); //obliczenie wysokości prostokata
                srodek += x; //nastepny srodek
            }
            return sumaPol * x;
        }

        static double f(double x, double a, double b, double c)
        {
            return a * Math.Pow((x), 2) + b * x + c;
        }


        static void Main(string[] args)
        {
            double a, b,c, n ,x1,x2;
            Console.WriteLine("Wprowadz dane do funkcji ax2 + bx +c \na = ");
            a = double.Parse(Console.ReadLine());
            Console.WriteLine("b = ");
            b = double.Parse(Console.ReadLine());
            Console.WriteLine("c = ");
            c = double.Parse(Console.ReadLine());

            Console.WriteLine("Podaj przedial (x1,x2) \nx1 = ");
            x1 = double.Parse(Console.ReadLine());
            Console.WriteLine("x2 = ");
            x2 = double.Parse(Console.ReadLine());

            Console.WriteLine("Podaj liczbę prostokatow: ");
            n = double.Parse(Console.ReadLine());

            if (!(x1 < x2))
                Console.WriteLine("To nie jest przedział!");
            else
            {
                double p = Pole(x1,x2,a, b,c, n);
                Console.WriteLine(p);
            }

        }
    }
}
