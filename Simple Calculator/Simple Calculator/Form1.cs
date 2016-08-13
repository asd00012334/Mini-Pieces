using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Simple_Calculator
{
    
    public partial class Form1 : Form
    {
        private String current;
        private double result;
        private int operation;
        public delegate void OperType(double para);
        private delegate void ButtonDistribution(object sender, EventArgs e);
        OperType[] operate;
        ButtonDistribution[] buttonDistribution;
        private void Add(double para)
        {
            result += para;
        }
        private void Subtract(double para)
        {
            result -= para;
        }
        private void Product(double para)
        {
            result *= para;
        }
        private void Divide(double para)
        {
            result /= para;
        }
        private void Assign(double para)
        {
            result = para;
        }
        public Form1()
        {
            InitializeComponent();
            current = "0";
            result = 0;
            operation = '=';
            textBox1.Text = "";
            operate = new OperType[128];
            operate['='] = Assign;
            operate['+'] = Add;
            operate['-'] = Subtract;
            operate['*'] = Product;
            operate['/'] = Divide;
            buttonDistribution = new ButtonDistribution[128];
            buttonDistribution['0'] = buttonDistribution['1'] = buttonDistribution['2'] = buttonDistribution['3'] =
            buttonDistribution['4'] = buttonDistribution['5'] = buttonDistribution['6'] = buttonDistribution['7'] =
            buttonDistribution['8'] = buttonDistribution['9'] = buttonDistribution['0'] = buttonDistribution['.'] = buttonNum_Click;
            buttonDistribution['+'] = buttonDistribution['-'] = buttonDistribution['*'] = buttonDistribution['/'] = operate_Click;
            buttonDistribution['='] = equal_Click;
            buttonDistribution['C'] = clear_Click;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }
        private void buttonDistribute(object sender, EventArgs e)
        {
            // The only triggered function by click events.
            buttonDistribution[((Button)sender).Text[0]](sender, e);
        }

        private void equal_Click(object sender, EventArgs e)
        {
            operate[operation](double.Parse(current));
            textBox1.Text = (result).ToString();
            textBox2.Text = "";
            result = 0;
            current = "0";
            operation = '=';
        }

        private void operate_Click(object sender, EventArgs e)
        {
            
            textBox2.Text += ((Button)sender).Text;
            operate[operation](double.Parse(current));
            operation = ((Button)sender).Text[0];
            current = "0";
            textBox1.Text = (result).ToString();
        }

        private void clear_Click(object sender, EventArgs e)
        {
            current = "0";
            result = 0;
            operation = 0;
            textBox2.Text = "";
            textBox1.Text = "";
        }

        private void buttonNum_Click(object sender, EventArgs e)
        {
            Button button = (Button)sender;
            current += button.Text;
            textBox2.Text += button.Text;
            textBox1.Text = (result).ToString();
        }
    }
}
