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
using System.Security.Permissions;


namespace lab12
{

    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
            label1.Text = "";
            label2.Text = "Podaj ścieżkę do monitorowania";
            label3.Text = "Podaj ścieżkę wyjścia";
            label4.Text = "Podaj rozszerzenie do monitorowania (Puste dla wszystkich plików)";
            button1.Text = "Backup";
            button2.Text = "Wybierz";
            button3.Text = "Wybierz";
        }


        [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
        private void button1_Click(object sender, EventArgs e)
        {

            FileSystemWatcher watcher = fileSystemWatcher1;


            string path = System.IO.Path.Combine(label2.Text);

            if (path != "")
            {
                label1.ForeColor = Color.Green;
                label1.Text = "Backupy są zapisywane do: " + label3.Text;

                watcher.Path = path;

                
                string ext = textBox1.Text;
                bool extIsCorrect = false;

                for(int i = 0; i < ext.Length; i++)
                {
                    if (ext[0] == '.' && Char.IsLetter(ext[i]))
                        extIsCorrect = true;
                    else
                        extIsCorrect = false;
                }

                if(extIsCorrect)
                    watcher.Filter = "*"+ext;
                else
                    watcher.Filter = "*.*";



                watcher.NotifyFilter = NotifyFilters.LastAccess
                                     | NotifyFilters.LastWrite
                                     | NotifyFilters.FileName
                                     | NotifyFilters.DirectoryName;


                watcher.Changed += fileSystemWatcher1_Changed;
                watcher.Created += fileSystemWatcher1_Changed;
                watcher.Deleted += fileSystemWatcher1_Changed;
                watcher.Renamed += fileSystemWatcher1_Changed;


                watcher.EnableRaisingEvents = true;
            }
        }



        private void button2_Click(object sender, EventArgs e)
        {
            folderBrowserDialog1.ShowDialog();
            string path = folderBrowserDialog1.SelectedPath;
            label2.Text = path;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            folderBrowserDialog2.ShowDialog();
            string pathToCreate = folderBrowserDialog2.SelectedPath + @"\Backup";
            label3.Text = pathToCreate;
        }

        [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
        private void fileSystemWatcher1_Changed(object sender, FileSystemEventArgs e)
        {

            DateTime now = DateTime.Now;
            string date = "_" + now.Day + "-" + now.Month + "-" + now.Year + "-" + now.Hour + "-" + now.Minute + "-" + now.Second;
            string backupName = "/B" + date;

            string path = System.IO.Path.Combine(label2.Text);
            string destination = System.IO.Path.Combine(label3.Text+backupName);

            foreach (string dirPath in Directory.GetDirectories(path, "*", SearchOption.AllDirectories))
                Directory.CreateDirectory(dirPath.Replace(path, destination));

            foreach (string file in Directory.GetFiles(path, "*.*", SearchOption.AllDirectories))
                File.Copy(file, file.Replace(path, destination), true);

        }
    }
}
