using System;
using System.Windows.Forms;

namespace GUI
{
    public partial class MainWnd : Form
    {
        private ProjectManager proj_manager_;

        public MainWnd()
        {
            InitializeComponent();
        }

        #region 关闭事件

        private void 关闭ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            CloseProject();
            Close();
        }

        #endregion

        #region 新建事件

        private void 新建ToolStripButton_Click(object sender, EventArgs e)
        {
            NewProject();
        }

        private void 新建ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NewProject();
        }

        #endregion
    }
}