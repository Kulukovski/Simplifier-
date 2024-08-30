namespace Damjan
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            WordsToBeIgnored = new TextBox();
            SimplifyTextbox = new RichTextBox();
            label1 = new Label();
            button1 = new Button();
            label2 = new Label();
            button2 = new Button();
            SuspendLayout();
            // 
            // WordsToBeIgnored
            // 
            WordsToBeIgnored.Location = new Point(368, 100);
            WordsToBeIgnored.Name = "WordsToBeIgnored";
            WordsToBeIgnored.Size = new Size(146, 33);
            WordsToBeIgnored.TabIndex = 0;
            WordsToBeIgnored.TextChanged += textBox1_TextChanged;
            // 
            // SimplifyTextbox
            // 
            SimplifyTextbox.Location = new Point(231, 194);
            SimplifyTextbox.Name = "SimplifyTextbox";
            SimplifyTextbox.Size = new Size(463, 286);
            SimplifyTextbox.TabIndex = 1;
            SimplifyTextbox.Text = "";
            SimplifyTextbox.TextChanged += richTextBox1_TextChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(35, 103);
            label1.Name = "label1";
            label1.Size = new Size(312, 27);
            label1.TabIndex = 2;
            label1.Text = "Word you don't want to be spellcheck";
            label1.Click += label1_Click;
            // 
            // button1
            // 
            button1.Location = new Point(593, 93);
            button1.Name = "button1";
            button1.Size = new Size(101, 28);
            button1.TabIndex = 3;
            button1.Text = "Submit";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(55, 318);
            label2.Name = "label2";
            label2.Size = new Size(92, 27);
            label2.TabIndex = 4;
            label2.Text = "Text Input";
            // 
            // button2
            // 
            button2.Location = new Point(335, 500);
            button2.Name = "button2";
            button2.Size = new Size(101, 28);
            button2.TabIndex = 5;
            button2.Text = "Submit";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(11F, 27F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 600);
            Controls.Add(button2);
            Controls.Add(label2);
            Controls.Add(button1);
            Controls.Add(label1);
            Controls.Add(SimplifyTextbox);
            Controls.Add(WordsToBeIgnored);
            Font = new Font("Arial Narrow", 11.25F, FontStyle.Regular, GraphicsUnit.Point);
            Margin = new Padding(3, 4, 3, 4);
            Name = "Form1";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "Simple English Translator";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox WordsToBeIgnored;
        private RichTextBox SimplifyTextbox;
        private Label label1;
        private Button button1;
        private Label label2;
        private Button button2;
    }
}