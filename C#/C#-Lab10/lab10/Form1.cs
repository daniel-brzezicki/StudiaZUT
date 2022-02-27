using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace lab10
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();


        }

        void CopyFiles(string path, string target)
        {
            if (!System.IO.Directory.Exists(path))
            {
                //path = System.IO.Directory.GetCurrentDirectory();\
                label3.ForeColor = Color.Red;
                label3.Text = "Błędna ścieżka wejścia";
                return;
            }

            if (!System.IO.Directory.Exists(target))
            {
                if(target != "")
                    System.IO.Directory.CreateDirectory(target);
                else
                {
                    label3.ForeColor = Color.Red;
                    label3.Text = "Błędna ścieżka wyjścia";
                    return;
                }

            }


            //Specify what files are we looking for
            string[] files = System.IO.Directory.GetFiles(path, "*.jpg");

            //Files found in path
            foreach (string s in files)
            {
                System.IO.FileInfo fileInfo = null;
                try
                {
                    fileInfo = new System.IO.FileInfo(s);
                }
                catch (System.IO.FileNotFoundException e)
                {
                    //Console.WriteLine(e.Message);
                    continue;
                }

                //wrzucenie do innego folderu
                System.IO.DirectoryInfo directory = new System.IO.DirectoryInfo(path);
              //  Console.WriteLine("{0}", directory);

                string FileName = $"{fileInfo.CreationTimeUtc}" + $"{directory.Name}.jpg";
                FileName = string.Concat(FileName.Split(Path.GetInvalidFileNameChars()));
                string FullPath = System.IO.Path.Combine(target, FileName);

                if (!File.Exists(FullPath))
                {
                    File.Copy(s, FullPath);
                    //Console.WriteLine("[INFO] Skopiowano zdjecie: {0}", FullPath);
                }
                else
                {
                    //Console.WriteLine("[OSTRZEZENIE] To zdjecie juz isnieje");
                }

            }


            string[] directories = System.IO.Directory.GetDirectories(path);

            //Enter every subdir
            foreach (string s in directories)
            {
                //ShowFiles(s, target);
                if (s != target)
                {
                    CopyFiles(s, target);
                }
            }

            label3.ForeColor = Color.Green;
            label3.Text = "Pomyślnie przekopiowano do " + target;
        }


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            CopyFiles(textBox1.Text,textBox2.Text);

        }


        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
