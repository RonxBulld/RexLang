using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    public partial class MainWnd : Form
    {
        private ProjectManager proj_manager_ = null;
        public MainWnd()
        {
            InitializeComponent();
        }

        #region 新建事件
        private void 新建ToolStripButton_Click(object sender, EventArgs e)
        {
            this.NewProject();
        }
        private void 新建ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.NewProject();
        }
        #endregion

        #region 关闭事件
        private void 关闭ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.CloseProject();
            this.Close();
        }
        #endregion
    }
}
