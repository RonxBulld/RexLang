using System.Windows.Forms;

namespace GUI
{
    internal class IOAgent
    {
        public static bool SaveProject(ref string proj_path)
        {
            var sfd = new SaveFileDialog();
            sfd.Filter = @"OpenELanguage文件(*.oe)|*.oe";
            sfd.RestoreDirectory = true;
            sfd.FileName = "YourFileName";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                proj_path = sfd.FileName; //获得文件路径
                return true;
            }

            return false;
        }
    }
}