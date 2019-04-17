using System;
using System.Drawing;
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
            showLineNo();
        }

        private void CodeTextBox_VScroll(object sender, EventArgs e)
        {
            showLineNo();
        }

        private void showLineNo()
        {
            var p = CodeTextBox.Location;
            var firstIndex = CodeTextBox.GetCharIndexFromPosition(p);
            var firstLine = CodeTextBox.GetLineFromCharIndex(firstIndex);
            var firstPos = CodeTextBox.GetPositionFromCharIndex(firstIndex);
            p.Y += CodeTextBox.Height;
            var lastIndex = CodeTextBox.GetCharIndexFromPosition(p);
            var lastLine = CodeTextBox.GetLineFromCharIndex(lastIndex);
            var lastPos = CodeTextBox.GetPositionFromCharIndex(lastIndex);
            // 准备画图
            var bmp = new Bitmap(LineNoPanel.ClientRectangle.Width, LineNoPanel.ClientRectangle.Height);
            var lineNoGraphics = Graphics.FromImage(bmp);
            var font = new Font(CodeTextBox.Font, CodeTextBox.Font.Style);
            var brush = new SolidBrush(Color.Green);
            // 画图开始
            // 刷新画布
            var rect = LineNoPanel.ClientRectangle;
            brush.Color = LineNoPanel.BackColor;
            lineNoGraphics.FillRectangle(brush, 0, 0, LineNoPanel.ClientRectangle.Width, LineNoPanel.ClientRectangle.Height);
            brush.Color = Color.Black;
            // 绘制行号
            var lineSpace = 0;
            if (firstLine != lastLine)
                lineSpace = (lastPos.Y - firstPos.Y) / (lastLine - firstLine);
            else
                lineSpace = Convert.ToInt32(CodeTextBox.Font.Size);

            float BrushY = lastPos.Y + Convert.ToInt32(font.Size * 0.21f);
            for (var i = lastLine; i >= firstLine; i--)
            {
                var lineStr = (i + 1).ToString();
                var brushX = LineNoPanel.ClientRectangle.Width - font.Size * lineStr.Length + font.Size * (lineStr.Length - 1) * 0.3f;
                lineNoGraphics.DrawString(lineStr, font, brush, brushX, BrushY);
                BrushY -= lineSpace;
            }

            var drawLineGraphics = LineNoPanel.CreateGraphics();
            drawLineGraphics.DrawImage(bmp, 0, 0);
            bmp.Dispose();
            drawLineGraphics.Dispose();
            lineNoGraphics.Dispose();
            font.Dispose();
            brush.Dispose();
        }

        private void LineNoPanel_Paint(object sender, PaintEventArgs e)
        {
            showLineNo();
        }
    }
}