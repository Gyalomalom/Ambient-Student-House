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
        List<bool> Inside = new List<bool>();
        List<string> Fridge = new List<string>();
        bool add = false;
        bool remove = false;
        int roomNumber;
        int roomInfo ;
        public Form1()
        {
            InitializeComponent();
            serialPortColor.Open();
            serialPortFan.Open();
            serialPortLCD.Open();
            serialPortLights.Open();
            serialPortRFID.Open();
            timer1.Start();
            rooms.Add(1);
            studentName.Add("Mitchell");
            AgeStudent.Add(22);
            School.Add("Fontys");
           Inside.Add(false);
            listBox1.Items.Add(rooms[0]);
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
            }
            else if (rooms.Contains(RoomNumber))
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
            int room = Convert.ToInt32(textBox6.Text);

            int studentInfo = rooms.IndexOf(room);

            if (rooms.Contains(room))
            {
                listBox1.Items.Remove(room);
                rooms.Remove(room);

                studentName.RemoveAt(studentInfo);
                AgeStudent.RemoveAt(studentInfo);
                School.RemoveAt(studentInfo);

            }
            else if (!rooms.Contains(room))
            {

                MessageBox.Show("Room not Found");
            }

        }

        private void ButtonShowDetails_Click(object sender, EventArgs e)
        {
             roomNumber = Convert.ToInt32(textBox5.Text);
             roomInfo = rooms.IndexOf(roomNumber);
            listBox2.Items.Clear();

            if (rooms.Contains(roomNumber))
            {
                listBox2.Items.Add(studentName[roomInfo]);
                listBox2.Items.Add(AgeStudent[roomInfo]);
                listBox2.Items.Add(School[roomInfo]);
               listBox2.Items.Add(Inside[roomInfo]);
            }
            else if (!rooms.Contains(roomNumber))
            {

                MessageBox.Show("Room isn't occupied");
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

     


       

        private void Timer1_Tick(object sender, EventArgs e)
        {
            string command = serialPortLCD.ReadExisting().Trim();
            string id = serialPortRFID.ReadExisting().Trim();
            string colour = serialPortColor.ReadExisting().Trim();
            int command_prot;
            if (command != "")
            {
                command_prot = Convert.ToInt32(command);
            }
            else if (id != "")
            {
                command_prot = Convert.ToInt32(id);
            }
            else if(colour != "")
            {
                command_prot = Convert.ToInt32(colour);
            }
            else
            {
                command_prot = -1;
            }




            if (command_prot % 10 == 1)
            {
                command_prot = command_prot / 10;
                serialPortLights.WriteLine($"{command_prot}");
            }
            else if (command_prot % 10 == 2)
            {
                command_prot = command_prot / 10;
                if (command_prot == 200)
                {
                    serialPortFan.WriteLine("C;");
                }
                else if (command_prot < 35 && command_prot != 0)
                {
                    command_prot = 35;
                }
                serialPortFan.WriteLine($"B;{command_prot};");
            }
            else if (command_prot % 10 == 3)
            {
                command_prot = command_prot / 10;
                if (command_prot == 1)
                {

                    if (Inside[0] == false)
                    {

                        Inside[0] = true;
                        listBox2.Items.Clear();
                        listBox2.Items.Add(studentName[roomInfo]);
                        listBox2.Items.Add(AgeStudent[roomInfo]);
                        listBox2.Items.Add(School[roomInfo]);
                        listBox2.Items.Add(Inside[roomInfo]);
                    }
                    else if (Inside[0] == true)
                    {

                        Inside[0] = false;
                        listBox2.Items.Clear();
                        listBox2.Items.Add(studentName[roomInfo]);
                        listBox2.Items.Add(AgeStudent[roomInfo]);
                        listBox2.Items.Add(School[roomInfo]);
                        listBox2.Items.Add(Inside[roomInfo]);
                    }

                }
            }
            else if(command_prot % 10 == 4)
            {
                command_prot = command_prot / 10;
                if (add)
                {
                    if(command_prot == 1)
                    {
                        Fridge.Add("Banana");
                        fridgeListbox.Items.Add("Banana");
                        add = false;
                    }
                    if (command_prot == 2)
                    {
                        Fridge.Add("Orange");
                        fridgeListbox.Items.Add("Orange");
                        add = false;
                    }
                    if (command_prot == 3)
                    {
                        Fridge.Add("Meat");
                        fridgeListbox.Items.Add("Meat");
                        add = false;

                    }
                    if (command_prot == 4)
                    {
                        Fridge.Add("Vegetable");
                        fridgeListbox.Items.Add("Vegetable");
                        add = false;
                    }
                    if (command_prot == 5)
                    {
                        Fridge.Add("Water");
                        fridgeListbox.Items.Add("Water");
                        add = false;
                    }
                }
                if (remove)
                {
                    if (command_prot == 1)
                    {
                        Fridge.Remove("Banana");
                        fridgeListbox.Items.Remove("Banana");
                        remove = false;
                    }
                    if (command_prot == 2)
                    {
                        Fridge.Remove("Orange");
                        fridgeListbox.Items.Remove("Orange");
                        remove = false;

                    }
                    if (command_prot == 3)
                    {
                        Fridge.Remove("Meat");
                        fridgeListbox.Items.Remove("Meat");
                        remove = false;


                    }
                    if (command_prot == 4)
                    {
                        Fridge.Remove("Vegetable");
                        fridgeListbox.Items.Remove("Vegetable");
                        remove = false;

                    }
                    if (command_prot == 5)
                    {
                        Fridge.Remove("Water");
                        fridgeListbox.Items.Remove("Water");
                        remove = false;

                    }
                }
            }



        }

        private void BtnAdd_Click(object sender, EventArgs e)
        {
            add = true;
            remove = false;
        }

        private void Remove_Click(object sender, EventArgs e)
        {
            remove = true;
            add = false;
        }
    }
}
