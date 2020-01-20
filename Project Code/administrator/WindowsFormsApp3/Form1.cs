using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp3
{
    public partial class Form1 : Form
    {

        List<string> studentName = new List<string>();
        List<int> AgeStudent = new List<int>();
        List<string> GenderStudent = new List<string>();
        List<string> School = new List<string>();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            timer1.Start();
            //serialPort1.Open();
        }

        private void BtnAddStudent_Click(object sender, EventArgs e)
        {
            string student = textBox1.Text;
            string school = txtbxSchool.Text;

            if (studentName.Contains(student))
            {
                MessageBox.Show("Student already exists");
            }
            else if (!studentName.Contains(student) && !string.IsNullOrEmpty(school))
            {
                if (checkMale.Checked)
                {

                    checkFemale.Checked = false;
                    listbox.Items.Add(student);

                    AddStudentMale();
                    clearItems();
                }
                else if (checkFemale.Checked)
                {

                    checkMale.Checked = false;
                    listbox.Items.Add(student);
                    AddStudentFemale();
                    clearItems();
                }
            }
            else
            {
                MessageBox.Show("Invalid!! Not all fields are filled in properly");
            }
        }

        private void BtnRemoveStudent_Click(object sender, EventArgs e)
        {
            string student = textBox2.Text;

            if (studentName.Contains(student))
            {
                listbox.Items.Remove(student);
                studentName.Remove(student);


            }
            else if (!studentName.Contains(student))
            {
                MessageBox.Show("student not found");
            }

        }

        private void BtnShowStudent_Click(object sender, EventArgs e)
        {
            string student = textBox2.Text;
            int studentIndex = studentName.IndexOf(student);

            lsbxShowInfo.Items.Clear();

            if (studentName.Contains(student))
            {
                lsbxShowInfo.Items.Add(studentName[studentIndex]);
                lsbxShowInfo.Items.Add(GenderStudent[studentIndex]);
                lsbxShowInfo.Items.Add(AgeStudent[studentIndex]);
                lsbxShowInfo.Items.Add(School[studentIndex]);
            }
            else
            {
                MessageBox.Show("student does not exist");
            }

        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            lblTime.Text = (DateTime.Now.ToString());

            //string command = serialPort1.ReadExisting().Trim();

            //if (command == "Alarm")
            //{
            //    pictureBox3.BackColor = Color.Red;
            //}
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            timer1.Stop();
            //serialPort1.Close();
        }

        void clearItems()
        {
            //
            textBox1.Clear();
            txtbxAge.Clear();
            txtbxSchool.Clear();
            checkMale.Checked = false;
            checkFemale.Checked = false;
        }

        void AddStudentMale()
        {
            string student = textBox1.Text;
            string school = txtbxSchool.Text;
            string genderMale = "Male";
            int age = Convert.ToInt32(txtbxAge.Text);

            //
            studentName.Add(student);
            AgeStudent.Add(age);
            School.Add(school);
            GenderStudent.Add(genderMale);
        }

        void AddStudentFemale()
        {
            string student = textBox1.Text;
            string school = txtbxSchool.Text;
            string genderFemale = "Female";
            int age = Convert.ToInt32(txtbxAge.Text);

            //
            studentName.Add(student);
            AgeStudent.Add(age);
            School.Add(school);
            GenderStudent.Add(genderFemale);
        }
    }
}
