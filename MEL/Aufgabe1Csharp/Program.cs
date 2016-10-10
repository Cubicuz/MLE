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
            TownAdministration t = new TownAdministration();
            HillClimber h = new HillClimber(ref t);
            h.HillClimb();
            Console.ReadKey();
//            Application.EnableVisualStyles();
//            Application.SetCompatibleTextRenderingDefault(false);
//            Application.Run(new Form1());
        }
    }
}
