
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 全屏截图
{
	/// <summary>
	/// Description of MainForm.
	/// </summary>
	public partial class jietu : Form
	{
		public jietu()
		{
			//
			// The InitializeComponent() call is required for Windows Forms designer support.
			//
			InitializeComponent();
			
			//
			// TODO: Add constructor code after the InitializeComponent() call.
			//
		}
		void MainFormLoad(object sender, EventArgs e)
		{
			pictureBox1.Image = GetImgDesk();
		}
		public static Bitmap GetImgDesk()
        {
            Rectangle rect = System.Windows.Forms.SystemInformation.VirtualScreen;
            //获取屏幕分辨率
            int x = rect.Width;
            int y = rect.Height;
            //截屏
            Bitmap img = new Bitmap(x, y);
            Graphics g = Graphics.FromImage(img);
            g.CopyFromScreen(new Point(0, 0), new Point(0, 0), new Size(x, y));
            return img;
        }
	}
}
