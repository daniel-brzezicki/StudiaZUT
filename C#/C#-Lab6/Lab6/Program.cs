using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


namespace Lab6
{
    class Matrix
    {
        float[,] A;
        int size;

        public Matrix(string path)
        {

            CreateMatrix(path);
        }

        public void CreateMatrix(string path)
        {
            string[] readText = File.ReadAllLines(path);


            for (int i = 0; i < readText.Length; i++)
            {
                readText[i] += ';';
            }


            string inLine = string.Concat(readText);

            string[] splited = inLine.Split(';');


            int counter = 0;
            this.size = int.Parse(splited[counter]);

            A = new float[size, 2 * size+1];
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size+1; j++)
                {
                    counter++;
                    A[i, j] = float.Parse(splited[counter]);
                }

            }

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (i == j)
                    {
                        A[i, j + size+1] = 1;
                    }
                    else
                    {
                        A[i, j + size+1] = 0;
                    }
                }
            }

        }

        public void ShowMatrix()
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < 2 * size+1; j++)
                {
                    if (A[i, j] < 0)
                        Console.Write(A[i, j] + " ");
                    else
                        Console.Write(A[i, j] + "  ");
                }
                Console.WriteLine();
            }
        }




        public void GaussSolve()
        {
            float ratio;


            for (int i = 0; i < size; i++)
            {
                if (A[i, i] == 0)
                    System.Environment.Exit(1);

                for (int j = 0; j < size; j++)
                {
                    if (i != j)
                    {
                        ratio = A[j, i] / A[i, i];
                        for (int k = 0; k < 2 * size + 1; k++)
                        {
                            A[j, k] = A[j, k] - ratio * A[i, k];
                        }
                    }
                }
            }


            for (int i = 0; i < size; i++)
            {
                for (int j = size; j < 2 * size + 1; j++)
                {
                    A[i, j] = A[i, j] / A[i, i];
                }
            }


            Console.Write("Wyniki to :\n");
            for (int i = 0; i < size; i++)
            {

                Console.Write($"x{i} = {A[i, size]} ");
                Console.WriteLine();
            }

        }
    }



    class Program
    {
        static void Main(string[] args)
        {

            string path = @"C:\Users\bd46477\source\repos\Lab6\Lab6\pliki\plik.csv";


            Matrix m = new Matrix(path);

            m.ShowMatrix();
            Console.WriteLine();

            m.GaussSolve();
            Console.WriteLine();


        }
    }
}

