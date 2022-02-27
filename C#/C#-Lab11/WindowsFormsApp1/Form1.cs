using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            label1.Text = "Ścieżka pliku do przekonwertowania";
            label2.Text = "Ścieżka do pliku stworzonego";
            label3.Text = "Wybierz konwerter";
            button1.Text = "Wybierz";
            button2.Text = "Wybierz";
            button3.Text = "Konwertuj";


            comboBox1.Items.Add("UNICODE");
            comboBox1.Items.Add("ASCII");
            comboBox1.Items.Add("UTF7");
            comboBox1.Items.Add("UTF8");
            comboBox1.Items.Add("UTF32");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            string path = openFileDialog1.FileName;
            label1.Text = path;
        }


        private void button2_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.ShowDialog();
            string pathToCreate = folderBrowserDialog1.SelectedPath + @"\Wynik.sln";
            label2.Text = pathToCreate;
        }


        private void button3_Click(object sender, EventArgs e)
        {
            string Source = System.IO.Path.Combine(label1.Text);
            string Target = System.IO.Path.Combine(label2.Text);
            var text = System.IO.File.ReadAllText($"{Source}");
            using (var fstream = System.IO.File.OpenRead($"{Source}"))
            {
                using (var r = new System.IO.StreamReader(fstream, Encoding.UTF8))
                {
                    using (var fstream2 = System.IO.File.Create($"{Target}"))
                    {
                        switch (comboBox1.SelectedIndex)
                        {
                            case 0:
                                using (var w = new System.IO.StreamWriter(fstream2, Encoding.Unicode))
                                {

                                    var buf = new char[65535];
                                    int read = 0;
                                    read = r.Read(buf, 0, 65535);
                                    w.Write(buf);
                                }
                                break;
                            case 1:
                                using (var w = new System.IO.StreamWriter(fstream2, Encoding.ASCII))
                                {

                                    var buf = new char[65535];
                                    int read = 0;
                                    read = r.Read(buf, 0, 65535);
                                    w.Write(buf);
                                }
                                break;
                            case 2:
                                using (var w = new System.IO.StreamWriter(fstream2, Encoding.UTF7))
                                {

                                    var buf = new char[65535];
                                    int read = 0;
                                    read = r.Read(buf, 0, 65535);
                                    w.Write(buf);
                                }
                                break;
                            case 3:
                                using (var w = new System.IO.StreamWriter(fstream2, Encoding.UTF8))
                                {

                                    var buf = new char[65535];
                                    int read = 0;
                                    read = r.Read(buf, 0, 65535);
                                    w.Write(buf);
                                }
                                break;
                            case 4:
                                using (var w = new System.IO.StreamWriter(fstream2, Encoding.UTF32))
                                {

                                    var buf = new char[65535];
                                    int read = 0;
                                    read = r.Read(buf, 0, 65535);
                                    w.Write(buf);
                                }
                                break;
                        }
                    }
                }
            }
        }
    }
}
