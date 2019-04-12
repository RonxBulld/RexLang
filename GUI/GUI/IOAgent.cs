using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI
{
    class IOAgent
    {
        public static bool SaveProject(ref string proj_path)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = @"OpenELanguage文件(*.oe)|*.oe";
            sfd.RestoreDirectory = true;
            sfd.FileName = "YourFileName";
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                proj_path = sfd.FileName.ToString(); //获得文件路径
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}