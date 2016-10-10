using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Aufgabe1Csharp.Logik
{
    class Town
    {
        public readonly int x;
        public readonly int y;
        public String name;

        public Town(int x = 0, int y = 0, string name = "no Name")
        {
            this.x = x;
            this.y = y;
            this.name = name;
        }

        public double distance(ref Town t)
        {
            int deltax = Math.Abs(x - t.x);
            int deltay = Math.Abs(y - t.y);
            return Math.Sqrt(deltax * deltax + deltay * deltay);
        }
    }
}
