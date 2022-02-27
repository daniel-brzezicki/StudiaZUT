using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AISearch;
using System.Diagnostics;
using System.Threading;


namespace SIConnect4
{


    class Program
    {

        public class CState : State
        {
            private readonly int n = 6;
            private readonly int[,] table;
            private int turn = 0;

            private string id;

            public double heur = 0;

            public int GRID_SIZE
            {
                get { return this.n - 3; }
            }

            public int GridLength
            {
                get { return this.n * this.n; }
            }

            public int Size
            {
                get { return this.n; }
            }

            public int[,] Table
            {
                get { return table; }
            }

            public override string ID
            {
                get { return this.id; }
            }

            public int Turn
            {
                get { return turn; }
            }

            public void swapTurn()
            {
                if (turn == 1)
                    turn = 2;
                else
                    turn = 1;
            }

            public void setHeuristic(double h)
            {
                heur = h;
            }

            public override double ComputeHeuristicGrade()
            {
                double result = 0;

                double h = 0;
                double middle = n / 2;

                for (int row = 0; row < n; row++)
                {
                    for (int column = 0; column < n; column++)
                    {
                        if (table[row, column] == 2)
                        {
                            double distance = Math.Abs(column - middle);
                            if (distance <= 1.5)
                            {
                                h -= 10;
                            }
                            else if (distance <= 2.5)
                            {
                                h -= 5;
                            }
                            else if (distance <= 3.5)
                            {
                                h -= 1;
                            }
                        }
                    }
                }


                double h1 = 0;
                middle = n / 2;


                if (turn == 2)
                {
                    RemoveTopCoin(column, 2);
                    DropCoinSafe(1, column);


                    for (int row = 0; row < n; row++)
                    {
                        for (int column = 0; column < n; column++)
                        {
                            if (table[row, column] == 1)
                            {
                                double distance = Math.Abs(column - middle);
                                if (distance <= 1.5)
                                {
                                    h1 -= 10;
                                }
                                else if (distance <= 2.5)
                                {
                                    h1 -= 5;
                                }
                                else if (distance <= 3.5)
                                {
                                    h1 -= 1;
                                }
                            }
                        }
                    }


                    if (getWinner() == 2)
                    {
                        h = double.NegativeInfinity;
                    }
                    else if (getWinner() == 1)
                    {
                        h1 = double.NegativeInfinity;
                    }

                    RemoveTopCoin(column, 1);
                    DropCoinSafe(2, column);
                }


                if (getWinner() == 2)
                {
                    h = double.NegativeInfinity;
                }
                else if (getWinner() == 1)
                {
                    h1 = double.NegativeInfinity;
                }


                if (h1 < h)
                    result = h1;
                else
                    result = h;

                this.h = result;
                return this.h;
            }



            public CState(string pattern, int turn) : base()
            {
                this.table = new int[n, n];

                this.turn = turn;
                this.depth = 0.5f;

                for (int i = 0; i < Size; i++)
                {
                    for (int j = 0; j < Size; j++)
                    {
                        table[i, j] = pattern[i + j * Size] - '0';
                    }
                }
                turn = 2;

                this.id = CreateID();


                this.h = ComputeHeuristicGrade();
            }

            int column = 0;
            public CState(string pattern, int column, int turn) : base()
            {
                this.table = new int[n, n];

                this.depth = 0.5f;
                this.turn = turn;

                for (int i = 0; i < Size; i++)
                {
                    for (int j = 0; j < Size; j++)
                    {
                        table[i, j] = pattern[(j * Size) + i] - '0';
                    }
                }

                if (CanPlace(column))
                {
                    this.DropCoin(turn, column);
                }

                this.id = CreateID();

                this.rootMove = CreateID();

                this.column = column;

                this.h = ComputeHeuristicGrade();



            }


            string CreateID()
            {

                string tableStr = "";
                for (int j = 0; j < n; j++)
                {
                    for (int i = 0; i < n; i++)
                    {
                        tableStr += table[i, j].ToString();
                    }
                }

                return tableStr;
            }


            public bool DropCoinSafe(int playerId,int column)
            {

                int row = 0;
                while (row < n && table[column, row] == 0)
                {
                    row++;
                }

                if (row == 0)
                    return false;
                table[column, row - 1] = playerId;


                return true;
            }

            public bool DropCoin(int playerId, int column)
            {
                int row = 0;
                while (row < n && table[column, row] == 0)//!table[column, row].HasValue)
                {
                    row++;
                }

                if (row == 0)
                    return false;
                table[column, row - 1] = playerId;

                this.id = CreateID();
                this.rootMove = CreateID();
                return true;
            }

            public bool RemoveTopCoin(int column, int toRemove)
            {
                int row = 0;
                while (row < n && table[column, row] == 0)//!table[column, row].HasValue)
                {
                    row++;
                }

                if (row == n)
                    return false;
                if (table[column, row] == toRemove)
                {
                    table[column, row] = 0;
                    return true;
                }
                else
                    return false;
                //_changed = true;
                //return true;
            }

