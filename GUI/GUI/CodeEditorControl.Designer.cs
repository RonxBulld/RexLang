namespace GUI
{
    partial class CodeEditorControl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.CodeTextBox = new System.Windows.Forms.RichTextBox();
            this.LineNoPanel = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // CodeTextBox
            // 
            this.CodeTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.CodeTextBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.CodeTextBox.Location = new System.Drawing.Point(62, 0);
            this.CodeTextBox.Name = "CodeTextBox";
            this.CodeTextBox.Size = new System.Drawing.Size(802, 479);
            this.CodeTextBox.TabIndex = 4;
            this.CodeTextBox.Text = "";
            this.CodeTextBox.WordWrap = false;
            this.CodeTextBox.VScroll += new System.EventHandler(this.CodeTextBox_VScroll);
            this.CodeTextBox.TextChanged += new System.EventHandler(this.CodeTextBox_TextChanged);
            // 
            // LineNoPanel
            // 
            this.LineNoPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.LineNoPanel.Dock = System.Windows.Forms.DockStyle.Left;
            this.LineNoPanel.Location = new System.Drawing.Point(0, 0);
            this.LineNoPanel.Name = "LineNoPanel";
            this.LineNoPanel.Size = new System.Drawing.Size(56, 479);
            this.LineNoPanel.TabIndex = 3;
            this.LineNoPanel.Paint += new System.Windows.Forms.PaintEventHandler(this.LineNoPanel_Paint);
            // 
            // CodeEditorControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.CodeTextBox);
            this.Controls.Add(this.LineNoPanel);
            this.Name = "CodeEditorControl";
            this.Size = new System.Drawing.Size(864, 479);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox CodeTextBox;
        private System.Windows.Forms.Panel LineNoPanel;
    }
}
