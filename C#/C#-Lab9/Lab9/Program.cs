using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Lab9
{
    public delegate void Delegat(string path, string target);

    public class Files
    {
        Delegat delegat = null;

        public Files(string path, string target)
        {
            delegat += ShowFiles;
            delegat(path, target);
        }


        static void ShowFiles(string path, string target)
        {
            if (!System.IO.Directory.Exists(path))
            {
                path = System.IO.Directory.GetCurrentDirectory();
            }

            if (!System.IO.Directory.Exists(target))
            {
                System.IO.Directory.CreateDirectory(target);
            }


            //Specify what files are we looking for
            string[] files = System.IO.Directory.GetFiles(path, "*.jpg");

            //Files found in path
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

                //wrzucenie do innego folderu
                System.IO.DirectoryInfo directory = new System.IO.DirectoryInfo(path);
                Console.WriteLine("{0}", directory);

                string FileName = $"{fileInfo.CreationTimeUtc}" + $"{directory.Name}.jpg";
                FileName = string.Concat(FileName.Split(Path.GetInvalidFileNameChars()));
                string FullPath = System.IO.Path.Combine(target, FileName);

                if (!File.Exists(FullPath))
                {
                    File.Copy(s, FullPath);
                    Console.WriteLine("[INFO] Skopiowano zdjecie: {0}", FullPath);
                }
                else
                {
                    Console.WriteLine("[OSTRZEZENIE] To zdjecie juz isnieje");
                }

            }


            string[] directories = System.IO.Directory.GetDirectories(path);

            //Enter every subdir
            foreach (string s in directories)
            {
                //ShowFiles(s, target);
                if (s != target)
                {
                    ShowFiles(s, target);
                }
            }
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Podaj sciezke przeszukania: ");
            //C:\Users\danie\source\repos\Lab9
            string pathToCheck = Console.ReadLine();

            Console.WriteLine("Podaj sciezke wyjscia: ");
            //C:\Users\danie\source\repos\Lab9\wyjscie
            string destination = Console.ReadLine();


            Files fil = new Files(pathToCheck, destination);
        }
    }
}
