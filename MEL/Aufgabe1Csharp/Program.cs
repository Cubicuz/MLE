using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using Aufgabe1Csharp.Logik;

namespace Aufgabe1Csharp
{
    static class Program
    {
        /// <summary>
        /// Der Haupteinstiegspunkt für die Anwendung.
        /// </summary>
        [STAThread]
        static void Main()
        {
            TownAdministration t = new TownAdministration(true);
            HillClimber h = new HillClimber(ref t);
            Random r = new Random();
            int rounds = 0, random, oldrndom;
            double temp, newTemp, eps, newEps, lastlength, newlength;
            temp = 10000;
            double HCResult = 0, SAResult = 0;

            eps = 0.001;
            newTemp = temp;
            newEps = eps;
            oldrndom = 0;
            random = r.Next(0, 3);
            while (rounds < 10) {
                HCResult += h.HillClimb();
                h.Resett();
                SAResult += h.SimulatedAnnealing(temp, eps);
                h.Resett();
                rounds++;
            }

            Console.WriteLine("done ...");
            Console.WriteLine("HillClimber: " + HCResult / 10);
            Console.WriteLine("Simulated Annealing: " + SAResult / 10);
            Console.ReadKey();
//            Application.EnableVisualStyles();
//            Application.SetCompatibleTextRenderingDefault(false);
//            Application.Run(new Form1());
        }
    }
}