            public int getWinner()
            {

                 int _winner = 0;

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (table[i, j] == 0)// || table[i, j] != 2)
                            continue;

                        bool horizontal = i + 3 < n;
                        bool vertical = j + 3 < n;

                        if (!horizontal && !vertical)
                            continue;

                        bool forwardDiagonal = horizontal && vertical;
                        bool backwardDiagonal = vertical && i - 3 >= 0;

                        if (table[i, j] != 0)
                        {
                            for (int k = 1; k < 4; k++)
                            {
                                horizontal = (horizontal && table[i, j] == table[i + k, j]);
                                vertical = (vertical && table[i, j] == table[i, j + k]);
                                forwardDiagonal = (forwardDiagonal && table[i, j] == table[i + k, j + k]);
                                backwardDiagonal = (backwardDiagonal && table[i, j] == table[i - k, j + k]);
                                if (!horizontal && !vertical && !forwardDiagonal && !backwardDiagonal)
                                    break;
                            }
                        }

                        if (horizontal || vertical || forwardDiagonal || backwardDiagonal)
                        {
                            //_winner = table[i, j];
                            return table[i, j];
                        }

                    }
                }
                return _winner;

            }

            public bool checkWinner()
            {

                // int _winner = 0;

                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        if (table[i, j] == 0)// || table[i, j] != 2)
                            continue;

                        bool horizontal = i + 3 < n;
                        bool vertical = j + 3 < n;

                        if (!horizontal && !vertical)
                            continue;

                        bool forwardDiagonal = horizontal && vertical;
                        bool backwardDiagonal = vertical && i - 3 >= 0;

                        if (table[i, j] != 0)
                        {
                            for (int k = 1; k < 4; k++)
                            {
                                horizontal = (horizontal && table[i, j] == table[i + k, j]);
                                vertical = (vertical && table[i, j] == table[i, j + k]);
                                forwardDiagonal = (forwardDiagonal && table[i, j] == table[i + k, j + k]);
                                backwardDiagonal = (backwardDiagonal && table[i, j] == table[i - k, j + k]);
                                if (!horizontal && !vertical && !forwardDiagonal && !backwardDiagonal)
                                    break;
                            }
                        }

                        if (horizontal || vertical || forwardDiagonal || backwardDiagonal)
                        {
                            //_winner = table[i, j];
                            return true;//_winner;
                        }

                    }
                }
                return false;

            }
            public bool CanPlace(int j)
            {

                for (int i = 0; i < n; i++)
                {

                    if (table[j, i] == 0)
                    {
                        return true;
                    }
                }

                return false;
            }

            public bool IsFull
            {
                get
                {
                    for (int i = 0; i < n; i++)
                    {
                        if (table[i, 0] == 0)
                            return false;
                    }

                    return true;
                }
            }



            public string Print()
            {
                var builder = new StringBuilder();
                for (int j = 0; j < n; j++)
                {
                    builder.Append('|');
                    for (int i = 0; i < n; i++)
                    {
                        builder.Append(table[i, j] != 0 ? table[i, j].ToString() : " ").Append('|');
                    }
                    builder.AppendLine();
                }
                builder.Append("\n|1|2|3|4|5|6|\n");

                return builder.ToString();
            }

        }

        public class CSearch : AlphaBetaSearcher
        {
            string p;
            int turn;
            public CSearch(CState state, bool isMaximizingPlayerFirst, double maximumDepth, string pattern, int turn) : base(state, isMaximizingPlayerFirst, maximumDepth)
            {
                p = pattern;
                this.turn = turn;
            }


            protected override void buildChildren(IState parent)
            {
                List<IState> children = new List<IState>();

                for (int i = 0; i < 6; i++)
                {

                    CState child = new CState(p, i, turn);
                    if (child != null)
                    {

                        children.Add(child);
                    }
                }

                parent.Children.Clear();
                foreach (CState s in children)
                {
                    parent.Children.Add(s);
                }

            }

        }

        public static int swapt(int turn)
        {
            if (turn == 2)
                return 1;
            else
                return 2;
        }

        static void Main(string[] args)
        {

            int turn = 1;
            string lastState = "000000000000000000000000000000000000";

            while (true)
            {
                turn = swapt(turn);

                CState startState = new CState(lastState, turn);
                Console.WriteLine(startState.Print());

                Console.WriteLine("Pick a column 1-6");
                int move;

                if (startState.IsFull)
                {
                    Console.WriteLine(startState.Print());
                    Console.WriteLine("Tie!");
                    break;
                }

                if (turn == 1)
                {

                    move = int.Parse(Console.ReadLine());
                    if (move <= 6)
                        startState.DropCoin(turn, move - 1);


                    //Console.Write(startState.Print());
                    lastState = startState.RootMove;
                }

                if (turn == 2)
                {
                    CState AIState = new CState(lastState, turn);


                    double tmax = Double.PositiveInfinity;
                    int AI_move = 0;

                    int counter = 0;





                    CSearch searcher = new CSearch(AIState, false, startState.Depth, lastState,turn);
                    searcher.DoSearch();


                    foreach (KeyValuePair<string, double> kvp in searcher.MovesMiniMaxes)
                    {

                        String key = kvp.Key;
                        Double max = kvp.Value;


                        Console.WriteLine(counter + " " + key);
                        Console.WriteLine(counter + " " + max);
                        if (max < tmax)
                        {
                            Console.WriteLine("new min " + key);
                            Console.WriteLine("new min " + max);
                            AI_move = counter;
                            tmax = max;
                            lastState = key;
                        }

                        counter++;
                    }
                }

                CState s = new CState(lastState, turn);

                if (s.checkWinner())
                {
                    Console.WriteLine("WINNNER " + (turn == 1 ? "Player" : "Ai"));
                    Console.WriteLine(s.Print());
                    Environment.Exit(0);
                    break;
                }

            }
        }
    }
}

