using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Aufgabe1Csharp.GUI
{
    public partial class TownMapPanel : UserControl
    {
        public TownMapPanel()
        {
            InitializeComponent();
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.TownMapPanel_Paint);
        }

        private void TownMapPanel_Load(object sender, EventArgs e)
        {

        }

        private void TownMapPanel_Paint(object sender, EventArgs e)
        {
            
        }
    }
}
