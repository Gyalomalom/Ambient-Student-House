using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace administratorsystem
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Start();
        }

        private void BtnAddStudent_Click(object sender, EventArgs e)
        {
            string student = textBox1.Text;

            lsbxStudents.Items.Add(student);
        }

        private void BtnRemoveStudent_Click(object sender, EventArgs e)
        {

        }

        private void BtnShowStudent_Click(object sender, EventArgs e)
        {

        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            lblTime.Text=(DateTime.Now.ToString());
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            timer1.Stop();
        }
    }
}
