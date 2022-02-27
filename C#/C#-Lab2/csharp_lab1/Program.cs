using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            Benzynowy b = new Benzynowy();
            b.UruchomSilnik(false);
            b.UruchomSilnik(true);
            b.UruchomSilnik(false);
            b.Tankuj(70f); //Zatankowany za 50
            b.Jedz();
            b.Jedz();

            Console.WriteLine();

            Elektryczny e = new Elektryczny();
            b.UruchomSilnik(true);
            e.Jedz();
            e.Jedz();
            e.Tankuj(250f);
        }
    }
}
