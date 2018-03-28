using System;
using System.IO;

namespace life
{
    class Program
    {
        static bool  IsNeightborAlive(bool[,] a, int x, int  y, int dx,int dy)
        {
            int lx = a.GetLength(0);
            int ly = a.GetLength(1);

            int rx = (x + dx + lx) % lx;
            int ry = (y + dy + ly) % ly;

            return a[rx, ry];
        }
        static int Neighbors(bool[,] a , int x, int y)
        {
            int r = 0;
            if (IsNeightborAlive(a, x, y, -1, -1)) r++;
            if (IsNeightborAlive(a, x, y, 0, -1)) r++;
            if (IsNeightborAlive(a, x, y, 1, -1)) r++;
            if (IsNeightborAlive(a, x, y, -1, 0)) r++;
            if (IsNeightborAlive(a, x, y, 1, 0)) r++;
            if (IsNeightborAlive(a, x, y, -1, 1)) r++;
            if (IsNeightborAlive(a, x, y, 0, 1)) r++;
            if (IsNeightborAlive(a, x, y, 1, 1)) r++;
            return r;
        }
        static void Main()
        {
            Console.SetIn(File.OpenText("in.txt"));
            string[] size = Console.ReadLine().Split(' ');
            int m = int.Parse(size[0]);
            int n = int.Parse(size[1]);
            int k = int.Parse(size[2]);

            bool[,] a = new bool[n, m];

            for(int j = 0; j<n; j++)
            {
                string line = Console.ReadLine();
                for (int i =0; i<n; i++)
                {
                    a[i, j] = line[i] == '1';
                    
                }
            }
            bool[,] b = new bool[n, m];

            for (int c = 0; c < k ; c++)
            {
                for (int j = 0; j < n; j++)
                {
                    for (int i = 0; i < n; i++)
                    {
                        int ns = Neighbors(a, i, j);
                        if (a[i, j])
                        {
                            if (ns == 2 || ns == 3)
                            {
                                b[i, j] = true;
                            }
                            else
                                b[i, j] = false;
                        }
                        else
                        {
                            if (ns == 3)
                            {
                                b[i, j] = true;
                            }
                            else
                                b[i, j] = false;
                        }
                    }
                }
                var t = a;
                a = b;
                b = t;
            }

            for (int j = 0; j < n; j++)
            {
                
                for (int i = 0; i < n; i++)
                {
                    Console.Write(a[i,j] ? '1' : '0');

                }
                Console.WriteLine();
            }
        }
    }
}
