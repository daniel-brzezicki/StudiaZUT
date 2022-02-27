using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public delegate void Dzialanie();


    public class Pralka
    {
        public bool wlaczona = false;
        public bool dodatkowePlukanie = false;

        public string WybranyProgram = null;

        public Pralka()
        {
            wlaczona = false;
        }

        ~Pralka() { }

        public void BawelnaZPW() { WybranyProgram = "Bawelna z praniem wstepnym"; Console.WriteLine(WybranyProgram); }
        public void Bawelna60() { WybranyProgram = "Bawelna 60st."; Console.WriteLine(WybranyProgram); }
        public void Bawelna40() { WybranyProgram = "Bawelna 40st."; Console.WriteLine(WybranyProgram); }
        public void BialeSyntetyki() { WybranyProgram = "Biale syntetyki 60st."; Console.WriteLine(WybranyProgram); }
        public void KolBawelna() { WybranyProgram = "Kolorowa bawelna 40st."; Console.WriteLine(WybranyProgram); }
        public void Bawelna20() { WybranyProgram = "Bawelna 20st."; Console.WriteLine(WybranyProgram); }
        public void MixLight() { WybranyProgram = "Mix light 20st. "; Console.WriteLine(WybranyProgram); }
        public void Odswiezanie() { WybranyProgram = "20' odswiezanie"; Console.WriteLine(WybranyProgram); }
        public void Jedwab() { WybranyProgram = "Jedwab/firanki 30st."; Console.WriteLine(WybranyProgram); }
        public void Welna() { WybranyProgram = "Welna 40 st."; Console.WriteLine(WybranyProgram); }
        public void Jeans() { WybranyProgram = "Jeans 40 st."; Console.WriteLine(WybranyProgram); }
        public void SportIntensive() { WybranyProgram = "Sport Intensive"; Console.WriteLine(WybranyProgram); }
        public void SportLight() { WybranyProgram = "Sport Light"; Console.WriteLine(WybranyProgram); }
        public void ObuwieSportowe() { WybranyProgram = "Obuwie sportowe"; Console.WriteLine(WybranyProgram); }
        public void DodatkowePlukanie() { Console.WriteLine("Dodatkowe plukanie"); }
        public void RozpoczeciePracy() { Console.WriteLine("Rozpoczecie prania"); }

        public void WyswietlWybor()
        {
            Console.WriteLine("-----Codzienne-----\n" +
                "1 - Bawelna z praniem wstepnym\n" +
                "2 - Bawelna 60st.\n" +
                "3 - Bawelna 40st.\n" +
                "4 - Biale syntetyki 60st.\n" +
                "5 - Kolorowa bawelna 40st.\n" +
                "-----Zone 20 stopni-----\n" +
                "6 - Bawelna 20st.\n" +
                "7 - Mix light 20st. \n" +
                "8 - 20' odswiezanie\n" +
                "-----Specjalne-----\n" +
                "9 - Jedwab/firanki 30st.\n" +
                "10 - Welna 40 st.\n" +
                "11 - Jeans 40 st.\n" +
                "-----Sportowe 30 stopni-----\n" +
                "12 - Sport Intensive\n" +
                "13 - Sport Light\n" +
                "14 - Obuwie sportowe\n" +
                "15 - START\n" +
                "Dodatkowe opcje:\n" +
                "16 - Dodatkowe plukanie");
        }

    }

   

    class Program
    {
        static void ToDo(Pralka pralka, Dzialanie dzialanie)
        {
            while (pralka.wlaczona == false)
            {
                Console.Clear();
                int key;
                pralka.WyswietlWybor();

                key = Convert.ToInt32(Console.ReadLine());

                switch (key)
                {
                    case 1: dzialanie = pralka.BawelnaZPW; break;
                    case 2: dzialanie = pralka.Bawelna60; break;
                    case 3: dzialanie = pralka.Bawelna40; break;
                    case 4: dzialanie = pralka.BialeSyntetyki; break;
                    case 5: dzialanie = pralka.KolBawelna; break;
                    case 6: dzialanie = pralka.Bawelna20; break;
                    case 7: dzialanie = pralka.MixLight; break;
                    case 8: dzialanie = pralka.Odswiezanie; break;
                    case 9: dzialanie = pralka.Jedwab; break;
                    case 10: dzialanie = pralka.Welna; break;
                    case 11: dzialanie = pralka.Jeans; break;
                    case 12: dzialanie = pralka.SportIntensive; break;
                    case 13: dzialanie = pralka.SportLight; break;
                    case 14: dzialanie = pralka.ObuwieSportowe; break;
                    case 15:
                        Console.Clear();
                        if (dzialanie != null && dzialanie != pralka.DodatkowePlukanie)
                        {
                            dzialanie += pralka.RozpoczeciePracy;
                            dzialanie.Invoke();
                            pralka.wlaczona = true;
                        }
                        break;
                    case 16:
                        if (!pralka.dodatkowePlukanie)
                            dzialanie += pralka.DodatkowePlukanie;
                        else
                            dzialanie -= pralka.DodatkowePlukanie;
                        break;
                }
            }
        }

        static void Main(string[] args)
        {
            Pralka pralka = new Pralka();

            Dzialanie dzialanie = null;

            ToDo(pralka, dzialanie);
        }
    }
}
