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
        List<int> rooms = new List<int>();

        List<string> studentName = new List<string>();
        List<int> AgeStudent = new List<int>();
        List<string> School = new List<string>();

        public Form1()
        {
            InitializeComponent();

        }


        private void ButtonAddStudent_Click(object sender, EventArgs e)
        {
            string name = textBox1.Text;
            string school = textBox2.Text;
            int RoomNumber = Convert.ToInt32(textBox4.Text);
            string age = textBox3.Text;

            if (studentName.Contains(name))
            {
                MessageBox.Show("Student already exists");
            } else if(rooms.Contains(RoomNumber))
                 {
                MessageBox.Show("room already occupied");
            }
            else if (!studentName.Contains(name) && !string.IsNullOrEmpty(school))
            {
                AddStudentMale();
                clearItems();

                listBox1.Items.Add(RoomNumber);

            }
        }

        private void ButtonRemoveStudent_Click(object sender, EventArgs e)
        {
            //for (int i = listBox1.SelectedIndices.Count -1; i>= 0; i--)
            //{
            //    listBox1.Items.RemoveAt(listBox1.SelectedIndices[i]);
            //}

            //listBox1.Items.Remove(listBox1.SelectedItem);
            //rooms.Remove(listBox1.SelectedIndex);
            //studentName.Remove(listBox1.SelectedIndex.ToString());

            int room = Convert.ToInt32(textBox2.Text);

            int studentInfo = rooms.IndexOf(room);

            if (rooms.Contains(room))
            {
                listBox1.Items.Remove(room);
                rooms.Remove(room);

                studentName.remove();
                AgeStudent.Add(age);
                School.Add(school);
                rooms.Add(roomNumber);

            }
            else if (!rooms.Contains(room)){

                MessageBox.Show("Room not Found");
            }


        }

        private void ButtonShowDetails_Click(object sender, EventArgs e)
        {
            int roomNumber = Convert.ToInt32(textBox5.Text);
            int roomInfo = rooms.IndexOf(roomNumber);
            listBox2.Items.Clear();

            if (rooms.Contains(roomNumber))
            {
                listBox2.Items.Add(studentName[roomInfo]);
                listBox2.Items.Add(AgeStudent[roomInfo]);
                listBox2.Items.Add(School[roomInfo]);
            }
            else if (!rooms.Contains(roomNumber))
                {

                MessageBox.Show("Room doesn't exist");
            }
        }

        void AddStudentMale()
        {
            string student = textBox1.Text;
            string school = textBox2.Text;
            int roomNumber = Convert.ToInt32(textBox4.Text);
            int age = Convert.ToInt32(textBox3.Text);

            //
            studentName.Add(student);
            AgeStudent.Add(age);
            School.Add(school);
            rooms.Add(roomNumber);
        }

        void clearItems()
        {
            //
            textBox1.Clear();
            textBox2.Clear();
            textBox3.Clear();
            textBox4.Clear();
        }
    }
}
