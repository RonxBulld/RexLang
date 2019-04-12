using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GUI
{
    class ProjectManager
    {
        private bool dirty_ = false;

        public bool isDirty()
        {
            return this.dirty_; 
        }

        public bool closeCurrentProject()
        {
            return true;
        }
    }
}
