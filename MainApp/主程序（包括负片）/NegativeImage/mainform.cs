using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;


namespace NegativeImage
{
    public partial class mainform : Form
    {
        public mainform()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            fuguang frm_Main = new fuguang();
            frm_Main.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            SuavityImage.xuhua xuhua = new SuavityImage.xuhua();
            xuhua.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            ImageGrain.wenli wenli = new ImageGrain.wenli();
            wenli.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Mosaic.masaike frm_Main = new Mosaic.masaike();
            frm_Main.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Process process = Process.Start("weatherroport.exe");
            process.WaitForExit();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            _SCREEN_CAPTURE.FrmCapture frmCapture = new _SCREEN_CAPTURE.FrmCapture();
            frmCapture.Show();
        }
    }
}
