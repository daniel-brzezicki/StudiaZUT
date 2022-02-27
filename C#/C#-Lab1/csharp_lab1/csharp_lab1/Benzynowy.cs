using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace csharp_lab1
{
    public class Benzynowy : Samochod
    {
        string RodzajPaliwa = "Benzyna";


        public override void Tankuj(float cena)
        {
            List<Paliwo> cenyPaliw = new List<Paliwo>(); 
            cenyPaliw = UstalCenyPaliw();

            foreach(Paliwo p in cenyPaliw)
            {
                if (RodzajPaliwa == p.nazwa)
                {
                    DodajDoBaku(cena / p.cena);

                    if (RodzajPaliwa == "Elektryk")
                        Console.WriteLine(RodzajPaliwa + " - Naladowano: " + Math.Round(cena / p.cena) + " kWh." );
                    else
                        Console.WriteLine(RodzajPaliwa + " - Zatankowano: " + Math.Round(cena / p.cena) + " l.");


                }
            }
        }
    }
}
