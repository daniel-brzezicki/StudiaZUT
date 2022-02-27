using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Lab3
{
    class Program
    {
        public static void Main()
        {
            string pathHTML = @"C:\Users\bd46477\source\repos\Lab3\Lab3\Pliki\MyTest.html";
            string path = @"C:\Users\bd46477\source\repos\Lab3\Lab3\Pliki\dokument.csv";

            string[] readText = File.ReadAllLines(path);

            int colsMax =1;

            //Wyliczenie ilosci kolumn (cols) oraz dodanie na końcu linijki ";"
            for(int i = 0; i < readText.Length; i++)
            {
                if (i == 0)
                {
                    foreach(char c in readText[i])
                    {
                        if (c == ';')
                            colsMax++;

                    }
                }

                readText[i] += ';';
            }

            //Zlepienie w jedna linie
            string inLine = string.Concat(readText);

            //Podzielenie
            string[] splited = inLine.Split(';');

            //Otworzenie pliku
            using (var HTMLTable = File.AppendText(pathHTML))
            {

                HTMLTable.WriteLine("<html><body><table>");
                int cols = 0;
                bool firstRow = true;


                //Przejscie przez kazdy element w splited
                foreach (var element in splited)
                {
                    //jezeli aktualna kolumna == kolumnie maksymalnej to zakończ wiersz
                    if (cols == colsMax)
                    {
                        HTMLTable.WriteLine("</tr>");
                        HTMLTable.WriteLine("<tr>");

                        cols = 0;

                        //Jezeli firstRow jest true to zmien jego wartosc -> teraz elementy beda zapisywane bez pogrubienia
                        if (firstRow)
                            firstRow = false;
                    }
                    cols++;

                    if (firstRow)
                        HTMLTable.WriteLine("<th>" + element + "</th>");
                    else
                        HTMLTable.WriteLine("<td>" + element + "</td>");
                }
                HTMLTable.WriteLine("</table></body></html>");
            }
        }
    }
}
