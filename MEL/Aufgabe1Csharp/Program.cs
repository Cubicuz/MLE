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
            int rounds = 0, random;
            double temp, newTemp, eps, newEps;
            temp = 5;
            double HCResult = 0, SAResult = 0;
            double hc, sa;
            eps = 0.000001;
            newTemp = temp;
            newEps = eps;
            random = r.Next(0, 3);
            while (rounds < 10) {
                hc = 0; // h.HillClimb((int)(temp / eps));
                HCResult += hc;
                h.Resett();
                sa = h.SimulatedAnnealing(temp, eps);
                SAResult += sa;
                h.Resett();
                rounds++;
                Console.WriteLine("------- " + rounds);
                Console.WriteLine("HC: " + hc);
                Console.WriteLine("SA: " + sa);
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
