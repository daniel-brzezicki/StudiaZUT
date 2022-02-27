using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab8
{
    public delegate void Delegat(string path);

    public class Files
    {
        Delegat delegat = null;

        public Files(string path)
        {
            delegat += ShowFiles;
            delegat(path);
        }


        static void ShowFiles(string path)
        {
            if (!System.IO.Directory.Exists(path))
            {
                path = System.IO.Directory.GetCurrentDirectory();
            }

            Console.WriteLine("\n" + path);


            string[] files = System.IO.Directory.GetFiles(path, "*.*");
            Console.WriteLine("Files:");
            foreach (string s in files)
            {
                System.IO.FileInfo fileInfo = null;
                try
                {
                    fileInfo = new System.IO.FileInfo(s);
                }
                catch (System.IO.FileNotFoundException e)
                {
                    Console.WriteLine(e.Message);
                    continue;
                }
                Console.WriteLine("{0} : {1}", fileInfo.Name, fileInfo.Directory);
            }

            string[] directories = System.IO.Directory.GetDirectories(path);
            Console.WriteLine("Directories:");
            foreach (string s in directories)
            {
                System.IO.DirectoryInfo dirInfo = null;
                try
                {
                    dirInfo = new System.IO.DirectoryInfo(s);
                }
                catch (System.IO.FileNotFoundException e)
                {
                    Console.WriteLine(e.Message);
                    continue;
                }
                Console.WriteLine("{0} : {1}", dirInfo.Name, dirInfo.Attributes);

            }

            //Rekurencyjne wypisanie podfolderow
            foreach (string s in directories)
            {
                ShowFiles(s);
            }
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Podaj sciezke: ");
            string pathToCheck = Console.ReadLine();

            Files fil = new Files(pathToCheck);
        }
    }
}
