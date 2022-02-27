using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;
using AISearch;

namespace Exercise {
    class Program
    {
        public enum Direction
        {
            Left,
            Right,
            Down,
            Up
        }


        public class PuzzleState : State
        {
            private readonly int n = 3;
            public int[,] table;

            public int Heuristic;
            public int GridLength
            {
                get { return this.n; }
            }
            public int[,] Table
            {
                get { return this.table; }
            }

            public string id;
            public override string ID
            {
                get { return this.id; }
            }


            public PuzzleState(PuzzleState ps)
            {
                this.table = ps.table;
                this.Heuristic = ps.Heuristic;
                this.id = ps.id;
            }

            public PuzzleState(int n, int whichHeuristic) : base()
            {
                this.n = n;

                this.table = new int[GridLength, GridLength];

                int num = 0;

                this.Heuristic = whichHeuristic;

                string pattern = "";
                for (int i = 0; i < GridLength; i++)
                {
                    for (int j = 0; j < GridLength; j++)
                    {
                        pattern += num.ToString();
                        this.table[i, j] = num;
                        num++;
                    }
                }

                StringBuilder buldier = new StringBuilder(pattern);


                this.id = buldier.ToString();
                this.h = ComputeHeuristicGrade();
            }


            public PuzzleState(PuzzleState parent, int nullPos, int newPos) : base(parent)
            {
                this.table = new int[GridLength, GridLength];


                Array.Copy(parent.table, this.table, this.table.Length);

                ChangePos(nullPos, newPos);

                StringBuilder buldier = new StringBuilder(parent.id);
                char v = buldier[nullPos];
                buldier[nullPos] = buldier[newPos];
                buldier[newPos] = v;

                //Print();

                this.id = buldier.ToString();
                this.h = ComputeHeuristicGrade();
            }

            public bool isMoveValid(int pos, Direction dir)
            {
                if (pos / GridLength == (n - 1)){
                    if (dir == Direction.Down)
                        return false;
                    else if (pos % GridLength == 0 && dir == Direction.Left)
                        return false;
                    else if (pos % GridLength == GridLength-1 && dir == Direction.Right)
                        return false;
                }
                else if (pos / GridLength == 0)
                {
                    if (dir == Direction.Up)
                        return false;
                    else if (pos % GridLength == 0 && dir ==Direction.Left)
                        return false;
                    else if (pos % GridLength == GridLength - 1 && dir == Direction.Right)
                        return false;

                }
                else
                {
                    if (pos / GridLength == 0 && dir == Direction.Left)
                        return false;
                    else if (pos % GridLength == GridLength - 1 && dir == Direction.Right)
                        return false;
                }
   

                return true;
            }

            public bool canMove(int destPos)
            {
                int pos = 0;
                for (int i = 0; i < table.Length; i++)
                {
                    for (int j = 0; j < table.Length; j++)
                    {
                        if (pos == destPos && pos == table[i, j])
                        {
                            return true;
                        }
                        pos++;
                    }
                }
                return false;
            }

            public int move(Direction dir)
            {
                if (dir == Direction.Left) return -1;
                else if (dir == Direction.Right) return 1;
                else if (dir == Direction.Up) return -n;
                else return n;
            }


            public override double ComputeHeuristicGrade()
            {
                double h = 0.0;
                if (Heuristic == 1)
                {

                    for (int i = 0; i < GridLength; i++)
                    {
                        for (int j = 0; j < GridLength; j++)
                        {
                            if (table[i, j] != i+j)
                            {
                                h += Math.Abs(i - table[i, j] / GridLength) + Math.Abs(j - table[i, j] % GridLength);
                            }
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < GridLength; i++)
                    {
                        for (int j = 0; j < GridLength; j++)
                        {
                            if (table[i, j] != i + j)
                            {
                                h++;
                            }
                        }
                    }
                }

                return h;
            }

            public int GetNullPuzzle()
            {
                int pos = 0;
                for(int i = 0; i < GridLength; i++)
                {
                    for(int j = 0; j < GridLength; j++)
                    {
                        if (table[i, j] == 0)
                            return pos;

                        pos++;
                    }
                }
                return 0;
            }

            public void ShufflePuzzle(int shuffleNum)
            {
                Random r = new Random();

                for(int i = 0; i < shuffleNum; i++)
                {
                    int random = Math.Abs(r.Next() % 4);
                    int nullPos = GetNullPuzzle();

                    Direction dir = (Direction)random;

                    if (!isMoveValid(nullPos, dir))
                    {
                        i--;
                        continue;
                    }

                    int newPos = nullPos + move(dir);
                    ChangePos(nullPos, newPos);

                }
            }

            public void ChangePos(int p1,int p2)
            {
                int p1value = table[p1 / n, p1 % n];
                int p2value = table[p2 / n, p2 % n];

                table[p1 / n, p1 % n] = p2value;
                table[p2 / n, p2 % n] = p1value;
            }

            public void Print()
            {
                Console.Write("\n");
                for (int i = 0; i < GridLength; i++)
                {
                    for (int j = 0; j < GridLength; j++)
                    {
                        if (table[i, j] == 0)
                            Console.Write(" ");
                        else
                            Console.Write(table[i, j]);

                        if(j+1==GridLength)
                            Console.Write("\n");
                    }
                }
                Console.Write("\n");
            }

        }

