using System.IO;
using System;
using System.ComponentModel.DataAnnotations.Schema;
using System.Security.Policy;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Xml.Linq;
using System.Diagnostics;

namespace Damjan
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
        List<string> wordsYouDontwantToBeSpellchecked = new List<string> { };
        string wordIgnored = "";
        string text_tobesimplified = "";
        private void button1_Click(object sender, EventArgs e)
        {

            wordIgnored = WordsToBeIgnored.Text;
            try
            {
                wordsYouDontwantToBeSpellchecked.Add(wordIgnored);
                MessageBox.Show("Message Added");
                WordsToBeIgnored.Clear();
            }
            catch (Exception ex)
            {
                throw new ApplicationException("Error: ", ex);
            }

        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            text_tobesimplified = SimplifyTextbox.Text;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string path_IgnoreWords = Path.Combine(Directory.GetParent(Directory.GetCurrentDirectory()).ToString(), "words.txt");
            string path_TextSimplify = Path.Combine(Directory.GetParent(Directory.GetCurrentDirectory()).ToString(), "file.txt");


            using (FileStream fs = new FileStream(path_TextSimplify, FileMode.Create))
            {
                using (StreamWriter sw = new StreamWriter(fs))
                {
                    sw.WriteLine(text_tobesimplified);
                }
            }

            using (FileStream fs = new FileStream(path_IgnoreWords, FileMode.Create))
            {
                using (StreamWriter sw = new StreamWriter(fs))
                {
                    foreach (string word in wordsYouDontwantToBeSpellchecked)
                    {
                        sw.WriteLine(word);
                    }
                }
            }
            MessageBox.Show("Text Added");
            this.Close();
        }

    }
}