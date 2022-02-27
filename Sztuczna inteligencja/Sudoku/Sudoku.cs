using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AISearch;
using System.Diagnostics;
using System.Threading;


namespace SIsudoku
{


    class Program
    {

        public class SudokuState : State
        {
            private readonly int n = 3;
            private int[,] table;
            public int GridLength
            {
                get { return this.n * this.n; }
            }
            public int[,] Table
            {
                get { return this.table; }
            }

            private string id;
            public override string ID
            {
                get { return this.id; }
            }

           public bool isValid(int row, int col, int v)
           {
                for (int i = 0; i < GridLength; i++)
                {
                    if (table[i, col] != 0 &&
                        table[i, col] == v)
                        return false;
                    if (table[row, i] != 0 &&
                        table[row, i] == v)
                        return false;
                    if (table[3 * (row / 3) + i / 3, 3 * (col / 3) + i % 3] != 0 &&
                        table[3 * (row / 3) + i / 3, 3 * (col / 3) + i % 3] == v)
                        return false;
                }
                return true;
           }

            

            public override double ComputeHeuristicGrade()
            {
                /*throw new NotImplementedException();
                {
                    throw new NotImplementedException();
                }*/
                /*for (int i = 0; i < GridLength; i++) do puzzli
                {
                    for(int j = 0; j < GridLength; j++)
                    {
                        //h = Math.Abs(i - table[i,j] / GridLength) + Math.Abs(j - table[i, j] % GridLength);
                    }
                }*/

                double h = 0.0;

                for (int i = 0; i < GridLength; i++)
                {
                    for (int j = 0; j < GridLength; j++)
                    {

                        if (table[i, j] == 0)
                        {
                            h++;
                        }
                    }
                }
                return h;
            }

            public SudokuState(int n, string sudokuPattern) : base()
            {
                this.n = n;

                if (sudokuPattern.Length != GridLength * GridLength)
                {
                    throw new ArgumentException("Niewlasciwa dlugosc sudoku");
                }

                this.id = sudokuPattern;
                this.table = new int[GridLength, GridLength];

                for (int i = 0; i < GridLength; i++)
                {
                    for (int j = 0; j < GridLength; j++)
                    {
                        this.table[i, j] = sudokuPattern[i * GridLength + j] - 48;
                    }
                }
                this.h = ComputeHeuristicGrade();
            }

            public SudokuState(SudokuState parent,int newValue,int x ,int y):base(parent)
            {
                this.table = new int[GridLength, GridLength];

                Array.Copy(parent.table, this.table, this.table.Length);
                this.table[x, y] = newValue;

                StringBuilder buldier = new StringBuilder(parent.id);
                buldier[x * GridLength + y] = (char)(newValue + 48);

                this.id = buldier.ToString();
                this.h = ComputeHeuristicGrade();
            }

            public void SudokuPrint()
            {
                Console.Write("\n");
                for (int i = 0; i < GridLength; i++)
                {
                    if (i % 3 == 0 && i!=0)
                        Console.WriteLine("\n---|---|---");
                    else
                        Console.Write("\n");
                    for (int j = 0; j < GridLength; j++) {
                        if (j % 3 == 0 && j!=0) Console.Write("|");
                        if(table[i, j]==0)
                            Console.Write(" ");
                        else
                            Console.Write(table[i,j]);
                    }
                }
                Console.Write("\n");
            }

        }

        public class SudokuSearch : BestFirstSearch
        {
            public SudokuSearch(SudokuState state) : base(state) { }
            protected override void buildChildren(IState parent)
            {
                SudokuState state = (SudokuState)parent;

                for (int i = 0; i <state.GridLength; i++)
                {
                    for (int j = 0; j < state.GridLength; j++)
                    {
                        if (state.Table[i, j] == 0)
                        {
                            for(int k = 1; k < state.GridLength + 1; k++)
                            {
                                if (state.isValid(i, j, k))
                                {
                                    SudokuState child = new SudokuState(state, k, i, j);
                                    parent.Children.Add(child);
                                }
                            }
                            return;
                        }
                    }
                }
            }
            protected override bool isSolution(IState state)
            {
                return state.H == 0.0;
            }
        }


        static void Main(string[] args)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            string sudokuPattern = "000012034000056017000000000000000000480000051270000048000000000350061000760035000";//"800030000930007000071520900005010620000050000046080300009076850060100032000040006";//"000000600600700001401005700005900000072140000000000080326000010000006842040002930";//"000012034000056017000000000000000000480000051270000048000000000350061000760035000";//"385000000921000000647000000000123000000784000000695000000000873000000962000000145";

            SudokuState startState = new SudokuState(3,sudokuPattern);
            startState.SudokuPrint();

            SudokuSearch searcher = new SudokuSearch(startState);
            searcher.DoSearch();

            IState state = searcher.Solutions[0];
            List<SudokuState> solutionPath = new List<SudokuState>();

            while (state != null)
            {
                solutionPath.Add((SudokuState)state);
                state = state.Parent;
            }

            solutionPath.Reverse();
            foreach(SudokuState s in solutionPath)
            {
                s.SudokuPrint();
            }

            Console.WriteLine("Open: " + searcher.Open.Count);
            Console.WriteLine("Closed: " + searcher.Closed.Count);
            stopwatch.Stop();
            Console.WriteLine("Time: " + stopwatch.ElapsedMilliseconds+"ms");
            Console.WriteLine();
        }
    }
}
