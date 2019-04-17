using System.Windows.Forms;

namespace GUI
{
    public partial class MainWnd : Form
    {
        private void NewProject()
        {
            if (CloseProject())
            {
                proj_manager_ = new ProjectManager();
                var new_tp = new TabPage("程序集1");
                Control code_editor = new CodeEditorControl();
                new_tp.BorderStyle = BorderStyle.FixedSingle;
                code_editor.Dock = DockStyle.Fill;
                new_tp.Controls.Add(code_editor);
                srcTabControl.TabPages.Add(new_tp);
            }
        }

        private bool CloseProject()
        {
            if (proj_manager_ != null)
            {
                if (proj_manager_.isDirty())
                    if (proj_manager_.closeCurrentProject())
                    {
                        srcTabControl.TabPages.Clear();
                        return true;
                    }

                return false;
            }

            return true;
        }
    }
}