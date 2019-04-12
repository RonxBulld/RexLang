using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    public partial class MainWnd : Form
    {
        private void NewProject()
        {
            if (this.CloseProject())
            {
                this.proj_manager_ = new ProjectManager();
                TabPage new_tp = new TabPage("程序集1");
                Control code_editor = new CodeEditorControl();
                new_tp.BorderStyle = BorderStyle.FixedSingle;
                code_editor.Dock = DockStyle.Fill;
                new_tp.Controls.Add(code_editor);
                this.srcTabControl.TabPages.Add(new_tp);
            }
        }

        private bool CloseProject()
        {
            if (this.proj_manager_ != null)
            {
                if (this.proj_manager_.isDirty())
                {
                    if (this.proj_manager_.closeCurrentProject())
                    {
                        this.srcTabControl.TabPages.Clear();
                        return true;
                    }
                }
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