        public class PuzzleSearch : AStarSearch
        {
            public PuzzleSearch(PuzzleState state) : base(state) {}
            protected override void buildChildren(IState parent)
            {
                PuzzleState state = (PuzzleState)parent;

                for (int i = 0; i < 4; i++) {
                    int nullPos = state.GetNullPuzzle();


                    if (state.isMoveValid(nullPos, (Direction)i)){
                        int calculationPos = nullPos + state.move((Direction)i);

                        PuzzleState child = new PuzzleState(state, nullPos, calculationPos);
                        parent.Children.Add(child);
                    }
                }
            }
            protected override bool isSolution(IState state)
            {

                PuzzleState puzzleState = (PuzzleState)state;
                int pos = 0;
                for (int i = 0; i < puzzleState.GridLength; i++)
                {
                    for (int j = 0; j < puzzleState.GridLength; j++)
                    {
                        if (pos != puzzleState.table[i, j])
                            return false;
                        pos++;
                    }
                }

                return true;
            }
        }


        public class Info
        {
            public List<int> openHeuristic1;
            public List<int> closedHeuristic1;

            public List<int> openHeuristic2;
            public List<int> closedHeuristic2;

            public List<long> HeuristicTime1;
            public List<long> HeuristicTime2;

            public Info()
            {
                openHeuristic1 = new List<int>();
                closedHeuristic1 = new List<int>();

                openHeuristic2 = new List<int>();
                closedHeuristic2 = new List<int>();

                HeuristicTime1 = new List<long>();
                HeuristicTime2 = new List<long>();
            }


            public void Search(PuzzleState ps)
            {
                Stopwatch stopwatch = new Stopwatch();
                stopwatch.Start();




                PuzzleSearch searcher = new PuzzleSearch(ps);
                searcher.DoSearch();

                IState state = searcher.Solutions[0];
                List<PuzzleState> solutionPath = new List<PuzzleState>();

                while (state != null)
                {
                    solutionPath.Add((PuzzleState)state);
                    state = state.Parent;
                }

                solutionPath.Reverse();
                /*foreach (PuzzleState s in solutionPath)
                {
                    s.Print();
                }*/


                //Console.WriteLine("Open: " + searcher.Open.Count);
                //Console.WriteLine("Closed: " + searcher.Closed.Count);
                stopwatch.Stop();
                //Console.WriteLine("Time: " + stopwatch.ElapsedMilliseconds + "ms");
                //Console.WriteLine();

                if (ps.Heuristic == 1)
                {
                    openHeuristic1.Add(searcher.Open.Count);
                    closedHeuristic1.Add(searcher.Closed.Count);

                    HeuristicTime1.Add(stopwatch.ElapsedMilliseconds);
                }
                else if (ps.Heuristic == 0)
                {
                    openHeuristic2.Add(searcher.Open.Count);
                    closedHeuristic2.Add(searcher.Closed.Count);
                    HeuristicTime2.Add(stopwatch.ElapsedMilliseconds);
                }

            }

            public void CalculateDifferences()
            {
                double sumOpen1 = 0;
                foreach (int open1 in openHeuristic1)
                {
                    sumOpen1 += open1;
                }

                double sumOpen2 = 0;
                foreach (int open2 in openHeuristic2)
                {
                    sumOpen2 += open2;
                }

                double sumClosed1 = 0;
                foreach (int closed1 in closedHeuristic1)
                {
                    sumClosed1 += closed1;
                }


                double sumClosed2 = 0;
                foreach (int closed2 in closedHeuristic2)
                {
                    sumClosed2 += closed2;
                }


                double sumTime1 = 0;
                foreach (long t in HeuristicTime1)
                {
                    sumTime1 += t;
                }

                double sumTime2 = 0;
                foreach (long t in HeuristicTime2)
                {
                    sumTime2 += t;
                }


                Console.WriteLine("Heurystyka manhatan sr. open: " + sumOpen1 / openHeuristic1.Count);
                Console.WriteLine("Heurystyka manhatan sr. closed: " + sumClosed1 / closedHeuristic1.Count);
                Console.WriteLine("Heurystyka manhatan sr. czas: " + (double)(sumTime1 / HeuristicTime1.Count));


                Console.WriteLine("Heurystyka zliczanie sr. open: " + sumOpen2 / openHeuristic2.Count);
                Console.WriteLine("Heurystyka zliczanie sr. closed: " + sumClosed2 / closedHeuristic2.Count);
                Console.WriteLine("Heurystyka zliczanie sr. czas: " + (double)(sumTime2 / HeuristicTime2.Count));
            }
        }

       

        static void Main(string[] args)
        {

            Info info = new Info();
            for (int i = 0; i < 100; i++)
            {
                PuzzleState startState = new PuzzleState(3, 0);

                startState.ShufflePuzzle(10);

                PuzzleState startStateDifferentHeuristic = new PuzzleState(startState);
                startState.Heuristic = 1;

                info.Search(startState);
                info.Search(startStateDifferentHeuristic);
            }
            info.CalculateDifferences();



        }
    }
}
