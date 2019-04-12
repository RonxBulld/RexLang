using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    public partial class CodeEditorControl : UserControl
    {
        public CodeEditorControl()
        {
            InitializeComponent();
        }

        private void CodeTextBox_TextChanged(object sender, EventArgs e)
        {
            this.showLineNo();
        }

        private void CodeTextBox_VScroll(object sender, EventArgs e)
        {
            this.showLineNo();
        }

        private void showLineNo()
        {
            Point p = this.CodeTextBox.Location;
            int firstIndex = this.CodeTextBox.GetCharIndexFromPosition(p);
            int firstLine = this.CodeTextBox.GetLineFromCharIndex(firstIndex);
            Point firstPos = this.CodeTextBox.GetPositionFromCharIndex(firstIndex);
            p.Y += this.CodeTextBox.Height;
            int lastIndex = this.CodeTextBox.GetCharIndexFromPosition(p);
            int lastLine = this.CodeTextBox.GetLineFromCharIndex(lastIndex);
            Point lastPos = this.CodeTextBox.GetPositionFromCharIndex(lastIndex);
            // 准备画图
            Bitmap bmp = new Bitmap(this.LineNoPanel.ClientRectangle.Width, this.LineNoPanel.ClientRectangle.Height);
            Graphics lineNoGraphics = Graphics.FromImage(bmp);
            Font font = new Font(this.CodeTextBox.Font, this.CodeTextBox.Font.Style);
            SolidBrush brush = new SolidBrush(Color.Green);
            // 画图开始
            // 刷新画布
            Rectangle rect = this.LineNoPanel.ClientRectangle;
            brush.Color = this.LineNoPanel.BackColor;
            lineNoGraphics.FillRectangle(brush, 0, 0, this.LineNoPanel.ClientRectangle.Width, this.LineNoPanel.ClientRectangle.Height);
            brush.Color = Color.Black;
            // 绘制行号
            int lineSpace = 0;
            if (firstLine != lastLine)
            {
                lineSpace = (lastPos.Y - firstPos.Y) / (lastLine - firstLine);
            }
            else
            {
                lineSpace = Convert.ToInt32(this.CodeTextBox.Font.Size);
            }

            float BrushY = lastPos.Y + Convert.ToInt32(font.Size * 0.21f);
            for (int i = lastLine; i >= firstLine; i--)
            {
                string lineStr = (i + 1).ToString();
                float brushX = (float)this.LineNoPanel.ClientRectangle.Width - (font.Size * lineStr.Length) + (font.Size * (lineStr.Length - 1) * 0.3f);
                lineNoGraphics.DrawString(lineStr, font, brush, brushX, BrushY);
                BrushY -= lineSpace;
            }

            Graphics drawLineGraphics = this.LineNoPanel.CreateGraphics();
            drawLineGraphics.DrawImage(bmp, 0, 0);
            bmp.Dispose();
            drawLineGraphics.Dispose();
            lineNoGraphics.Dispose();
            font.Dispose();
            brush.Dispose();
        }

        private void LineNoPanel_Paint(object sender, PaintEventArgs e)
        {
            this.showLineNo();
        }
    }
}
