
//new added:
using System.Drawing.Drawing2D;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
namespace RNAViewerNS
{
    
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        public Form1 create()
        {
            log("start loging...");
            /*RNAViewer v=new RNAViewer();
            string s = "sd21fsds0dfs21ds1ds0dfs12d2s1f0sd2s11sdsf0sd2f1sdfsdf2121";
            if (!v.init(s,s))
            {
                log("arg error!!!!!!!!!!");
            }
            RNAViewer.Args args= new RNAViewer.Args();*/
           /* args.size=30;
            args.fontSize=10;
            args.spaceLen=8;

            args.basicLineColor=Color.Red;
            args.pairLineColor=Color.Blue;
            args.fontColor=Color.Green;*/
             RNAViewer rnaViwer = new RNAViewer();
         string rnaImageName = "rna.gif";
         string seqs = "0101011000";
            rnaImageName = Directory.GetCurrentDirectory() + "\\rnaImages";
            if (!Directory.Exists(rnaImageName)) Directory.CreateDirectory(rnaImageName);

            rnaImageName = rnaImageName + "\\" + seqs + ".gif";
            if (!File.Exists(rnaImageName))
            {
                rnaViwer.init(seqs, seqs);
                rnaViwer.create(rnaImageName);
            }
            //
            if (!Directory.Exists(".\\image"))
            {
                Directory.CreateDirectory(".\\image");
            }
            v.create(System.Environment.CurrentDirectory+"\\image\\rna.gif",args);
            return this;
        }
        public static void log(string mess)
        {
            label1.Text += mess + "\n";
        }
        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point(12, 9);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(0, 12);
            label1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private static System.Windows.Forms.Label label1;

    }
}

